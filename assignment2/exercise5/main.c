#include <string.h> /∗ For memset ∗/ 



int main(int argc, char const *argv[])
{

}

// 1 Get input data; 
// 2 for each timestep { 
// 3      if (timestep output) Print positions and velocities of particles; 
// 4      for each particle q 
// 5         Compute total force on q; 
// 6      for each particle q 
// 7         Compute position and velocity of q; 
// 8 } 
// 9 Print positions and velocities of particles;

//simple 
// for each particle q { 
//     for each particle k != q { 
//             x_diff = pos[q][X] − pos[k][X]; 
//             y_diff = pos[q][Y] − pos[k][Y]; 
//             dist = sqrt(x_diff∗x_diff + y_diff∗y_diff); 
//             dist_cubed = dist∗dist∗dist; 
//             forces[q][X] −= G∗masses[q]∗masses[k]/dist_cubed ∗ x_diff; 
//             forces[q][Y] −= G∗masses[q]∗masses[k]/dist_cubed ∗ y_diff; 
//     } 
// }

// //reduced 
// for each particle q 
//         forces[q] = 0; 
// for each particle q { 
//        for each particle k > q {
//             x_diff = pos[q][X] − pos[k][X]; 
//             y_diff = pos[q][Y] − pos[k][Y]; 
//             dist = sqrt(x_diff∗x diff + y_diff∗y diff); 
//             dist_cubed = dist∗dist∗dist; 
//             force_qk[X] = G∗masses[q]∗masses[k]/dist_cubed ∗ x_diff; 
//             force_qk[Y] = G∗masses[q]∗masses[k]/dist_cubed ∗ y_diff 
//             forces[q][X] += force_qk[X]; 
//             forces[q][Y] += force_qk[Y]; 
//             forces[k][X] −= force qk[X]; 
//             forces[k][Y] −= force qk[Y]; 
//        } 
// }

// // mover 
// pos[q][X] += delta_t∗vel[q][X]; 
// pos[q][Y] += delta_t∗vel[q][Y]; 
// vel[q][X] += delta_t/masses[q]∗forces[q][X]; 
// vel[q][Y] += delta_t/masses[q]∗forces[q][Y];

// #define DIM 2
// typedef double vect_t[DIM];

// #include <string.h> /∗ For memset ∗/ 
// . . . 
// vect_t∗ forces = malloc(n∗sizeof(vect t));
// . . . 
// for (step = 1; step <= n steps; step++) { 
//       . . .  
//       /∗ Assign 0 to each element of the forces array ∗/ 
//      forces = memset(forces, 0, n∗sizeof(vect t); 
//      for (part = 0; part < n−1; part++) 
//            Compute force(part, forces, . . .)
// }

//initialization
// for each particle q {
// 		pos[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
// 		pos[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
// 		pos[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

// 		old_pos[i][X] = pos[q][X];
// 		old_pos[i][Y] = pos[q][Y];
// 		old_pos[i][Z] = pos[q][Z];

// 		vel[q][X] = (rand() / (double)(RAND_MAX)) * 2 - 1;
// 		vel[q][Y] = (rand() / (double)(RAND_MAX)) * 2 - 1;
// 		vel[q][Z] = (rand() / (double)(RAND_MAX)) * 2 - 1;

// 		mass[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
// 	}