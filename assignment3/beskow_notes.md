# get ticket:
kinit --forwardable YourUsername@NADA.KTH.SE

# loggin:
ssh YourUsername@beskow.pdc.kth.s

# copy files:

# compile
cc main.c -O2 -o main.out
cc hello.c -O2 -o hello.out

cc main.c -O2 -o main.out -lm 
cc main.c -O2 -o main.out

# complile local
mpicc hello.c -o hello

mpicc main.c -o main -lm

# get info
projinfo

# get allocation 
salloc --nodes=1 -t 00:05:00 -A edu20.dd2356 -C Haswell
salloc --nodes=4 -t 00:05:00 -A edu20.dd2356 -C Haswell

# run code
srun -n 4 ./main.out
srun -n 4 ./hello.out

# run code local
mpiexec -n 2 ./hello

mpiexec -n 2 ./main

# Module list
module list

# Switch to MPI module
module swap cray-mpich/7.7.8

# Ping Pong

cc ping_pong.c -o ping_pong
# Out-of-Node
salloc --nodes=2 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 --ntasks-per-node=1 ./ping_pong
# On-Node
salloc --nodes=1 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 ./ping_pong
