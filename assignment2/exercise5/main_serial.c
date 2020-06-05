#include <string.h>     /* For memset */ 
#include <stdlib.h>     /* srand, rand */
#include <string.h>
#include <math.h>       /* fabs */
#include <stdio.h>      /* print */
#include <omp.h>        /* openmp library like timing */
#include <time.h>       /* time(0) to get random seed */


#define X 0
#define Y 1
#define G 1.0
#define DIM 2
typedef double vect_t[DIM];

int main()
{
    int n = 500;
    int T = 100;
    float delta_t = 0.05;
    float x_diff;
	float y_diff;
    float dist;
    float dist_cubed;

    // omp_set_num_threads(8);

    vect_t* forces = malloc(n*sizeof(vect_t));
    vect_t* pos = malloc(n*sizeof(vect_t));
    vect_t* old_pos = malloc(n*sizeof(vect_t));
    vect_t* vel = malloc(n*sizeof(vect_t));
    double* masses = malloc(n*sizeof(double));
    double* force = malloc(n*sizeof(double));

    // start timer
	double start_time = omp_get_wtime();

    for (int step = 1; step <= T; step++)
    {
        /* Assign 0 to each element of the forces array */
        forces = memset(forces, 0, n*sizeof(vect_t));
		vel = memset(vel, 0, n*sizeof(vect_t));
		pos = memset(pos, 0, n*sizeof(vect_t));
		old_pos = memset(old_pos, 0, n*sizeof(vect_t));

        for (int q = 0; q < n; q++) {
            forces[step][q] = 0;
            pos[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
            pos[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;

            old_pos[q][X] = pos[q][X];
            old_pos[q][Y] = pos[q][Y];

            vel[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
            vel[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;

            masses[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
        }
        /*
        // simple alg
        for (int q = 0; q < n; q++) { 
            for (int k = 0; k < n; k++) { 
                if (k!=q) {
                    x_diff = pos[q][X] - pos[k][X]; 
                    y_diff = pos[q][Y] - pos[k][Y]; 
                    dist = sqrt(x_diff*x_diff + y_diff*y_diff); 
                    dist_cubed = dist*dist*dist; 
                    forces[q][X] -= G * masses[q] * masses[k]/dist_cubed * x_diff;
                    forces[q][Y] -= G * masses[q] * masses[k]/dist_cubed * y_diff;
                }  
            }
        }
        */

        // reduced alg
        for (int q = 0; q < n; q++) { 
            // forces[step][q] = 0;
            for (int k = 0; k < n; k++) { 
                if (k>q) {
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
                }  
            }
        } 

        for (int q = 0; q < n; q++) { 
            pos[q][X] += delta_t * vel[q][X];
            pos[q][Y] += delta_t * vel[q][Y];
            vel[q][X] += delta_t/masses[q] * forces[q][X];
            vel[q][Y] += delta_t/masses[q] * forces[q][Y];
        }  
        
        
        
    }
    // used to make sure the algorithms workes as expected
    // for (int i = 0; i < n; i++) {
	// 	printf("position: %f %f\n", pos[i][X], pos[i][Y]);
	// 	printf("velocity: %f %f\n",vel[i][X], vel[i][Y]);
    // }

    // stop timer
    double run_time = omp_get_wtime() - start_time;
    printf("Time in %f seconds\n",run_time);
    return 0;
}