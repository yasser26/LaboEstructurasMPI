# LaboEstructurasMPI

Laboratorio de Open MPI, para el curso IE0521- Estructuras de Computadoras Digitales II. Escuela de Ingeniería Eléctrica, Universidad de Costa Rica.

Integrantes:

Paula Hernández G. - B53375

Yasser Wagon M. - B47732 


# Para HelloWorld2 (imprimir en orden)

  mpicc HelloWorld2.c -o hello
 
 mpiexec -n 6 ./hello
 
 # Pregunta2.c Enviar y recibir 
 
  mpicc Pregunta2.c -o preg2
 
 mpiexec -n 2 ./preg2
 
  # Anillo 
 
  mpicc Ejercicio3_anillo.c -o anillo
 
 mpiexec -n 4 ./anillo
 
# Para Scatter/Gather ( recibe por parámetro N , en este caso 8)

 mpicc Scatter.c -o scatter
 
 mpiexec -n 4 ./scatter 8
 
# Para reduce ( recibe por parámetro N , en este caso 8)

mpicc reduce.c -o reduce 

mpiexec -n 4 ./reduce 8

# Para la múltiplicación de la matriz 8x8

mpicc mul88.c -o mul

mpiexec -n 8 ./mul
