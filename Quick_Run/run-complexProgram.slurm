#!/bin/bash

#SBATCH --job-name=complexProgram           # Job name
#SBATCH --output=outputcomplexProgram.out   # Output file name
#SBATCH --error=errorcomplexProgram.err     # Error file name
#SBATCH --cluster=chip-cpu                  # Cluster
#SBATCH --account=pi_userid                 # Account
#SBATCH --partition=2021.                   # Partition
#SBATCH --qos=short                         # Queue
#SBATCH --time=00:05:00                     # Time limit
#SBATCH --nodes=1                           # Number of nodes
#SBATCH --ntasks-per-node=1                 # MPI processes per node
#SBATCH --mem=4G                            # Memory per node

module load intel/2024a
./complexProgram
