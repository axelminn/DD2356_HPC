cc main3.c -O2 -o main3.out
srun -n 8 ./main3.out
srun -n 16 ./main3.out
srun -n 32 ./main3.out
srun -n 64 ./main3.out
srun -n 128 ./main3.out
