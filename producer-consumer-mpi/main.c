#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "mpi.h"
#include "card.h"

#define MESSAGE_DATA 0
#define PRODUCER_RANK 0
#define CONSUMER_RANK 1
#define BUFFER_MAX_SIZE 100000

void producer(void);

void consumer(void);

int number_of_cards = 4, rank;

int main(int argc, char** argv) {
	void (*routines[])(void) = {producer, consumer};

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	(*routines[rank])();

	MPI_Finalize();

	return 0;
}

void producer(void) {
	FILE** cards;
	char** cards_names;
	char* buffer;
	int i, j;

	printf("Producer started its execution rank: %d. . .\n", rank);

	cards = calloc(number_of_cards, sizeof(FILE *));

	char card_number[3];
	char card_name[15] = "card";
	for(i = 0; i < number_of_cards; i++) {
		// generates cards with 3 to 9 lines
		sprintf(card_number, "%d", i);
		strcat(card_name, card_number);
		strcat(card_name, ".txt");
		cards[i] = generate_card(card_name, 3 + rand() % 7);
		buffer = read_card(cards[i]);
		j = 0;
		while(buffer[j]) {
			// printf("Producer sent %c\n", buffer[j]);
			MPI_Send(&buffer[j], 1, MPI_CHAR, CONSUMER_RANK, 0, MPI_COMM_WORLD);
			j++;
		}
		MPI_Send(&buffer[j], 1, MPI_CHAR, CONSUMER_RANK, MESSAGE_DATA, MPI_COMM_WORLD); // sending '\0' character
		printf("Producer(%d): A card has been sent!\n", getpid());
		card_name[4] = '\0';
	}

}

void consumer(void) {
	int i, j;
	char* buffer = calloc(BUFFER_MAX_SIZE, sizeof(char));
	FILE* output_file;

	if(!(output_file = fopen("output.txt", "w+"))) {
		perror("Output file could not be open. ");
	}

	printf("Consumer started its execution rank: %d. . .\n", rank);

	for(i = 0; i < number_of_cards; i++) {
		j = 0;
		do {
			MPI_Recv(&buffer[j], 1, MPI_CHAR, PRODUCER_RANK, MESSAGE_DATA, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// printf("Consumer received %c\n", buffer[j]);
		} while(buffer[j++]);
		buffer[j] = '\0';
		printf("Consumer(%d): A card has been received!\n", getpid());
		write_card(output_file, buffer);
	}
	
	free(buffer);
}

