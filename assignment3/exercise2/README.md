## Exercise 2 – Calculate PI with MPI
In this exercise, we are going to parallelize the calculation of Pi following a Monte Carlo method and using different communication functions and measure their performance.

Expected knowledge is MPI blocking and non-blocking communication, collective operations, and one-sided communication.

Instructions. Write different versions of MPI codes to calculate pi. The technique we are implementing relies on random sampling to obtain numerical results.  The basic MC algorithm is based on the following steps:

Draw a unit square
Draw a unit circle inside the unit square
Throw a coin in the unit square
Count the rate of success where the coin ends up in the unit circle: P(coin in the circle)
P(coin in the circle) = area of the circle / area of the square = π r^2 / (2 r)^2 = π r^2 / 4 r^2 = π / 4 
--> π = 4 P( coin in the circle)

The serial code (courtesy of ORNL) we are going to parallelize is provided herePreview the document.

# notes:
compile command local:
cc main.c -O2 -o main.out -lm 

# 2.1  MPI Blocking Communication & Linear Reduction Algorithm
In our parallel implementation, we split the number of iterations of the main loop into all the processes (i.e., "NUM_ITER / num_ranks"). Each process will calculate an intermediate count, which is going to be used afterward to calculate the final value of Pi.

To calculate Pi, you need to send all the intermediate counts of each process to rank 0. This communication algorithm for reduction operation is called linear as the communication costs scales as the number of processes.

An example of linear reduction with 8 processing is the following:

linear

Rank 0 is going to receive the intermediate count calculated by each process and accumulate them to its own count value. Finally, after rank 0 has received and accumulated all the intermediate counts, it will calculate Pi and show the result, as in the original code.

Implement this code using blocking communication and test its performance.

Hint 1. Change the main loop to include the number of iterations per process, and not NUM_ITER (which is the total number of iterations).

Hint 2. Do not forget to multiply the seed of srand() with the rank of each process (e.g., “rank * SEED”) to ensure the RNGs of processes generate different random numbers.

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using a linear algorithm with MPI Send/Recv
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it

Using :
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 00:05:00 -A edu20.dd2356 -C Haswell

The result is 3.1416
The number of processes is 8
The time is 3.860348

The result is 3.14158
The number of processes is 16
The time is 1.973509

The result is 3.14157
The number of processes is 32
The time is 1.070448

The result is 3.14161
The number of processes is 64
The time is 0.611238

The result is 3.14162
The number of processes is 128
The time is 0.314987

(TO-DO) Plot!!


Answer the following questions:

Why MPI_Send and MPI_Recv are called "blocking "communication?

Because both MPI_Send and MPI_Recv do not return until the communication is finished. Therefore they block untill the call is succesfull.

What is the MPI function for timing?

MPI_Wtime();

# 2.2 MPI Blocking Communication & Binary Tree Reduction Communication Algorithm
Implement the binary tree communication algorithm for performing the reduction on rank 0 using blocking communication, e.g. MPI_Send / MPI_Recv.

The communication pattern for a reduction with a binary tree with 8 processes is the following:

binary tree

In our implementation, we can assume that we use a power of 2 number of processes.

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using a binary tree algorithm with MPI Send/Recv
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following questions:
How does the performance of binary tree reduction compare to the performance of linear reduction? 

Using : (same as with linear reduction)
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 01:00:00 -A edu20.dd2356 -C Haswell

The result is 1.57082
The number of processes is 8
The time is 3.860834

The result is 1.57076
The number of processes is 16
The time is 1.984907

The result is 1.57075
The number of processes is 32
The time is 1.077781

The result is 1.5708
The number of processes is 64
The time is 0.626081

The result is 1.57082
The number of processes is 128
The time is 0.310368

(TO-DO) Plot!!

Increasing the number of processes, which approach (linear/tree) is going to perform better? Why? Think about the number of messages and their costs.

I would think that the binary tree would outperform the linear reduction if we where to increse the number of processes. It is begining to show in the last run, where the binary tree is outperforming the linear reduction. I think that the binary tree scales better with fewer total messages when working with many processes. 

# 2.3  MPI Non-Blocking Communication & Linear Reduction  Algorithm
Use non-blocking communication for the linear reduction operation (2.1).

