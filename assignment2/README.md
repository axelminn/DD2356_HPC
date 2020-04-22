# Assignment II: Programming with OpenMP

Due Wednesday by 11:59pm Points 1 Submitting a file upload File Types pdf Available Apr 7 at 12am - May 29 at 11:59pm about 2 months
For each exercise:

Compile a short report according to instructions, and answer questions that are marked Question(s).
Submit your code to a GitHub repo (have the link either in the report or as a comment on the submission page). 
The assignments should be done using either Beskow or your laptop.

## Exercise 1 – OpenMP Hello World, get familiar with OpenMP Environment

Here we’re going to implement the first OpenMP program.

Expected knowledge includes basic understanding of OpenMP environment, how to compile an OpenMP program, how to set the number of OpenMP threads and retrieve the thread ID number at runtime.

Instructions. Write a C code to make each OpenMP thread print Hello World from Thread X! with X = thread ID. Learn how to launch OpenMP code on Beskow or your laptop.

Your code using 4 threads should behave similarly to:

Output:

Hello World from Thread 3!
Hello World from Thread 0!
Hello World from Thread 2!
Hello World from Thread 1!
Questions. Here the steps you need to follow for the exercise submission:

Write an OpenMP C code with each thread printing Hello World from Thread X! where X is the thread ID.
Answer the following questions:
How do you compile it, which compiler and flags have you used?
How do you run the OpenMP code on Beskow, what flags did you set?
How many different ways are there to change the number of threads in OpenMP? Which are they?

## Exercise 2 – STREAM benchmark and the importance of threads
Here we’re going to measure the sustained memory bandwidth on a node of the Beskow supercomputer and study the impact of using different numbers of threads and schedules.

Expected knowledge includes an understanding of parallel for constructs and different OpenMP schedules.

Instructions. Download the STREAM benchmarkPreview the document, measure the bandwidth varying the number of threads and varying the schedules for the four STREAM kernels.

Questions. Here the steps you need to follow for the exercise submission:

Run the STREAM benchmark for 5 times and record the average values of bandwidth and its standard deviation for the copy kernel
Prepare a plot (with Excel, Matlab, Gnuplot, …) comparing the bandwidth using 1-2-4-8-12-16-20-24-28-32 threads.
How does the bandwidth measured with copy kernel depend on the number of threads?
Prepare a plot comparing the bandwidth measured with copy kernel with static, dynamic and guided schedules using 32 threads.
How do you set the schedule in the STREAM code? What is the fastest schedule and why do you think it is so?
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
Questions: Here are the steps you need to follow for the exercise submission:

Measure the performance of the serial code (average + standard deviation)
Use omp parallel for construct to parallelize. Run the code with 32 threads and measure the execution time (average + standard deviation). Is the code correct? If not, why so?
Use omp critical and omp atomic to protect the code region that might be updated by multiple threads concurrently. Measure the execution time for both versions (omp critical) varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32. How does the performance compare to 1 and 2? What is the reason for the performance gain/loss?
Try to avoid the use of critical section. Let each thread find the maxloc in its own data then combine their local result to get the final result. For instance, we can use temporary arrays indexed by thread number to hold the values found by each thread:
    int maxloc[MAX_THREADS], mloc;
    double maxval[MAX_THREADS], mval;
Measure the performance of the new implementation varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32. Does the performance increase as expected? If not why?

Write a version of the code in 4 using a technique to remove false sharing with padding. Measure the performance of code varying the number of threads: 1,2,4,8,16, 20, 24, 28 and 32.

## Exercise 4 – DFTW, The Fastest DFT in the West

The FFTW is the most famous library to solve a Fourier Transform (FT) using the Fast Fourier Transform algorithm. The FFTW takes its names from the fact that it is the fastest FFT in the West if not in the world. The goal of this exercise is to develop the fastest DFT (Discrete Fourier Transform, a different algorithm to calculate FT) in the west by parallelizing the serial C code that is available here.

Your starting point is a serial code DFTW_1.cPreview the document we have developed to compute a DFT in serial. The code calculates direct and inverse DFTs, timing the total time taken for the computation of the two DFTs. The computational core of the program is the DFT subroutine that takes idft argument as 1 for direct DFT and -1 for inverse DFT.

The code also prints the value of the first element of the DFT computation. This is equal to input size (N). You can use this number to quickly check the correctness of your implementation.

You will  focus on parallelizing the DFT function:

