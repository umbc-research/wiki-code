#!/bin/bash

#SBATCH --job-name=hello_parallel       # Job name
#SBATCH --output=slurm.out              # Output file name
#SBATCH --error=slurm.err               # Error file name
#SBATCH --cluster=chip-cpu              # Cluster
#SBATCH --account=pi_userid             # Account
#SBATCH --partition=general             # Partition
#SBATCH --qos=short                     # Queue
#SBATCH --time=00:05:00                 # Time limit
#SBATCH --nodes=2                       # Number of nodes
#SBATCH --ntasks-per-node=4             # MPI processes per node
#SBATCH --mem=4G                        # Memory per node

module load intel/2024a
unset I_MPI_PMI_LIBRARY
export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
mpirun -print-rank-map ./hello_parallel