Hint: Use a non-blocking MPI_Irecv() . The basic idea is that rank 0 is going to issue all the receive operations and then wait for them to finish. You can either use MPI_Wait() individually to wait for each request to finish or MPI_Waitall(). Regardless of your decision, keep in mind that we want you to perform the receive operations in parallel. Thus, do not call MPI_Irecv() and immediately MPI_Wait()! In addition, we recommend you allocate an array of MPI_Request and also an array of counts (i.e., one for each receive needed).

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using non-blocking communication.
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following questions:

What are the MPI functions for non-blocking communication? What does the "I" in front of function name stand for in non-blocking communication?

MPI_Isend();
MPI_Irecv();

The "I" stands for immediately, I think. Because these returns immediately and need to be waited on, therefore they do not block.

How the performance of non-blocking communication compares to the performance of blocking communication. e.g. performance results in 2.1?

Using : (same as 2.1)
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 01:00:00 -A edu20.dd2356 -C Haswell

The result is 3.1416
The number of processes is 8
The time is 3.857384

The result is 3.14158
The number of processes is 16
The time is 1.962395

The result is 3.14157
The number of processes is 32
The time is 1.071934

The result is 3.14161
The number of processes is 64
The time is 0.612208

The result is 3.14162
The number of processes is 128
The time is 0.341371


# 2.4 MPI Collective: MPI_Gather
Use the collective MPI_Gather() operation, instead of point-to-point communication.

Hint: You can keep rank 0 as the root of the communication and still make this process aggregate manually the intermediate counts. Remember that the goal of MPI_Gather() is to provide the root with an array of all the intermediate values. Reuse the array of counts from Exercise 2 as the output for the gather operation.

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI_Gather
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it

Using :
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 00:05:00 -A edu20.dd2356 -C Haswell

The result is 3.1416
The number of processes is 8
The time is 4.177716

The result is 3.14157
The number of processes is 16
The time is 1.960568

The result is 3.14157
The number of processes is 32
The time is 1.101902

The result is 3.14161
The number of processes is 64
The time is 0.622270

The result is 3.14162
The number of processes is 128
The time is 0.312371

(TO-DO) plot!!

Answer the following question:
Which collective function we could use to send the final pi to all the other processes?

We could use "MPI_Bcast" which is a "one-to-all" communicator to send the value of pi to all processes.

# 2.5 MPI Collective: MPI_Reduce
Use the collective MPI_Reduce() operation.

Hint 1: Remember that the goal of MPI_Reduce() is to perform a collective computation. Use the MPI_SUM operator to aggregate all the intermediate count values into rank 0, But, watch out: rank 0 has to provide its own count as well, alongside the one from the other processes.

Hint 2: The send buffer of MPI_Reduce() must not match the receive buffer. In other words, use a different variable on rank 0 to store the result

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI_Reduce
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it.

Using :
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 01:00:00 -A edu20.dd2356 -C Haswell

The result is 0.493363
The number of processes is 8
The time is 4.529524

The result is 0.330567
The number of processes is 16
The time is 2.452154

The result is 0.265946
The number of processes is 32
The time is 1.065286

The result is 0.250414
The number of processes is 64
The time is 0.630493

The result is 0.250414
The number of processes is 128
The time is 0.311248


(TO-DO) plot!!

# 2.6   MPI Windows and One-Sided Communication & Linear Reduction  Algorithm
Use MPI Windows and MPI one-sided communication (you can choose the function to use but remember that there is a reduction on the same MPI window from many processes!) to implement the code.

# Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI windows and one-sided communication
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it.

Using :
module swap cray-mpich/7.7.8
salloc --nodes=4 -t 01:00:00 -A edu20.dd2356 -C Haswell

The result is 2.7489
The number of processes is 8
The time is 3.891205

The result is 2.94523
The number of processes is 16
The time is 1.961700

The result is 3.0434
The number of processes is 32
The time is 1.087931

The result is 3.09252
The number of processes is 64
The time is 0.627681

The result is 3.11708
The number of processes is 128
The time is 0.325286


Answer the following question:
Which approach gives the best performance among the 2.1 - 2.6 cases? What is the reason for that?

Answer when I have finished the plots !!
(TO-DO) !!!!


Which algorithm or algorithms do MPI implementations use for reduction operations? You can research this on the WEB focusing on one MPI implementation.

(TO-DO) !!!!