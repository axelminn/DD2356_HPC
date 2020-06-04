# get ticket:
kinit --forwardable YourUsername@NADA.KTH.SE

# loggin:
ssh YourUsername@beskow.pdc.kth.s

# copy files:
scp main.c axellaru@beskow.pdc.kth.se:
scp hello.c axellaru@beskow.pdc.kth.se:

scp main.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp main2.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run2.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp main3.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run3.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp main4.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run4.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp main5.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run5.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp main6.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2
scp run6.sh axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise2

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
Project info for all projects for user: axellaru
If usage of specific users is not listed, then that user has not been executing job within this time period
Last update: Thu May 21 17:04:56 2020
Information for project: edu20.dd2356
Methods in HPC
Active from 2020-03-13 00:00:00 to 2020-06-30 00:00:00
beskow: 10000 corehours/month, used 215.46% (21545 corehours) during the past 30 days

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
scp ping_pong.c axellaru@beskow.pdc.kth.se:/cfs/klemming/scratch/a/axellaru/exercise3

cc ping_pong.c -o ping_pong
# Out-of-Node
salloc --nodes=2 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 --ntasks-per-node=1 ./ping_pong
# On-Node
salloc --nodes=1 -t 00:10:00 -A edu20.dd2356 -C Haswell
srun -n 2 ./ping_pong