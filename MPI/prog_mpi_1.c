/* Nesse programa, o primeiro processo envia uma mensagem
 * ponto a ponto para os restantes.
 * Para compilar, usa-se <mpicc "codigo_fonte.c" -o "executavel">.
 * Para executar, <mpirun -np "nº" "executável">.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int communicator_size, process_rank, message, source, destination, tag;
 
int main(int argc, char *argv[])
{
   MPI_Status status;
 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&communicator_size);
   MPI_Comm_rank(MPI_COMM_WORLD,&process_rank);
 
	if(process_rank == 0)
	{
   		message = 42; destination = 1; tag = 0;
	
		int i;
		for (i = 1;i < communicator_size;i ++)
		{
	   		MPI_Send(&message, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
	   		printf("Processo %d enviou %d para %d.\n", process_rank, message, i);
		}	
	}
 
	if(process_rank != 0)
	{
		source = 0; tag = 0;
		
		MPI_Recv(&message, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
		printf("Processo %d recebeu %d de %d.\n", process_rank, message, source);
	}
 
   MPI_Finalize();
}