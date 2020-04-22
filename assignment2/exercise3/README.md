## Exercise 3 – Maxloc, parallel for, race condition atomic, critical and false sharing
Here, you are going to implement and parallelize a simple C code to find the maximum value of an array with 1E6 elements and its location in the array. Expected knowledge includes an understanding of parallel for constructs, race condition and false sharing. For this exercise, it is useful to check Lecture: OpenMP and maxloc.

Instructions. Implement a serial and an OpenMP parallel version of maxloc.

The simple skeleton version of the code is the following:

  double maxval = 0.0; int maxloc = 0;
  for (int i=0; i < 1000000; i++){
       if (x[i] > maxval) 
            maxval = x[i]; maxloc = i;
  }
 We can initialize the x array as follows:

#include "stdlib.h" // rand for instance.

...
   srand(time(0)); // seed
   for(int i=0; i < N;i++){
     // Generate random number between 0 and 1
     x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
   }
...

# Questions: Here are the steps you need to follow for the exercise submission:

1. Measure the performance of the serial code (average + standard deviation)

$ bash run.sh


2. Use omp parallel for construct to parallelize. Run the code with 32 threads and measure the execution time (average + standard deviation). Is the code correct? If not, why so?

answers both 1 and 2:
# -------------------------------------------------------------
maxloc computation (s) in 0.001299 seconds
maxloc computation (omp) in 0.645857 seconds
maxloc computation (s) in 0.002143 seconds
maxloc computation (omp) in 0.524326 seconds
maxloc computation (s) in 0.001284 seconds
maxloc computation (omp) in 0.513557 seconds
maxloc computation (s) in 0.001241 seconds
maxloc computation (omp) in 0.497253 seconds
maxloc computation (s) in 0.001281 seconds
maxloc computation (omp) in 0.528931 seconds
maxloc computation (s) in 0.001301 seconds
maxloc computation (omp) in 0.504321 seconds
maxloc computation (s) in 0.001230 seconds
maxloc computation (omp) in 0.510668 seconds
maxloc computation (s) in 0.001265 seconds
maxloc computation (omp) in 0.523793 seconds
maxloc computation (s) in 0.001562 seconds
maxloc computation (omp) in 0.499068 seconds
maxloc computation (s) in 0.001238 seconds
maxloc computation (omp) in 0.497909 seconds
# -------------------------------------------------------------

race conditions ??

3. Use omp critical to protect the code region that might be updated by multiple threads concurrently. Measure the execution time for both versions (omp critical) varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32. How does the performance compare to 1 and 2? What is the reason for the performance gain/loss?

Done! 
allt í test<Num>.txt

4. Try to avoid the use of critical section. Let each thread find the maxloc in its own data then combine their local result to get the final result. For instance, we can use temporary arrays indexed by thread number to hold the values found by each thread:
    int maxloc[MAX_THREADS], mloc;
    double maxval[MAX_THREADS], mval;
Measure the performance of the new implementation varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32. Does the performance increase as expected? If not why?

maxloc computation (omp) in 0.000829 seconds, Num threads: 1
maxloc computation (omp) in 0.000781 seconds, Num threads: 2
maxloc computation (omp) in 0.006101 seconds, Num threads: 4
maxloc computation (omp) in 0.001095 seconds, Num threads: 8
maxloc computation (omp) in 0.001318 seconds, Num threads: 12
maxloc computation (omp) in 0.001433 seconds, Num threads: 16
maxloc computation (omp) in 0.001691 seconds, Num threads: 20
maxloc computation (omp) in 0.001292 seconds, Num threads: 24
maxloc computation (omp) in 0.001365 seconds, Num threads: 28
maxloc computation (omp) in 0.001822 seconds, Num threads: 32

5. Write a version of the code in 4 using a technique to remove false sharing with padding. Measure the performance of code varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32.

maxloc computation (omp) in 0.000840 seconds, Num threads: 1
maxloc computation (omp) in 0.000736 seconds, Num threads: 2
maxloc computation (omp) in 0.000631 seconds, Num threads: 4
maxloc computation (omp) in 0.000837 seconds, Num threads: 8
maxloc computation (omp) in 0.001111 seconds, Num threads: 12
maxloc computation (omp) in 0.001081 seconds, Num threads: 16
maxloc computation (omp) in 0.001199 seconds, Num threads: 20
maxloc computation (omp) in 0.001150 seconds, Num threads: 24
maxloc computation (omp) in 0.001303 seconds, Num threads: 28
maxloc computation (omp) in 0.001190 seconds, Num threads: 32
