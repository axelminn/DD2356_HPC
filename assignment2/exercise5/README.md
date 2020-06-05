## Exercise 5 – Develop and Parallelize an N-body simulator

In an n-body problem, we need to find the positions and velocities of a collection of interacting particles over a period of time. For example, an astrophysicist might want to know the positions and velocities of a collection of stars, while a chemist might want to know the positions and velocities of a collection of molecules or atoms.

An n-body solver is a program that finds the solution to an n-body problem by simulating the behavior of the particles. The input to the problem is the mass, position, and velocity of each particle at the start of the simulation, and the output is the position and velocity of each particle at a sequence of user-specified times.

# 5.1 Problem

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

# 5.2 Two Serial Programs

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

# 5.2.1 Simple Algorithm. We can use our formula for the total force on a particle  to refine our pseudocode for the computation of the forces in Lines 4–5:

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

# 5.2.2 Reduced Algorithm. We can use Newton’s third law of motion, that is, for every action there is an equal and opposite reaction, to halve the total number of calculations required for the forces. If the force on particle q due to particle k is fqk, then the force on k due to q is −fqk. Using this simplification we can modify our code to compute forces, as follows:

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

# 5.3 Particle Mover.  The position and velocity remain to be found. We will use the following pseudocode

pos[q][X] += delta_t∗vel[q][X]; 
pos[q][Y] += delta_t∗vel[q][Y]; 
vel[q][X] += delta_t/masses[q]∗forces[q][X]; 
vel[q][Y] += delta_t/masses[q]∗forces[q][Y];
Here, we’re using pos[q], vel[q], and forces[q] to store the position, the velocity, and the force, respectively, of particle q.

# 5.4 Data structures. We are going to use an array type to store our vectors.

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

# 5.5 Initialization. We provide you a simple code on how to initialize the bodies.

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

## Question 1: Implement serial both simple and reduced algorithm of N-Body simulator and answer the following questions:

1. : What is the performance of the serial simple and reduced algorithms in execution time for 500, 1000, 2000 particles using 100 cycles and delta_t = 0.05, no output?

Simple 500:
Time in 0.180513 seconds
Time in 0.183029 seconds
Time in 0.181508 seconds
Time in 0.182412 seconds
Time in 0.183596 seconds

Simple 1000:
Time in 0.833234 seconds
Time in 0.723108 seconds
Time in 0.730627 seconds
Time in 0.778000 seconds
Time in 0.698490 seconds

Simple 2000:
Time in 2.922832 seconds
Time in 2.884527 seconds
Time in 2.928055 seconds
Time in 2.885068 seconds
Time in 2.994144 seconds

Reduced 500:
Time in 0.119798 seconds
Time in 0.127644 seconds
Time in 0.122050 seconds
Time in 0.122329 seconds
Time in 0.122957 seconds

Reduced 1000:
Time in 0.494598 seconds
Time in 0.598320 seconds
Time in 0.509799 seconds
Time in 0.468754 seconds
Time in 0.493692 seconds

Reduced 2000:
Time in 2.021681 seconds
Time in 1.940849 seconds
Time in 1.958425 seconds
Time in 1.916981 seconds
Time in 1.970993 seconds

 


2. : Which algorithm has better cache reuse and why is that? Hint: you can use perf for monitoring cache counters.

Focus on "L1-dcache-loads/L1-dcache-load-misses" 

Reduced 500:
 Performance counter stats for './main.out':

       730 813 373      instructions:u                                                (29,41%)
            10 265      cache-misses:u            #   50,425 % of all cache refs      (38,92%)
            20 357      cache-references:u                                            (34,21%)
            87 499      L1-dcache-load-misses:u   #    0,09% of all L1-dcache hits    (46,11%)
        94 864 295      L1-dcache-loads:u                                             (33,30%)
                 0      LLC-load-misses:u         #    0,00% of all LL-cache hits     (23,79%)
             1 694      LLC-loads:u                                                   (23,02%)
               119      dTLB-load-misses:u        #    0,00% of all dTLB cache hits   (32,54%)
        98 537 526      dTLB-loads:u                                                  (18,99%)

       0,126605571 seconds time elapsed

       0,125970000 seconds user
       0,000000000 seconds sys

