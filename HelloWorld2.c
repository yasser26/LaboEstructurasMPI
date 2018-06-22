#include<mpi.h>
#include<stdio.h>
int main(int argc, char *argv[]) {
  int rank, root_process, ierr, size ;
  MPI_Status status;
  ierr = MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  ierr = MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccion
  if(rank %2 == 0){
    printf( "Hello ! My ID is an even number. I am %d of %d \n" , rank , size ) ;
  } else{
    printf( "Hello ! My ID is an odd number. I am %d of %d \n" , rank , size ) ;
  }
  ierr = MPI_Finalize();
  return 0;
}
