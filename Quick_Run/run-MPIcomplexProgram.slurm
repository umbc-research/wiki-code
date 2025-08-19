#!/bin/bash

#SBATCH --job-name=MPIcomplexProgram            # Job name
#SBATCH --output=outputMPIcomplexProgram.out    # Output file name
#SBATCH --error=errorMPIcomplexProgram.err      # Error file name
#SBATCH --cluster=chip-cpu                      # Cluster
#SBATCH --account=pi_userid                     # Account
#SBATCH --partition=2021                        # Partition
#SBATCH --qos=short                             # Queue
#SBATCH --time=00:05:00                         # Time limit
#SBATCH --nodes=2                               # Number of nodes
#SBATCH --ntasks-per-node=1                     # MPI processes per node
#SBATCH --mem=4G                                # Memory per node

module load intel/2024a
unset I_MPI_PMI_LIBRARY
export I_MPI_JOB_RESPECT_PROCESS_PLACEMENT=0
mpirun ./MPIcomplexProgram
