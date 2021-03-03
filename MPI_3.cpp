#include <iostream>
#include <vector>
#include "mpi.h"
#include "LongDouble.h"

int main(int argc, char **argv){
      int rank, size;
      int steps;
      steps = 100;
      LongDouble factotial_x(1.0);
      LongDouble summ(0.0);
      MPI_Status status;


      MPI_Init(&argc, &argv);
      MPI_Comm_size(MPI_COMM_WORLD, &size);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      std::cont << "1" << rank << std::endl;

      for (int i = rank; i <= steps; i += size) {
          for (int k = i; k > i - size && k > 0; k--) {
              factotial_x *= k;
          }
          summ = summ + factotial_x.inverse();
      }

      std::cont << "2" << rank << std::endl;

      if (rank != 0) {
          std::ostringstream summ_ostr;
          summ_ostr << summ;
          std::string sring_summ_ostr = summ_ostr.str();
          MPI_Send(sring_summ_ostr.c_str(), sring_summ_ostr.length(), MPI_CHAR, 0, 5, MPI_COMM_WORLD);
      }

      if (rank == 0) {
          LongDouble exp(0.0);

          std::cont << "3" << rank << std::endl;

          for (int i = 1; i < size; i++) {
              char* buffer_strings_subtotals[size];
              int num_length;
              MPI_Get_count(&status, MPI_CHAR, &num_length);
              MPI_Recv(buffer_strings_subtotals[i], num_length, MPI_CHAR, i, 5, MPI_COMM_WORLD, &status);
              exp = exp + LongDouble(buffer_strings_subtotals[i]);
              std::cout << "5" << rank << std::endl;
          }

          exp = exp + summ;

          std::cout << "exp = " << exp << std::endl;
      }

    MPI_Finalize();
    return 0;


}