Reduced 2000:
 Performance counter stats for './main.out':

    11 125 407 445      instructions:u                                                (33,37%)
            21 494      cache-misses:u            #   13,055 % of all cache refs      (44,31%)
           164 639      cache-references:u                                            (33,24%)
       102 611 850      L1-dcache-load-misses:u   #    7,22% of all L1-dcache hits    (44,35%)
     1 420 942 239      L1-dcache-loads:u                                             (33,16%)
             6 687      LLC-load-misses:u         #    4,78% of all LL-cache hits     (22,21%)
           139 968      LLC-loads:u                                                   (22,22%)
             1 458      dTLB-load-misses:u        #    0,00% of all dTLB cache hits   (33,32%)
     1 432 105 073      dTLB-loads:u                                                  (22,34%)

       1,918652156 seconds time elapsed

       1,904853000 seconds user
       0,000000000 seconds sys

Simple 500:
 Performance counter stats for './main.out':

       915 112 594      instructions:u                                                (30,81%)
            12 740      cache-misses:u            #   41,746 % of all cache refs      (40,70%)
            30 518      cache-references:u                                            (33,63%)
           124 294      L1-dcache-load-misses:u   #    0,15% of all L1-dcache hits    (45,17%)
        80 915 369      L1-dcache-loads:u                                             (32,93%)
               117      LLC-load-misses:u         #    1,92% of all LL-cache hits     (23,04%)
             6 080      LLC-loads:u                                                   (23,07%)
               329      dTLB-load-misses:u        #    0,00% of all dTLB cache hits   (33,43%)
        81 417 691      dTLB-loads:u                                                  (20,25%)

       0,182638443 seconds time elapsed

       0,181469000 seconds user
       0,000000000 seconds sys

Simple 2000:
 Performance counter stats for './main.out':

    14 467 331 966      instructions:u                                                (33,19%)
            30 886      cache-misses:u            #   11,906 % of all cache refs      (44,20%)
           259 419      cache-references:u                                            (33,29%)
       147 616 154      L1-dcache-load-misses:u   #   12,08% of all L1-dcache hits    (44,51%)
     1 221 927 546      L1-dcache-loads:u                                             (33,36%)
            17 640      LLC-load-misses:u         #    9,15% of all LL-cache hits     (22,23%)
           192 796      LLC-loads:u                                                   (22,24%)
             3 114      dTLB-load-misses:u        #    0,00% of all dTLB cache hits   (33,36%)
     1 222 040 576      dTLB-loads:u                                                  (22,13%)

       2,915615851 seconds time elapsed

       2,885698000 seconds user
       0,003237000 seconds sys


## Question 2: Implement an OpenMP parallel version of the two algorithms of the N-body simulators and. Answer the questions:

1. : Which part of the codes has a potential race condition when parallelizing with OpenMP? How do you guarantee the correctness in these parts of the code?

there is possible for race condition in this section because we are using loop-carried dependencies.

(from reduce algorithm)
x_diff = pos[q][X] - pos[k][X]; 
y_diff = pos[q][Y] - pos[k][Y]; 
dist = sqrt(x_diff*x_diff + y_diff*y_diff); 
dist_cubed = dist*dist*dist; 
force[X] = G * masses[q] * masses[k]/dist_cubed * x_diff;
force[Y] = G * masses[q] * masses[k]/dist_cubed * y_diff;
forces[q][X] += force[X];
forces[q][Y] += force[Y];
forces[k][X] -= force[X];
forces[k][Y] -= force[Y];

2. : How the two OpenMP codes scale increasing the number of threads, e.g. 1, 4, 8, 12, 16, 20, 24 28 and 32 threads on Beskow? Make a plot of the parallel speed-up.

Simple 500:
Number of threads 1: Time in 0.316602 seconds
Number of threads 4: Time in 0.487615 seconds
Number of threads 8: Time in 0.324873 seconds
Number of threads 12: Time in 0.209482 seconds
Number of threads 16: Time in 0.221404 seconds
Number of threads 20: Time in 0.436053 seconds
Number of threads 24: Time in 0.232992 seconds
Number of threads 28: Time in 0.215023 seconds
Number of threads 32: Time in 0.243448 seconds

Simple 1000:
Number of threads 1: Time in 1.189261 seconds
Number of threads 4: Time in 0.757257 seconds
Number of threads 8: Time in 0.840256 seconds
Number of threads 12: Time in 0.835009 seconds
Number of threads 16: Time in 0.858627 seconds
Number of threads 20: Time in 0.842854 seconds
Number of threads 24: Time in 0.774562 seconds
Number of threads 28: Time in 0.866475 seconds
Number of threads 32: Time in 0.842747 seconds

