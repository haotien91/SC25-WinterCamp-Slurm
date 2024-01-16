#!/bin/bash

#SBATCH -J pi-mt-Intel-OMPI    # Job Name
#SBATCH -A GOV111082           # Account
#SBATCH -o mt_iompi_%j_out.log # Redirect `stdout` to File
#SBATCH -e mt_iompi_%j_err.log # Redirect `stderr` to File

#SBATCH -n 1000                # `--ntasks`, number of tasks / MPI ranks / processes

ml purge
ml compiler/intel/2021 OpenMPI/4.1.0

echo "Build the binaries!!"
BUILD=build/icc_ompi
LC_ALL=C make all # It seems that for `icc` and Intel MPI, we have to set locale properly.
cd $BUILD

echo "Calculat $\pi$ by Monte Carlo method!!"
for n in 1000000 1000000000 1000000000000
do
    printf "\tN=$n\n"
    time srun ./pi_monte_carlo $n
done
