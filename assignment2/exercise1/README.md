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

# Questions. Here the steps you need to follow for the exercise submission:

Write an OpenMP C code with each thread printing Hello World from Thread X! where X is the thread ID.

Code is in "hello.c"

Answer the following questions:
1. How do you compile it, which compiler and flags have you used?


'''bash
$ gcc -fopenmp hello.c
$ ./a.out
'''

2. How do you run the OpenMP code on Beskow, what flags did you set?

Running Stream on Beskow (2.4. OpenMP Basics video 23:40)
''bash
$ salloc ...
$ export OMP_NUM_THREADS=4
$ srun -n 1 ./stream
'''

3. How many different ways are there to change the number of threads in OpenMP? Which are they?

There are two different ways to change the number of threads.
- use the "omp_set_num_threads(num_threads);" in the <omp.h> library
- use  "export OMP_NUM_THREADS=<number of threads>" as an environment variable. (used in Beskow)