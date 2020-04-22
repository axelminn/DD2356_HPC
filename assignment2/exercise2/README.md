## Exercise 2 – STREAM benchmark and the importance of threads
Here we’re going to measure the sustained memory bandwidth on a node of the Beskow supercomputer and study the impact of using different numbers of threads and schedules.

Expected knowledge includes an understanding of parallel for constructs and different OpenMP schedules.

Instructions. Download the STREAM benchmarkPreview the document, measure the bandwidth varying the number of threads and varying the schedules for the four STREAM kernels.

# Questions. Here the steps you need to follow for the exercise submission:

1. Run the STREAM benchmark for 5 times and record the average values of bandwidth and its standard deviation for the copy kernel

Done!

2. Prepare a plot (with Excel, Matlab, Gnuplot, …) comparing the bandwidth using 1-2-4-8-12-16-20-24-28-32 threads.

Done! [TO-DO] Plot 

3. How does the bandwidth measured with copy kernel depend on the number of threads?

[TO-DO] see the plot

4. Prepare a plot comparing the bandwidth measured with copy kernel with static, dynamic and guided schedules using 32 threads.

''bash
export OMP_NUM_THREADS=32
gcc -fopenmp stream.c
./a.out > test32guided.txt
'''

''bash
export OMP_NUM_THREADS=32
gcc -fopenmp stream.c
./a.out > test32static.txt
'''

''bash
export OMP_NUM_THREADS=32
gcc -fopenmp stream.c
./a.out > test32dynamic.txt
'''

all in the .txt files

5. How do you set the schedule in the STREAM code? What is the fastest schedule and why do you think it is so?

"#pragma omp parallel for schedule(SET_SCHEDULE)"

[TO-DO] see results.

Example:

Output:

-------------------------------------------------------------
Number of Threads requested = 4
Number of Threads counted = 4
-------------------------------------------------------------
…
-------------------------------------------------------------
Function    Best Rate MB/s  Avg time     Min time     Max time
Copy:           11839.5     0.013682     0.013514     0.013894
… 

''bash
$ export OMP_NUM_THREADS=1
'''
