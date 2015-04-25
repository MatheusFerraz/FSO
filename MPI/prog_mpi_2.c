/* Nesse exemplo, o primeiro processo envia uma mensagem
 * em broadcast para os restantes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int size, rank, msg, source, dest, tag;
 
int main(int argc, char *argv[]){
   MPI_Status stat;
 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
 
	if(rank == 0)
	{
   		msg = 42; dest = 1; tag = 0;	
		MPI_Bcast (&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);	
	} else {
		MPI_Bcast (&msg, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Processo %d recebeu a mensagem - %d.\n",rank,msg);
	}
	
   MPI_Finalize();
}