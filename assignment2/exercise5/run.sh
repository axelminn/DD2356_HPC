gcc -lm -Wall -O2 -fopenmp -o main.out main.c
./main.out 
./main.out 
./main.out 
./main.out 
./main.out 
perf stat -e instructions,cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads,dTLB-load-misses,dTLB-loads ./main.out