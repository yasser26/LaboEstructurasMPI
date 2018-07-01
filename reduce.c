/*Se recibe por parámetro a N el largo del array y el número de procesadores y la salida es el promedio de un array de tamaño N con números aleatorios
Se crea en cada procesador un array de tamaño N con números aleatorios, del cual cada uno de los procesadores calcula el promedio de N/size elementos
que de la posición rank*(N/size)-rank*(N/size)+(N/size) y con reduce se suman todos esos promedios parciales y se divide entre el número de procesadores
para tener el promedio de un arreglo de tamaño N */
#include <mpi.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int rank, root_process, ierr, size , N ,numProc , partialSum =0 ;
  float partialAvg , totalAvg;
  MPI_Status status;
  MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccion
  srand(time(NULL));
  N = atoi(argv[1]);
  int subArr[N];
  if (rank ==0)
    printf("Array N \n [ " );
  for (int i = 0; i < N ; i++) {
    subArr[i]= rand()%25; // generate random number 0-24
    if (rank == 0){
      if(i == N -1)
        printf("%d]\n",subArr[i] );
        else
        printf("%d,",subArr[i] );
      }
  }

 for (int j = rank*(N/size); j < rank*(N/size)+(N/size); j++) {
    partialSum+=(float)subArr[j];
 }
  printf("Partial Sum : %d from Rank %d \n",partialSum,rank);
  partialAvg = partialSum/(N/size);
  MPI_Reduce(&partialAvg, &totalAvg, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
  if (rank == 0 ){
    printf("El promedio de los N números es %f \n", totalAvg/size );
  }
  MPI_Finalize();
return 0;
  }
