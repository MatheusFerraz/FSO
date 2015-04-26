// Programa que indica o local da execuçao das tarefas.

#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{
   int  tasks_number, process_rank, processor_name, call_result; 
   char hostname[MPI_MAX_PROCESSOR_NAME];

   call_result = MPI_Init(&argc,&argv);

   if (call_result != MPI_SUCCESS) 
   {
     printf ("Erro ao iniciar o programa MPI. Terminando.\n");
     MPI_Abort(MPI_COMM_WORLD, call_result);
   }

   MPI_Comm_size(MPI_COMM_WORLD, &tasks_number);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Get_processor_name(hostname, &processor_name);
   
   printf ("Numero de tarefas = %d. Posicao = %d.  Executando em: %s.\n", tasks_number, process_rank, hostname);

   MPI_Finalize();
}