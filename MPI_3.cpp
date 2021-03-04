#include "mpi.h"
#include "LongDouble.h"

struct srtToSend
{
    int sign;
    int digits[4000];
    long exponent;
    int length;
};


int main(int argc, char** argv) {
    int rank, size;
    int steps;
    steps = 100;
    LongDouble factotial_x(1.0);
    LongDouble summ(0.0);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    for (int i = rank; i <= steps; i += size) {
        for (int k = i; k > i - size && k > 0; k--) {
            factotial_x *= k;
        }
        summ = summ + factotial_x.inverse();
    }

    if (rank != 0) {
        srtToSend str;
        memcpy(str.digits, summ.getDigits().data(), summ.getDigits().size());
        str.sign = summ.getSign();
        str.exponent = summ.getExponent();
        str.length = summ.getDigits().size();
        MPI_Send(&str, sizeof(str), MPI_BYTE, 0, 5, MPI_COMM_WORLD);
    }

    if (rank == 0) {
        LongDouble exp(0.0);
        srtToSend sss;
        LongDouble prom;

        for (int i = 1; i < size; i++) {
            MPI_Recv(&sss, sizeof(sss), MPI_BYTE, i, 5, MPI_COMM_WORLD, &status);
            prom.setDigits(sss.digits, sss.length);
            prom.setExponent(sss.exponent);
            prom.setSign(sss.sign);
            exp = exp + prom;
            prom.getDigits().clear();
        }

        exp = exp + summ;

        std::cout << "exp = " << exp << std::endl;
    }

    MPI_Finalize();
    return 0;


}
