export OMP_NUM_THREADS=1
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=2
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=4
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=8
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=12
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=16
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=20
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=24
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=28
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=32
gcc -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=4