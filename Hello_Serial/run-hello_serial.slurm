#!/bin/bash

#SBATCH --job-name=hello_serial         # Job name
#SBATCH --output=slurm.out              # Output file name
#SBATCH --error=slurm.err               # Error file name
#SBATCH --cluster=chip-cpu              # Requesting a job on chip CPU cluster
#SBATCH --partition=general             # Partition
#SBATCH --qos=short                     # Queue
#SBATCH --time=00:05:00                 # Time limit 
#SBATCH --mem=4G                        # Memory requested
#SBATCH --nodes=1                       # Number of nodes
#SBATCH --ntasks-per-node=1             # MPI processes per node

./hello_serial

