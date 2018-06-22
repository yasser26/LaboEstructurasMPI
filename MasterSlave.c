#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
  int rank, root_process, ierr, size ;
  MPI_Status status;
  ierr = MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  ierr = MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccion


  if (rank == 0) { //Master
    printf("Pregunta 1 \n");
    int recived;
    // If we are rank 0, set the number to -1 and send it to process 1
    for (int id = 1 ; id < size ; id++) {
       ierr = MPI_Send( &id , 1 , MPI_INT , id , 0 , MPI_COMM_WORLD);
     }

     for (int id = 1 ; id < size ; id++) {
      ierr = MPI_Recv ( &recived , 1 , MPI_INT, id , MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE );
      printf(" Hello World im number %d of %d\n", recived , size );
    }
  } else { //Slaves
      int number;
      MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Send( &number , 1 , MPI_INT , 0 , 0 , MPI_COMM_WORLD);
    }



  MPI_Finalize();
}
