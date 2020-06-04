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
How do you compile it, which compiler and flags have you used if any?
How do you run the MPI code on Beskow?
How do you change the number of MPI processes? 
Which functions do you use for retrieving the rank of an MPI process and the total number of processes?
What are the names of the most used MPI implementations?

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

2.1  MPI Blocking Communication & Linear Reduction Algorithm
In our parallel implementation, we split the number of iterations of the main loop into all the processes (i.e., "NUM_ITER / num_ranks"). Each process will calculate an intermediate count, which is going to be used afterward to calculate the final value of Pi.

To calculate Pi, you need to send all the intermediate counts of each process to rank 0. This communication algorithm for reduction operation is called linear as the communication costs scales as the number of processes.

An example of linear reduction with 8 processing is the following:

linear

Rank 0 is going to receive the intermediate count calculated by each process and accumulate them to its own count value. Finally, after rank 0 has received and accumulated all the intermediate counts, it will calculate Pi and show the result, as in the original code.

Implement this code using blocking communication and test its performance.

Hint 1. Change the main loop to include the number of iterations per process, and not NUM_ITER (which is the total number of iterations).

Hint 2. Do not forget to multiply the seed of srand() with the rank of each process (e.g., “rank * SEED”) to ensure the RNGs of processes generate different random numbers.

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using a linear algorithm with MPI Send/Recv
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following questions:
Why MPI_Send and MPI_Recv are called "blocking "communication?
What is the MPI function for timing?
2.2 MPI Blocking Communication & Binary Tree Reduction Communication Algorithm
Implement the binary tree communication algorithm for performing the reduction on rank 0 using blocking communication, e.g. MPI_Send / MPI_Recv.

The communication pattern for a reduction with a binary tree with 8 processes is the following:

binary tree

In our implementation, we can assume that we use a power of 2 number of processes.

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using a binary tree algorithm with MPI Send/Recv
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following questions:
How does the performance of binary tree reduction compare to the performance of linear reduction? 
Increasing the number of processes, which approach (linear/tree) is going to perform better? Why? Think about the number of messages and their costs.
2.3  MPI Non-Blocking Communication & Linear Reduction  Algorithm
Use non-blocking communication for the linear reduction operation (2.1).

Hint: Use a non-blocking MPI_Irecv() . The basic idea is that rank 0 is going to issue all the receive operations and then wait for them to finish. You can either use MPI_Wait() individually to wait for each request to finish or MPI_Waitall(). Regardless of your decision, keep in mind that we want you to perform the receive operations in parallel. Thus, do not call MPI_Irecv() and immediately MPI_Wait()! In addition, we recommend you allocate an array of MPI_Request and also an array of counts (i.e., one for each receive needed).

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using non-blocking communication.
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following questions:
What are the MPI functions for non-blocking communication? What does the "I" in front of function name stand for in non-blocking communication?
How the performance of non-blocking communication compares to the performance of blocking communication. e.g. performance results in 2.1?
2.4 MPI Collective: MPI_Gather
Use the collective MPI_Gather() operation, instead of point-to-point communication.

Hint: You can keep rank 0 as the root of the communication and still make this process aggregate manually the intermediate counts. Remember that the goal of MPI_Gather() is to provide the root with an array of all the intermediate values. Reuse the array of counts from Exercise 2 as the output for the gather operation.

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI_Gather
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it
Answer the following question:
Which collective function we could use to send the final pi to all the other processes?
2.5 MPI Collective: MPI_Reduce
Use the collective MPI_Reduce() operation.

Hint 1: Remember that the goal of MPI_Reduce() is to perform a collective computation. Use the MPI_SUM operator to aggregate all the intermediate count values into rank 0, But, watch out: rank 0 has to provide its own count as well, alongside the one from the other processes.

Hint 2: The send buffer of MPI_Reduce() must not match the receive buffer. In other words, use a different variable on rank 0 to store the result

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI_Reduce
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it.
2.6   MPI Windows and One-Sided Communication & Linear Reduction  Algorithm
Use MPI Windows and MPI one-sided communication (you can choose the function to use but remember that there is a reduction on the same MPI window from many processes!) to implement the code.

Questions. Here the steps you need to follow for the exercise submission:

Implement the code using MPI windows and one-sided communication
Measure the performance of the code (execution time) for 8, 16, 32,  64, 128 MPI processes and plot it.
Answer the following question:
Which approach gives the best performance among the 2.1 - 2.6 cases? What is the reason for that?
Which algorithm or algorithms do MPI implementations use for reduction operations? You can research this on the WEB focusing on one MPI implementation.

## Exercise 3 – Measure Bandwidth and Latency on Beskow with Ping-Pong
Expected knowledge is concepts of bandwidth and latency and performance model for parallel communication.

The ping-pong is a benchmark code to measure the bandwidth and latency of a supercomputer. In this benchmark, two MPI processes use MPI_Send and MPI_Recv to continually bounce messages off of each other until a final limit.

The ping-pong benchmark provides as output the average time for the ping-pong for different messages sizes.

If we plot the results of the ping-pong with size on the axis and ping-pong time on the y-axis, we will roughly obtain points distributed along a line. If we do a linear best fit of the obtained points, we will get the intercept and the slope of the line. The inverse of the line slope is the bandwidth while the intercept is the latency of the system.

We will use the following codePreview the document to measure the ping-pong time for different message sizes.

Instructions.  For completing this exercise, make sure to check Lecture: Performance Modeling & Ping-Pong.

Run the ping-pong code and calculate the bandwidth and latency for 1) intra-node communication  (2 processes on the same node) 2) inter-node communication (2 processes on different nodes).

Questions. Here the steps you need to follow for the exercise submission:

Run the ping-pong benchmark for 1) and 2).
Plot ping-pong time in function of the message size for 1) and 2). 
By best fit (using Matlab, Python, or similar), calculate the bandwidth and latency for 1) and 2).
Answer the following question
For case 2), how do the obtained values of bandwidth and latency compare to the nominal Beskow network bandwidth and latency.  What are the differences and what could be the explanation of the differences if any?