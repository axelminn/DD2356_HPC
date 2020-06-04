cc main.c -O2 -o main.out
srun -n 8 ./main.out
srun -n 16 ./main.out
srun -n 32 ./main.out
srun -n 64 ./main.out
srun -n 128 ./main.out