int DFT(int idft, double* xr, double* xi, double* Xr_o, double* Xi_o, int N){
        for (int k=0 ; k<N ; k++){
          for (int n=0 ; n<N ; n++{
              // Real part of X[k]
              Xr_o[k] += xr[n] * cos(n * k * PI2 / N) + idft*xi[n]*sin(n * k * PI2 / N);
              // Imaginary part of X[k]
              Xi_o[k] += -idft*xr[n] * sin(n * k * PI2 / N) + xi[n] * cos(n * k * PI2 / N);
           }
      }
…
Instructions and Questions: Here the steps you need to follow for the exercise submission:

Parallelize the DFTW code with OpenMP. You can develop different strategies; the important point is that the code produces the correct results and it is fast!
Measure the performance on Beskow 32 cores reporting the average values and standard deviation for DFTW using an input size equal to 10000 (N=10000).
Prepare a speed-up plot varying the number of threads: 1, 2, 4, 8, 12, 16, 20, 24, 28 and 32.
Which performance optimizations would be suitable for DFT, other than parallelization with OpenMP? Explain, no need for implementing the optimizations.
Example:

output:

DFTW calculation with N = 10000
DFTW computation in 2.107117 seconds
Xre[0] = 8000.000000

## Exercise 5 – Develop and Parallelize an N-body simulator

In an n-body problem, we need to find the positions and velocities of a collection of interacting particles over a period of time. For example, an astrophysicist might want to know the positions and velocities of a collection of stars, while a chemist might want to know the positions and velocities of a collection of molecules or atoms.

An n-body solver is a program that finds the solution to an n-body problem by simulating the behavior of the particles. The input to the problem is the mass, position, and velocity of each particle at the start of the simulation, and the output is the position and velocity of each particle at a sequence of user-specified times.

5.1 Problem

We will write and parallelize a two-dimensional n-body solver that simulates the motions of planets or stars. We’ll use Newton’s second law of motion and his law of universal gravitation to determine the positions and velocities. Thus, if particle q has position sq(t) at time t, and particle k has position sk(t), then the force on particle q exerted by particle k is given by

formula1

Here, G is the gravitational constant (6.673 × 10−11m3 /(kg ·s 2 )), and mq and mk are the masses of particles q and k, respectively. Also, the notation sq(t) − sk(t) represents the distance from particle k to particle q. Note that in general the positions, the velocities, the accelerations, and the forces are vectors.

We can use the equation above to find the total force on any particle by adding the forces due to all the particles. If our n particles are numbered 0, 1, 2,...,n − 1, then the total force on particle q is given by

equation2

The acceleration of an object is given by the second derivative of its position and that Newton’s second law of motion states that the force on an object is given by its mass multiplied by its acceleration, so if the acceleration of particle q is aq(t), then Fq(t) = mqaq(t) = mqs'' q (t), where s''q (t) is the second derivative of the position sq(t). Thus, we can use the equation above to find the acceleration of particle q:

eq3

Therefore, Newton’s laws give us a system of differential equations—equations involving derivatives—and our job is to find at each time t of interest the position sq(t) and velocity vq(t) = s' q (t). We’ll suppose that we either want to find the positions and velocities at the times

deltat

or, more often, simply the positions and velocities at the final time T delta_t. Here, delta_t and T are specified by the user, so the input to the program will be n, the number of particles, delta_t, T, and, for each particle, its mass, its initial position, and its initial velocity.

5.2 Two Serial Programs

In outline, a serial n-body solver can be based on the following pseudocode:

1 Get input data; 
2 for each timestep { 
3      if (timestep output) Print positions and velocities of particles; 
4      for each particle q 
5         Compute total force on q; 
6      for each particle q 
7         Compute position and velocity of q; 
8 } 
9 Print positions and velocities of particles;
5.2.1 Simple Algorithm. We can use our formula for the total force on a particle  to refine our pseudocode for the computation of the forces in Lines 4–5:

for each particle q { 
    for each particle k != q { 
            x_diff = pos[q][X] − pos[k][X]; 
            y_diff = pos[q][Y] − pos[k][Y]; 
            dist = sqrt(x_diff∗x_diff + y_diff∗y_diff); 
            dist_cubed = dist∗dist∗dist; 
            forces[q][X] −= G∗masses[q]∗masses[k]/dist_cubed ∗ x_diff; 
            forces[q][Y] −= G∗masses[q]∗masses[k]/dist_cubed ∗ y_diff; 
    } 
}
Here, we are assuming that the forces and the positions of the particles are stored as two-dimensional arrays, forces and pos, respectively. We’re also assuming we’ve defined constants X = 0 and Y = 1. So the x-component of the force on particle q is forces[q][X] and the y-component is forces[q][Y]. Similarly, the components of the position are pos[q][X] and pos[q][Y].

5.2.2 Reduced Algorithm. We can use Newton’s third law of motion, that is, for every action there is an equal and opposite reaction, to halve the total number of calculations required for the forces. If the force on particle q due to particle k is fqk, then the force on k due to q is −fqk. Using this simplification we can modify our code to compute forces, as follows:

for each particle q 
        forces[q] = 0; 
for each particle q { 
       for each particle k > q {
            x_diff = pos[q][X] − pos[k][X]; 
            y_diff = pos[q][Y] − pos[k][Y]; 
            dist = sqrt(x_diff∗x diff + y_diff∗y diff); 
            dist_cubed = dist∗dist∗dist; 
            force_qk[X] = G∗masses[q]∗masses[k]/dist_cubed ∗ x_diff; 
            force_qk[Y] = G∗masses[q]∗masses[k]/dist_cubed ∗ y_diff 
            forces[q][X] += force_qk[X]; 
            forces[q][Y] += force_qk[Y]; 
            forces[k][X] −= force qk[X]; 
            forces[k][Y] −= force qk[Y]; 
       } 
}
To better understand this pseudocode, imagine the individual forces as a two-dimensional array:

forces

Our original solver simply adds all of the entries in row q to get forces[q]. In our modified solver, when q = 0, the body of the loop for each particle q will add the entries in row 0 into forces[0]. It will also add the kth entry in column 0 into forces[k] for k = 1, 2,...,n − 1. In general, the qth iteration will add the entries to the right of the diagonal (that is, to the right of the 0) in row q into forces[q], and the entries below the diagonal in column q will be added into their respective forces, that is, the kth entry will be added in to forces[k]. Note that in using this modified solver, it’s necessary to initialize the forces array in a separate loop, since the qth iteration of the loop that calculates the forces will, in general, add the values it computes into forces[k] for k = q + 1,q + 2,..., n − 1, not just forces[q].

5.3 Particle Mover.  The position and velocity remain to be found. We will use the following pseudocode

pos[q][X] += delta_t∗vel[q][X]; 
pos[q][Y] += delta_t∗vel[q][Y]; 
vel[q][X] += delta_t/masses[q]∗forces[q][X]; 
vel[q][Y] += delta_t/masses[q]∗forces[q][Y];
Here, we’re using pos[q], vel[q], and forces[q] to store the position, the velocity, and the force, respectively, of particle q.

5.4 Data structures. We are going to use an array type to store our vectors.

#define DIM 2
typedef double vect_t[DIM];
If forces  are stored in an array using contiguous memory, we can use a fast function such as memset to quickly assign zeroes to all of the elements at the beginning of each iteration:

#include <string.h> /∗ For memset ∗/ 
. . . 
vect_t∗ forces = malloc(n∗sizeof(vect t));
. . . 
for (step = 1; step <= n steps; step++) { 
      . . .  
      /∗ Assign 0 to each element of the forces array ∗/ 
     forces = memset(forces, 0, n∗sizeof(vect t); 
     for (part = 0; part < n−1; part++) 
           Compute force(part, forces, . . .)
}
5.5 Initialization. We provide you a simple code on how to initialize the bodies.

	for each particle q {
		pos[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		pos[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		pos[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

		old_pos[i][X] = pos[q][X];
		old_pos[i][Y] = pos[q][Y];
		old_pos[i][Z] = pos[q][Z];

		vel[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		vel[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		vel[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

		mass[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
	}
Question 1: Implement serial both simple and reduced algorithm of N-Body simulator and answer the following questions:

1.1: What is the performance of the serial simple and reduced algorithms in execution time for 500, 1000, 2000 particles using 100 cycles and delta_t = 0.05, no output?
1.2: Which algorithm has better cache reuse and why is that? Hint: you can use perf for monitoring cache counters.
Question 2: Implement an OpenMP parallel version of the two algorithms of the N-body simulators and. Answer the questions:

2.1: Which part of the codes has a potential race condition when parallelizing with OpenMP? How do you guarantee the correctness in these parts of the code?
2.2: How the two OpenMP codes scale increasing the number of threads, e.g. 1, 4, 8, 12, 16, 20, 24 28 and 32 threads on Beskow? Make a plot of the parallel speed-up.
2.3: Use both block and acyclic loop scheduling in the simple and reduced OpenMP implementations. Which loop scheduling works best when using 32 threads on Beskow?