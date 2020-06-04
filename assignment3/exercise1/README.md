## Exercise 1 – MPI Hello World, Get Familiar with the MPI Environment
Here we’re going to implement our first MPI program.

Expected knowledge includes basic understanding of the MPI environment, how to compile an MPI program, how to set the number of MPI processes, and retrieve the rank of the process and number of MPI processes at runtime.

Instructions. Write a C code to make each MPI process to print "Hello World from rank X from n processes ! with X = rank of the MPI process and n = total number of processes. Learn how to launch an MPI code on Beskow.

Your code using 4 MPI processes should behave similarly to:

Output:

Hello World from rank 3 from 4 processes!
Hello World from rank 0 from 4 processes!
Hello World from rank 2 from 4 processes!
Hello World from rank 1 from 4 processes!
Questions. Here the steps you need to follow for the exercise submission:

Write the Hello World Code in C
Answer the following questions:

1.  How do you compile it, which compiler and flags have you used if any?

Fist I switch module:
module swap cray-mpich/7.7.8
Then I get allocation:
salloc --nodes=1 -t 00:05:00 -A edu20.dd2356 -C Haswell
Then I compile:
cc hello.c -O2 -o hello.out
Then I run:
srun -n 4 ./hello.out

2.  How do you run the MPI code on Beskow?

srun -n 4 ./hello.out

3.  How do you change the number of MPI processes? 

number after the "-n" flag.
 
4.  Which functions do you use for retrieving the rank of an MPI process and the total number of processes?

MPI_Comm_rank (MPI_COMM_WORLD, &rank);	// get rank
MPI_Comm_size (MPI_COMM_WORLD, &size);	// get number of processors 

5.  What are the names of the most used MPI implementations?

MPI_Init_thread();
MPI_Finalized();

To start and end MPI section.
