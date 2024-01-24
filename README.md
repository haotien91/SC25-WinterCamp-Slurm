## Hands-on Lab

1. Scalability Test.
   * Set TRIES to 100,000 and measure the performance with different numbers of processes multiple times. Then, use Google Sheets to create a Scalability chart.
   ```bash
   #!/bin/bash
   #PBS -N pi-mt-Intel-OMPI
   #PBS -P ACD110018
   #PBS -q cf160
   #PBS -o out.log
   #PBS -e err.log
   #PBS -l mpiprocs=$(TRY_IT_YOURSELF!)

   # Please set TRIES to 100,000 and experiment with different numbers of processes (NUM_OF_PROCS).
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
   * Keep the number of processes constant at 1000, and vary the number of TRIES. Then, create a graph to show how the error changes with different TRIES values.
   ```bash
   #!/bin/bash
   #PBS -N pi-mt-Intel-OMPI
   #PBS -P ACD110018
   #PBS -q cf160
   #PBS -o out.log
   #PBS -e err.log
   #PBS -l mpiprocs=1000

   # Please set NUM_OF_PROCS to 1000 and experiment with various values for TRIES.
   NUM_OF_PROCS=1000
   TRIES=$(TRY_IT_YOURSELF!)

   module purge
   module load gcc/9.3.0
   module load mpi/openmpi-4.0.5/gcc930

   make clean && make

   echo "Calculat pi by Monte Carlo method with 100000 tries!!"

   time mpirun --mca btl ^openib -np $NUM_OF_PROCS /home/tim911004/SC25-WinterCamp-Lab/mpi-monte-carlo $TRIES

   ```
