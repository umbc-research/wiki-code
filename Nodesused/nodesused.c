#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>
#include <sched.h>

#ifdef _OPENMP
#include <omp.h>
#endif

void nodesused (void)
{
  int id, np;
  char name[MPI_MAX_PROCESSOR_NAME];
  int namelen;
  int sys_status;
  int j;
  MPI_Status status;
  char message[128];
  FILE *fil, *fil_threads;
  char filename[128], filename_threads[128];

  MPI_Comm_size (MPI_COMM_WORLD, &np);
  MPI_Comm_rank (MPI_COMM_WORLD, &id);
  MPI_Get_processor_name (name, &namelen);

  /* classical nodesused output with hostnames only: */
  sprintf(message, "MPI process %04d of %04d on node %4s", id, np, name);
  if (id == 0) {
    sprintf (filename, "nodesused.log");
    fil = fopen (filename, "w");
    if (fil == NULL)
    {
      fprintf (stderr, "nodesused: problem opening file %s\n", filename);
      MPI_Abort(MPI_COMM_WORLD, 1);
    }
    fprintf(fil, "%s\n", message);
    for (j = 1; j < np; j++) {
        MPI_Recv(message, 128, MPI_CHAR, j, 0, MPI_COMM_WORLD, &status);
        fprintf(fil, "%s\n", message);
    }
    fflush (fil);
    fclose (fil);
  } else {
      MPI_Send(message, strlen(message)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
  }
  /* nodesused output with cpu ids: */
  sprintf (filename, "nodesused-%04d.log", id);
  fil = fopen (filename, "w");
  if (fil == NULL)
  {
    fprintf (stderr, "nodesused: problem opening file %s\n", filename);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  fprintf(fil, "MPI process %04d of %04d on cpu_id %04d of node %4s\n",
  id, np, sched_getcpu(), name);
  MPI_Barrier(MPI_COMM_WORLD);
  fflush (fil);
  fclose (fil);
  /* combine all files nodesused-????.log to nodesused_cpuid.log: */
  MPI_Barrier(MPI_COMM_WORLD);
  if (id == 0) {
    sys_status = system ("sort -n nodesused-????.log > nodesused_cpuid.log");
    if (sys_status == -1)
      fprintf (stderr, "nodesused: problem with 'system' call\n");  
    fflush (stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  if (id == 0) {
    sys_status = system ("rm nodesused-????.log");
    if (sys_status == -1)
      fprintf (stderr, "nodesused: problem with 'system' call\n");  
    fflush (stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);
#ifdef _OPENMP
  sprintf (filename_threads, "nodesused_threads-%04d.log", id);
  fil_threads = fopen(filename_threads, "w");
  if(fil_threads == NULL)
  {
    fprintf (stderr, "nodesused: problem opening file %s\n", filename_threads);
    MPI_Abort(MPI_COMM_WORLD, 1);
  }
  #pragma omp parallel
  {
    fprintf(fil_threads,
    "MPI process %04d of %04d thread %04d of %04d on cpu_id %04d of node %4s\n",
    id, np, omp_get_thread_num(), omp_get_num_threads(),
    sched_getcpu(), name);
  }
  #pragma omp barrier
  fflush (fil_threads);
  fclose (fil_threads);
  /* combine all files nodesused_threads-????.log to nodesused_threads.log: */
  MPI_Barrier(MPI_COMM_WORLD);
  if (id == 0) {
    sys_status
      = system ("sort -n nodesused_threads-????.log > nodesused_threads.log");
    if (sys_status == -1)
      fprintf (stderr, "nodesused: problem with 'system' call\n");
    fflush (stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);
  if (id == 0) {
    sys_status = system ("rm nodesused_threads-????.log");
    if (sys_status == -1)
      fprintf (stderr, "nodesused: problem with 'system' call\n");
    fflush (stdout);
  }
  MPI_Barrier(MPI_COMM_WORLD);
#endif
}

int main (int argc, char *argv[])
{
    int id, np;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int processor_name_len;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Get_processor_name(processor_name, &processor_name_len);

    printf("Hello world from process %04d out of %04d, processor name %s\n",
        id, np, processor_name);

    nodesused();

    MPI_Finalize();
    return 0;
}

