cc main2.c -O2 -o main2.out
srun -n 8 ./main2.out
srun -n 16 ./main2.out
srun -n 32 ./main2.out
srun -n 64 ./main2.out
srun -n 128 ./main2.out
