cc main6.c -O2 -o main6.out
srun -n 8 ./main6.out
srun -n 16 ./main6.out
srun -n 32 ./main6.out
srun -n 64 ./main6.out
srun -n 128 ./main6.out
