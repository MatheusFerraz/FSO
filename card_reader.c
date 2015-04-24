#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card_generator.h"

void generate_card_names(char** card_names, const int number_of_cards);

int main(int argc, char** argv) {
	int number_of_cards;
	char** card_names;
	int i;
	const int number_of_lines = 10;
	// Identifies if the number of line arguments is correct
	if(!(argc == 2 && argv[1][0] <= '9' && argv[1][0] >= '0')) {
		fprintf(stderr, "The number of cards to be generated was not specified. System will now exit. . .\n");
		exit(EXIT_FAILURE);
	}

	number_of_cards = atoi(argv[1]);

	card_names = calloc(number_of_cards, sizeof(char *));

	generate_card_names(card_names, number_of_cards);
	
	for(i = 0; i < number_of_cards; i++) {
		generate_card(card_names[i], number_of_lines);
	}
	
	return 0;
}

void generate_card_names(char** card_names, const int number_of_cards) {
	int i;
	const int name_length = 10;

	for(i = 0; i < number_of_cards; i++) {
		printf("generating %dº card name\n", i + 1);
		card_names[i] = calloc(name_length, sizeof(char));
		strcpy(*(card_names + i), "testi.txt");
		card_names[i][4] = i + '0';
	}
}