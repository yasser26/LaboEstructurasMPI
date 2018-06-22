#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int rank, root_process, size , count = 0 , max = 20;
  MPI_Status status;
  MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccio

  int rank_opposite = (rank + 1) % 2;
while (count < max ){
  if (rank == count % 2) {
      count++;
      MPI_Send(&count, 1, MPI_INT, rank_opposite, 0, MPI_COMM_WORLD);
      printf("Proceso %d: Envía a ""%d el num. %d\n", rank, rank_opposite, count);
  } else {
      MPI_Recv(&count, 1, MPI_INT, rank_opposite, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      printf( "Proceso %d: Recibe de "" %d el num. %d \n" ,rank, rank_opposite, count );
  }
}
  MPI_Finalize();
}
