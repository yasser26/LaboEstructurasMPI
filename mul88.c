/*Multiplicación matricial
Se elije comunicación punto porque con Scatter y Gather no puedo enviar todo el vector para multiplicar , solo pedacitos de él
y aunque reduce puede hacerse, el resultado final no podría enviarse al master como un array de resultados si no como alguna operación
sobre esos reusltados*/

#include <mpi.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const **argv) {
  int rank, root_process, ierr, size,  mX=8,mY=8,vX=8,vY=1 , row ,i ,j ;
  bool control = true;
  MPI_Status status;
  ierr = MPI_Init(&argc, &argv); // Iniciar la aplicacion paralela
  ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank); // Identifica numero de procesos de la aplicacion
  ierr = MPI_Comm_size(MPI_COMM_WORLD,&size); //Permote qie cada proceso identifique su direccion dentro dela coleccion

  srand(time(NULL));

  /*Master crea el vector y la matriz a partir de los datos dados  */
  if(rank == 0){

// Rellena la matriz con numeros aleatorios
  int matrix[mX][mY]; // Matrix with input sizes
  int vector[vX][vY]; // Vector with input sizes
  for( i = 0 ; i < mX ; i++){
    for ( j = 0; j < mY; j++) {
      matrix[i][j]= rand()%10; // Fill matrix with random numbers from 0-9
      if(j<vY && i<vX){
        vector[i][j]= rand()%10; // while filling vector array as well
      }
    }
  }
  // Print Generated Vectors
  printf("Matriz = ( %d , %d )\n", mX , mY);
  for( i = 0; i < mX; i++) {
    printf("\t|");
    for( j = 0; j < mY; j++) {
        printf("%d ", matrix[i][j]);
    }
    printf("|\n");
  }
  printf("Vector = ( %d , %d )\n", vX,vY);
  for(i = 0; i < vX; i++) {
    printf("\t|");
    for( j = 0; j < vY; j++) {
        printf("%d ", vector[i][j]);
    }
    printf("|\n");
  }

  int resultArr[mX];
  for( j = 0; j < mX; j++) {
      resultArr[j] = 0;
  }
  int currentProc = 1 , sendSize = size,initial=0 ;
  row = mX/size;
  for (i = 1; i < size; i++)  {
      MPI_Send(&mY,1,MPI_INT, i , initial , MPI_COMM_WORLD);// send Y max
      MPI_Send(&matrix[initial],mY*row,MPI_INT, i , initial , MPI_COMM_WORLD);// send each line with mY values
      MPI_Send(&vector,mY,MPI_INT, i , initial , MPI_COMM_WORLD); // vector
      //printf("Initial:%d, CP %d , row %d\n",initial,currentProc , row);
      initial += row ;
      currentProc += 1;
    }
    int row1 ;
    for (i = 1; i < size; i++) {
        int resultado;
        ierr = MPI_Recv(&resultado,1,MPI_INT,MPI_ANY_SOURCE, MPI_ANY_TAG , MPI_COMM_WORLD, &status);//
        int num = status.MPI_TAG;
        resultArr[num]=resultado;
      }

  printf("Matriz resultante = ( %d , %d ) \n", mX,1);
    printf("\t|");
    for( j = 0; j < mX; j++) {
        printf("%d ", resultArr[j]);
    }
    printf("|\n");


}else {
  //   MPI_Recv(&count, 1, MPI_INT, rank_opposite, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

  MPI_Recv(&mY,1,MPI_INT, 0 , MPI_ANY_TAG , MPI_COMM_WORLD, &status);//
  //printf("Recieved %d and %d in %d \n", mY ,row, rank );
  int recMatrix[mY];
  int vector[mY];
  MPI_Recv(&recMatrix,mY,MPI_INT,0, MPI_ANY_TAG , MPI_COMM_WORLD , &status);//
  MPI_Recv(&vector,mY,MPI_INT,0, MPI_ANY_TAG , MPI_COMM_WORLD, &status);
  int resultado = 0;
  for ( i = 0; i < mY; i++) {
      resultado += (vector[i])*(recMatrix[i]);
      //  printf("%dx%d=%d Proc: %d\n", vector[i],recMatrix[j][i],resultado[j], rank);
  }

  MPI_Send(&resultado,1,MPI_INT, 0 , status.MPI_TAG , MPI_COMM_WORLD);
}

  MPI_Finalize();
  return 0;
}