Simple 2000:
Number of threads 1: Time in 4.768894 seconds
Number of threads 4: Time in 3.184174 seconds
Number of threads 8: Time in 3.058177 seconds
Number of threads 12: Time in 5.035930 seconds
Number of threads 16: Time in 3.216504 seconds
Number of threads 20: Time in 3.246381 seconds
Number of threads 24: Time in 5.134643 seconds
Number of threads 28: Time in 3.246935 seconds
Number of threads 32: Time in 3.278937 seconds

Reduced 500:
Number of threads 1: Time in 0.173503 seconds
Number of threads 4: Time in 0.243600 seconds
Number of threads 8: Time in 0.217544 seconds
Number of threads 12: Time in 0.220322 seconds
Number of threads 16: Time in 0.224526 seconds
Number of threads 20: Time in 0.225693 seconds
Number of threads 24: Time in 0.239365 seconds
Number of threads 28: Time in 0.243517 seconds
Number of threads 32: Time in 0.225925 seconds

Reduced 1000:
Number of threads 1: Time in 0.686336 seconds
Number of threads 4: Time in 0.899130 seconds
Number of threads 8: Time in 0.858650 seconds
Number of threads 12: Time in 0.917527 seconds
Number of threads 16: Time in 0.861669 seconds
Number of threads 20: Time in 0.831520 seconds
Number of threads 24: Time in 0.937908 seconds
Number of threads 28: Time in 0.852358 seconds
Number of threads 32: Time in 0.865386 seconds

Reduced 2000:
Number of threads 1: Time in 2.745457 seconds
Number of threads 4: Time in 3.447432 seconds
Number of threads 8: Time in 3.418584 seconds
Number of threads 12: Time in 3.178529 seconds
Number of threads 16: Time in 3.251567 seconds
Number of threads 20: Time in 3.177790 seconds
Number of threads 24: Time in 3.141514 seconds
Number of threads 28: Time in 3.445883 seconds
Number of threads 32: Time in 3.147040 seconds

(TO-DO) plot!!!

3. : Use both block and acyclic loop scheduling in the simple and reduced OpenMP implementations. Which loop scheduling works best when using 32 threads on Beskow?

Simple:

(guided, 10):
Time in 3.023720 seconds
Time in 3.016441 seconds
Time in 4.822957 seconds
Time in 5.003484 seconds
Time in 3.010849 seconds

(guided, 5000):
Time in 4.767674 seconds
Time in 4.757770 seconds
Time in 4.787978 seconds
Time in 4.938303 seconds
Time in 5.017736 seconds

(static, 10):
Time in 3.675791 seconds
Time in 3.157467 seconds
Time in 3.282135 seconds
Time in 3.352651 seconds
Time in 3.107625 seconds

(static, 5000):
Time in 4.704940 seconds
Time in 4.729397 seconds
Time in 4.698593 seconds
Time in 4.775341 seconds
Time in 4.742875 seconds

(dynamic, 10):
Time in 5.413995 seconds
Time in 5.453273 seconds
Time in 6.223194 seconds
Time in 5.435821 seconds
Time in 5.364539 seconds

(dynamic, 5000):
Time in 4.776112 seconds
Time in 4.793516 seconds
Time in 4.798693 seconds
Time in 4.758689 seconds
Time in 4.803243 seconds

Reduce:

(guided, 10):
Time in 3.220448 seconds
Time in 3.201219 seconds
Time in 3.119071 seconds
Time in 3.406032 seconds
Time in 3.125385 seconds

(guided, 5000):
Time in 2.838654 seconds
Time in 2.778540 seconds
Time in 2.771020 seconds
Time in 2.737039 seconds
Time in 2.753862 seconds

(static, 10):
Time in 3.449622 seconds
Time in 3.213746 seconds
Time in 3.215886 seconds
Time in 3.184619 seconds
Time in 3.172055 seconds

(static, 5000):
Time in 2.821872 seconds
Time in 2.759450 seconds
Time in 2.722818 seconds
Time in 2.750877 seconds
Time in 2.724886 seconds

(dynamic, 10):
Time in 3.326126 seconds
Time in 3.116538 seconds
Time in 3.298508 seconds
Time in 2.997503 seconds
Time in 3.291990 seconds

(dynamic, 5000):
Time in 2.741222 seconds
Time in 2.774521 seconds
Time in 2.722691 seconds
Time in 2.739539 seconds
Time in 2.934704 seconds
