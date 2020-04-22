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


2. : Which algorithm has better cache reuse and why is that? Hint: you can use perf for monitoring cache counters.


## Question 2: Implement an OpenMP parallel version of the two algorithms of the N-body simulators and. Answer the questions:

1. : Which part of the codes has a potential race condition when parallelizing with OpenMP? How do you guarantee the correctness in these parts of the code?


2. : How the two OpenMP codes scale increasing the number of threads, e.g. 1, 4, 8, 12, 16, 20, 24 28 and 32 threads on Beskow? Make a plot of the parallel speed-up.


3. : Use both block and acyclic loop scheduling in the simple and reduced OpenMP implementations. Which loop scheduling works best when using 32 threads on Beskow?