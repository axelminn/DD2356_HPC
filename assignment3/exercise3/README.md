## Exercise 3 – Measure Bandwidth and Latency on Beskow with Ping-Pong
Expected knowledge is concepts of bandwidth and latency and performance model for parallel communication.

The ping-pong is a benchmark code to measure the bandwidth and latency of a supercomputer. In this benchmark, two MPI processes use MPI_Send and MPI_Recv to continually bounce messages off of each other until a final limit.

The ping-pong benchmark provides as output the average time for the ping-pong for different messages sizes.

If we plot the results of the ping-pong with size on the axis and ping-pong time on the y-axis, we will roughly obtain points distributed along a line. If we do a linear best fit of the obtained points, we will get the intercept and the slope of the line. The inverse of the line slope is the bandwidth while the intercept is the latency of the system.

We will use the following codePreview the document to measure the ping-pong time for different message sizes.

Instructions.  For completing this exercise, make sure to check Lecture: Performance Modeling & Ping-Pong.

Run the ping-pong code and calculate the bandwidth and latency for 1) intra-node communication  (2 processes on the same node) 2) inter-node communication (2 processes on different nodes).

# Questions. Here the steps you need to follow for the exercise submission:

Run the ping-pong benchmark for 1) and 2).

cc ping_pong.c -o ping_pong
salloc --nodes=1 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 ./ping_pong

Intra

        N           Time(s)

         8          0.000000575
        16          0.000000606
        32          0.000000668
        64          0.000000746
       128          0.000000916
       256          0.000000772
       512          0.000000901
      1024          0.000001359
      2048          0.000001180
      4096          0.000001729
      8192          0.000003679
     16384          0.000004139
     32768          0.000006690
     65536          0.000011556
    131072          0.000023944
    262144          0.000045180
    524288          0.000086980
   1048576          0.000172107
   2097152          0.000342450
   4194304          0.000682654
   8388608          0.001364646
  16777216          0.002719507
  33554432          0.005528224
  67108864          0.011307344
 134217728          0.022855937
 268435456          0.045983405
 536870912          0.092266812
1073741824          0.184605513

salloc --nodes=2 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 --ntasks-per-node=1 ./ping_pong

Inter

        N           Time(s)

         8          0.000001354
        16          0.000001302
        32          0.000001273
        64          0.000001276
       128          0.000001316
       256          0.000001323
       512          0.000001431
      1024          0.000001645
      2048          0.000002074
      4096          0.000002842
      8192          0.000004706
     16384          0.000005679
     32768          0.000007749
     65536          0.000011454
    131072          0.000019240
    262144          0.000034914
    524288          0.000065758
   1048576          0.000126987
   2097152          0.000254204
   4194304          0.000466502
   8388608          0.000997903
  16777216          0.001978073
  33554432          0.003792682
  67108864          0.008617511
 134217728          0.017515094
 268435456          0.034691787
 536870912          0.070977032
1073741824          0.1414


Plot ping-pong time in function of the message size for 1) and 2). 

(TO-DO) plot !!!

By best fit (using Matlab, Python, or similar), calculate the bandwidth and latency for 1) and 2).

My python code. DONE!

Answer the following question
For case 2), how do the obtained values of bandwidth and latency compare to the nominal Beskow network bandwidth and latency.  What are the differences and what could be the explanation of the differences if any?

(TO-DO)!!!