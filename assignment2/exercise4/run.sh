export OMP_NUM_THREADS=1
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test1.txt
export OMP_NUM_THREADS=2
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test2.txt
export OMP_NUM_THREADS=4
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test4.txt
export OMP_NUM_THREADS=8
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test8.txt
export OMP_NUM_THREADS=12
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test12.txt
export OMP_NUM_THREADS=16
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test16.txt
export OMP_NUM_THREADS=20
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test20.txt
export OMP_NUM_THREADS=24
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test24.txt
export OMP_NUM_THREADS=28
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test28.txt
export OMP_NUM_THREADS=32
gcc -lm -Wall -O2 -fopenmp -o DFTW DFTW.c
./DFTW > test32.txt
export OMP_NUM_THREADS=4