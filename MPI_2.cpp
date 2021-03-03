#include <iostream>
#include <math.h>
#include "mpi.h"



int main(int argc, char **argv){
      int rank, size;
      int steps;
      steps = 100;

      MPI_Init(&argc, &argv);
      MPI_Comm_size(MPI_COMM_WORLD, &size);
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);

      double steps_div = steps / (size);

      int j = 0;
      double x = 1;
      double summ = 0;

      for(int i = 0; i < size; i++){
        if (rank == i){
            for(j = 1; j < i * steps_div + 1; j ++){
                x = x / j;
            }
        if (rank == 0) summ += 1;

            for (j = i * steps_div + 1; j < (i + 1) * steps_div + 1; j ++)
                if (j < steps){
                  x = x / j;
                  summ = summ + x;
                }
        }
      }

      double total_summ = 0;

      if (rank == 0)
        MPI_Reduce(&summ, &total_summ, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

      std::cout.precision(100);
      std::cout << total_summ << std::endl;

      MPI_Finalize();
}
