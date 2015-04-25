/* Nesse exemplo, o primeiro processo envia uma mensagem
 * em broadcast para os restantes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int communicator_size, process_rank, message, source, destination, tag;
 
int main(int argc, char *argv[]){
   MPI_Status status;
 
   MPI_Init(&argc,&argv);
   MPI_Comm_size(MPI_COMM_WORLD,&communicator_size);
   MPI_Comm_rank(MPI_COMM_WORLD,&process_rank);
 
	if(process_rank == 0)
	{
   		message = 42; destination = 1; tag = 0;	
		MPI_Bcast (&message, 1, MPI_INT, 0, MPI_COMM_WORLD);	
	} else {
		MPI_Bcast (&message, 1, MPI_INT, 0, MPI_COMM_WORLD);
		printf("Processo %d recebeu a mensagem - %d.\n",process_rank,message);
	}
	
   MPI_Finalize();
}