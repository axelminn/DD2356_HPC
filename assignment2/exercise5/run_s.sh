gcc -lm -Wall -O2 -fopenmp -o serial main_serial.c
./serial
./serial 
./serial 
./serial 
./serial 
perf stat -e instructions,cache-misses,cache-references,L1-dcache-load-misses,L1-dcache-loads,LLC-load-misses,LLC-loads,dTLB-load-misses,dTLB-loads ./serial