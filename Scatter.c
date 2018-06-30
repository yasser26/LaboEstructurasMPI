#include <mpi.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  int rank, root_process, ierr, size , N ,numProc;
  MPI_Status status;
  MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccion
  srand(time(NULL));
  N = atoi(argv[1]);

  numProc = N / size;

  float arrNum[N];
  if (rank == 0){
    printf("Num por proceso %d\n",numProc );
    printf("Array generado \n [ " );
    for (int i = 0; i < N; i++) {
      arrNum[i]= (float) (rand()%20); // generate random number 0-19
      if(i == N-1)
        printf("%.1f]\n",arrNum[i] );
        else
          printf("%.1f,",arrNum[i] );
    }
  }
  float subArr[numProc] ;
  MPI_Scatter(&arrNum, numProc, MPI_FLOAT, &subArr, numProc, MPI_FLOAT, 0, MPI_COMM_WORLD);
  float average;

  for (int i = 0; i < numProc; i++) {
    //printf("Node %d , recived %f\n",rank,subArr[i]);
    average += subArr[i];
  }
  average = average/numProc;
  float averageArr[size];
  MPI_Gather(&average, 1, MPI_FLOAT, averageArr, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);

  if (rank == 0) {
    float avg = 0;
    for (int i = 0; i < size; i++) {
      avg += averageArr[i];
    }
    avg = avg/size;
    printf("Promedio entre nodos %.2f\n", avg);
    // Compute the average across the original data for comparison
    float allAvg = 0;
    for (int i = 0; i < N; i++) {
      allAvg += arrNum[i];
    }
    allAvg = allAvg/N;
    printf("Promedio general %.2f\n", allAvg);
    printf("RECORDAR:\n Si los valores del promedio general y entre nodos es distintos, es porque la función MPI_Scatter distribuye equitativamente, si se quisiera repartir distinta cantidad se debe usar Scatterv y Gatherv. Si estos no se utilizan entonces el número de procesadores debe ser multiplo del largo del array.\n ");
  }
  MPI_Barrier(MPI_COMM_WORLD);
  MPI_Finalize();
return 0;
}
