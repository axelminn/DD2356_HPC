#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <mpi.h> // to uses MPI

#define SEED     921
#define NUM_ITER 1000000000
// #define NUM_ITER 1000

int main(int argc, char* argv[])
{
    int count = 0, total_count=0;
    int rank, size, provided, i, iter_per_p;      
    double x, y, z, pi; 
    double time_start=0.0, time_end=0.0;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_SINGLE, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &size);  /* get number of processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  /* get current process id */

    time_start = MPI_Wtime();

    int count_arr[size];
    iter_per_p = NUM_ITER / size;
    srand(rank * SEED); 

    for (int iter = 0; iter < iter_per_p; iter++)    
    {        
        // Generate random (X,Y) points        
        x = (double)random() / (double)RAND_MAX;        
        y = (double)random() / (double)RAND_MAX;        
        z = sqrt((x*x) + (y*y));        
        // Check if point is in unit circle        
        if (z <= 1.0)        
        {            
            count++;        
        }    
    } 

    MPI_Gather(&count, 1, MPI_INT, &count_arr, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        total_count = count;
        for (int proc = 0; proc < size-1; proc++)
        {
            total_count += count_arr[proc];
        }
        pi = ((double)total_count / (double)NUM_ITER) * 4.0;
        time_end = MPI_Wtime();
        printf("The result is %g\n", pi);  
        printf("The number of processes is %d\n", size);
        printf("The time is %f\n", (time_end-time_start));
    }

    MPI_Finalize();
    return 0;


    /*
    srand(SEED); 
    // Important: Multiply SEED by "rank" when you introduce MPI!    
    // Calculate PI following a Monte Carlo method    
    for (int iter = 0; iter < NUM_ITER; iter++)    
    {        
        // Generate random (X,Y) points        
        x = (double)random() / (double)RAND_MAX;        
        y = (double)random() / (double)RAND_MAX;        
        z = sqrt((x*x) + (y*y));        
        // Check if point is in unit circle        
        if (z <= 1.0)        
        {            
            count++;        
        }    
    }    
    // Estimate Pi and display the result    
    pi = ((double)count / (double)NUM_ITER) * 4.0;    
    printf("The result is %f\n", pi);    
    return 0;
    */
}