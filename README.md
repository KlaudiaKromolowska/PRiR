# PRiR

Project for Parallel and Distributed Programming course at University of Technology in Cracow.
Comparing OpenMP, MPI and hibrid version (OpenMP+MPI)

Commands to compile project  
$ py main.py amount min max  

Parameters:  
amount - amount of numbers to generate  
min - minimum value of number  
max - maximum value of number


$ gcc main.cpp -o main -fopenmp -lstdc++

$ mpiexec -n 8 onlympi.exe