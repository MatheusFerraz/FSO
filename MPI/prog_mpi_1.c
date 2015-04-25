/* Nesse programa, o primeiro processo envia uma mensagem
 * ponto a ponto para os restantes.
 * Para compilar, usa-se <mpicc "codigo_fonte.c" -o "executavel">.
 * Para executar, <mpirun -np "nº" "executável">.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int size, rank, msg, source, dest, tag;
 
int main(int argc, char *argv[])
{
   MPI_Status stat;
 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 
	if(rank == 0)
	{
   		msg = 42; dest = 1; tag = 0;
	
		int i;
		for (i = 1;i < size;i ++)
		{
	   		MPI_Send(&msg, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
	   		printf("Processo %d enviou %d para %d.\n", rank, msg, i);
		}	
	}
 
	if(rank != 0){
		source = 0; tag = 0;
		
		MPI_Recv(&msg, 1, MPI_INT, source, tag, MPI_COMM_WORLD, &stat);
		printf("Processo %d recebeu %d de %d.\n", rank, msg, source);
	}
 
   MPI_Finalize();
}