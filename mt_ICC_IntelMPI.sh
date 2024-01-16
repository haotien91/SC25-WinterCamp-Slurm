#!/bin/bash

#SBATCH -J pi-mt-IntelMPI      # Job Name
#SBATCH -A GOV111082           # Account
#SBATCH -o mt_impi_%j_out.log  # Redirect `stdout` to File
#SBATCH -e mt_impi_%j_err.log  # Redirect `stderr` to File

#SBATCH -n 1000                # `--ntasks`, number of tasks / MPI ranks / processes

ml purge
ml compiler/intel/2022 IntelMPI

echo "Build the binaries!!"
BUILD=build/icc_impi
make all CC=$MPICC
cd $BUILD

export UCX_NET_DEVICES=all # The UCX config of the module is incorrect!! We have to fix it manually.

echo "Calculat $\pi$ by Monte Carlo method!!"
for n in 1000000 1000000000 1000000000000
do
    printf "\tN=$n\n"
    time mpirun ./pi_monte_carlo $n
    # time mpiexec.hydra -bootstrap slurm ./pi_monte_carlo $n
done
