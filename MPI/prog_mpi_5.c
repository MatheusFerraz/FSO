#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include "BasicLibrary.h"

#define MASTER_PROCESS_RANK 0
#define SLAVE_PROCESS_RANK 1
#define TAG 0

// Prototypes
void master_process(void);

void slave_process(void);

int process_rank, print_code;

int main(int argc, char **argv)
{
	void (*procedures[])(void) = {master_process, slave_process};

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

	(*procedures[process_rank])();

	printf("\n");

	MPI_Finalize();

	return 0;
}

void master_process(void)
{
	print_code = 1;

	printf("Processo Mestre iniciou sua execucao.\n");

	MPI_Send(&print_code, 1, MPI_INT, SLAVE_PROCESS_RANK, TAG, MPI_COMM_WORLD);

	printf("Processo Mestre enviou o codigo de impressao para Processo Escravo.\n\n");
}

void slave_process(void)
{
	FILE *entry_file;
	MPI_Status status;
	char file_name[] = "file_in.txt";

	printf("Processo Escravo iniciou sua execucao.\n");

	MPI_Recv(&print_code, 1, MPI_INT, MASTER_PROCESS_RANK, TAG, MPI_COMM_WORLD, &status);

	printf("Processo Escravo recebeu codigo de impressao do Processo Mestre.\n\n");
	printf("Conteudo do arquivo:\n");

	if(print_code == 1)
	{
		if(!(entry_file = fopen(file_name, "r")))
		{
			perror("Arquivo informado nao localizado.\n");
		} else {
			print_file_content(entry_file);
		}
	} else if(print_code == 0) {
		printf("O Processo Mestre nao autorizou impressao do conteudo do arquivo.\n");
	} else {
		printf("Nao foi enviado um codigo de impressao valido.\n");
	}
}