// Programa para exibiçao de mensagem definida em uma string.

#include <stdio.h>
#include <string.h>
#include <mpi.h>

main(int argc, char *argv[])
{
	int process_rank, communicator_size, source, destination;
	int tag = 0;
	char word[] = "MENSAGEM";

	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &communicator_size);

	if(process_rank != 0)
	{
		printf("Processo %d esta vivo.\n",process_rank);
		destination = 0;
		MPI_Send(word, strlen(word)+1, MPI_CHAR, destination, tag, MPI_COMM_WORLD);
	} else {
		for(source = 1; source < communicator_size; source ++) {
			MPI_Recv(word, 15, MPI_CHAR, source, tag, MPI_COMM_WORLD, &status);
			printf("Palavra passada: %s.\n",word);
		}
	}

	MPI_Finalize();
}