#include "stdio.h" // printf
#include "stdlib.h" // rand for instance.
#include "time.h"   // time(0) to get random seed
#include "omp.h"

#define N 1000000

int main(int argc, char* argv[]){
    // Array with doubles
    double x[N];
    // double maxval = 0.0;
    // int maxloc = 0;

    double maxval_1;
    int maxloc_1;
    double start_time, run_time;
    double start_time_1, run_time_1;

    // fill the array
    srand(time(0)); // seed
    for(int i=0; i < N;i++){
        // Generate random number between 0 and 1
        x[i] = ((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*((double)(rand()) / RAND_MAX)*1000;
    }
   
    // start_time_1 = omp_get_wtime();
    // // calculate first serially to get values to checking the results obtianed with OpenMP
    // for (int i=0; i < N; i++){
    //     if (x[i] > maxval) {
    //         maxval = x[i];
    //         maxloc = i;
    //     }
    // }
    // run_time_1 = omp_get_wtime() - start_time_1;
    // maxval_1 = maxval; maxloc_1 = maxloc;
       

    // // OpenMP Version
    // maxval = 0.0; maxloc = 0;
    // start_time = omp_get_wtime();
    // // omp_set_num_threads(32);
    // #pragma omp parallel for
    // for (int i=0; i < N; i++){
    //     #pragma omp critical
    //     {
    //         if (x[i] > maxval) {
    //             maxval = x[i];
    //             // sleep(1); // have this to show race conditions
    //             maxloc = i;
    //         }
    //     }
    // }

     // OpenMP Version for each thread
     // for each thread
    int maxloc[omp_get_max_threads()], mloc;
    double maxval[omp_get_max_threads()], mval;
    start_time = omp_get_wtime();
    #pragma omp parallel shared(maxval,maxloc)
    {
        int id = omp_get_thread_num();
        maxval[id] = -1.0e30;
        #pragma omp for
        for (int i=0; i < N; i++){
            if (x[i] > maxval[id]) {
                maxval[id] = x[i];
                // sleep(1); // have this to show race conditions
                maxloc[id] = i;
            }
        }
    }

    mloc = maxloc[0];
    mval = maxval[0];
    for (int i = 1; i < 32; i++)
    {
        if (maxval[i] > mval)
        {
            mval = maxval[i];
            mloc = maxloc[i];
        }
        
    }

    // // OpenMP Version for each thread
    // // for each thread with Padding
    // typedef struct {double val; int loc; char pad[128]; } tvals;
    // tvals maxinfo[omp_get_max_threads()];
    // start_time = omp_get_wtime();
    // #pragma omp parallel shared(maxinfo)
    // {
    //     int id = omp_get_thread_num();
    //     maxinfo[id].val = -1.0e30;
    //     #pragma omp for
    //     for (int i=0; i < N; i++){
    //         if (x[i] > maxinfo[id].val) {
    //             maxinfo[id].val = x[i];
    //             // sleep(1); // have this to show race conditions
    //             maxinfo[id].loc = i;
    //         }
    //     }
    // }
    
    run_time = omp_get_wtime() - start_time;
   
    // printf("maxloc computation (s) in %f seconds\n",run_time_1);
    printf("maxloc computation (omp) in %f seconds\n",run_time);
   
    // if (maxloc_1 != maxloc)
    //      printf("Test failed\n");

    return(0);

}
