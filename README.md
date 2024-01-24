# SC24 Training Camp - Pi simulator

## Hands-on Lab

1. Scalability Test.
   * 固定TRIES=100000，用不同行程數測量多次並用Google試算表繪製出Scalability圖。
   ```bash
   #!/bin/bash
   #PBS -N pi-mt-Intel-OMPI
   #PBS -P ACD110018
   #PBS -q cf160
   #PBS -o out.log
   #PBS -e err.log
   #PBS -l mpiprocs=$(TRY_IT_YOURSELF!)

   # Please fix TRIES to 100000 and try different $NUM_OF_PROCS.
   NUM_OF_PROCS=$(TRY_IT_YOURSELF!)
   TRIES=100000

   module purge
   module load gcc/9.3.0
   module load mpi/openmpi-4.0.5/gcc930

   make clean && make

   echo "Calculat pi by Monte Carlo method with 100000 tries!!"

   time mpirun --mca btl ^openib -np $NUM_OF_PROCS /home/tim911004/SC25-WinterCamp-Lab/mpi-monte-carlo $TRIES

   ```


2. Error Test.
   * 固定行程數=1000，調整不同的TRIES數，作誤差對TRIES數的圖。
   ```bash
   #!/bin/bash
   #PBS -N pi-mt-Intel-OMPI
   #PBS -P ACD110018
   #PBS -q cf160
   #PBS -o out.log
   #PBS -e err.log
   #PBS -l mpiprocs=1000

   # Please fix NUM_OF_PROCS to 1000 and try different TRIES.
   NUM_OF_PROCS=1000
   TRIES=100000

   module purge
   module load gcc/9.3.0
   module load mpi/openmpi-4.0.5/gcc930

   make clean && make

   echo "Calculat pi by Monte Carlo method with 100000 tries!!"

   time mpirun --mca btl ^openib -np $NUM_OF_PROCS /home/tim911004/SC25-WinterCamp-Lab/mpi-monte-carlo $TRIES

   ```
