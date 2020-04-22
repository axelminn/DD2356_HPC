export OMP_NUM_THREADS=1
gcc -fopenmp stream.c
./a.out > test1.txt
export OMP_NUM_THREADS=2
gcc -fopenmp stream.c
./a.out > test2.txt
export OMP_NUM_THREADS=4
gcc -fopenmp stream.c
./a.out > test4.txt
export OMP_NUM_THREADS=8
gcc -fopenmp stream.c
./a.out > test8.txt
export OMP_NUM_THREADS=12
gcc -fopenmp stream.c
./a.out > test12.txt
export OMP_NUM_THREADS=16
gcc -fopenmp stream.c
./a.out > test16.txt
export OMP_NUM_THREADS=20
gcc -fopenmp stream.c
./a.out > test20.txt
export OMP_NUM_THREADS=24
gcc -fopenmp stream.c
./a.out > test24.txt
export OMP_NUM_THREADS=28
gcc -fopenmp stream.c
./a.out > test28.txt
export OMP_NUM_THREADS=32
gcc -fopenmp stream.c
./a.out > test32.txt
export OMP_NUM_THREADS=4

