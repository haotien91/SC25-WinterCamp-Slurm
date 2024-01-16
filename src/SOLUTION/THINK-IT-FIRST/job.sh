#!/bin/bash

#SBATCH -J pi-mt-Intel-OMPI    # Job Name
#SBATCH -o mt_iompi_%j_out.log # Redirect `stdout` to File
#SBATCH -e mt_iompi_%j_err.log # Redirect `stderr` to File

#SBATCH -n 1000                # `--ntasks`, number of tasks / MPI ranks / processes

ml purge
ml compiler/intel/2021 OpenMPI/4.1.0

make clean && make

echo "Calculat $\pi$ by Monte Carlo method!!"
for n in 1000000 1000000000 1000000000000
do
    printf "\tN=$n\n"
    time srun ./monte-carlo.run $n
done


 echo "Calculat $\pi$ by Integral method!!"
 for n in 1000000 1000000000 1000000000000
 do
     printf "\tN=$n\n"
     time srun ./integral.run $n
 done

