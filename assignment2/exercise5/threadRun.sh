export OMP_NUM_THREADS=1
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=4
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=8
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=12
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=16
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=20
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=24
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=28
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=32
gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out
export OMP_NUM_THREADS=4
