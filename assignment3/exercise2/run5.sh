cc main5.c -O2 -o main5.out
srun -n 8 ./main5.out
srun -n 16 ./main5.out
srun -n 32 ./main5.out
srun -n 64 ./main5.out
srun -n 128 ./main5.out
