cc main4.c -O2 -o main4.out
srun -n 8 ./main4.out
srun -n 16 ./main4.out
srun -n 32 ./main4.out
srun -n 64 ./main4.out
srun -n 128 ./main4.out
