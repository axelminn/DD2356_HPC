#include <stdio.h>
#include <omp.h>

/* use private, better than using build in functions */
int main(){
    int num_threads, thread_id;
    
    #pragma omp parallel private(num_threads, thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("Hello World from Thread %d!\n", thread_id);
        // if (thread_id == 0)
        // {
        //     num_threads = omp_get_num_threads();
        //     printf("Total # of threads is: %d\n", num_threads);
        // }
    }
    return 0;
}

/* basic code */
// int main(){

//     omp_set_num_threads(8);
//     #pragma omp parallel
//     {
//         int thread_id = omp_get_thread_num();
//         printf("Hello World from Thread %d!\n", thread_id);
//     }
//     return 0;
// }
