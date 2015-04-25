#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "card_generator.h"

void generate_card_names(char** card_names, const int number_of_cards);

FILE* read_cards(FILE** cards, const int number_of_cards);

int main(int argc, char** argv) {
	int number_of_cards;
	char** card_names;
	FILE** cards;
	int i;
	const int number_of_lines = 10;
	// Identifies if the number of line arguments is correct
	if(!(argc == 2 && argv[1][0] <= '9' && argv[1][0] >= '0')) {
		fprintf(stderr, "The number of cards to be generated was not specified. System will now exit. . .\n");
		exit(EXIT_FAILURE);
	}

	number_of_cards = atoi(argv[1]);

	card_names = calloc(number_of_cards, sizeof(char *));

	cards = calloc(number_of_cards, sizeof(FILE *));

	generate_card_names(card_names, number_of_cards);
	
	for(i = 0; i < number_of_cards; i++) {
		printf("generating %dº card\n", i + 1);
		cards[i] = generate_card(card_names[i], number_of_lines);
		rewind(cards[i]);
	}

	read_cards(cards, number_of_cards);

	for(i = 0; i < number_of_cards; i++) {
		fclose(cards[i]);
	}

	return 0;
}

void generate_card_names(char** card_names, const int number_of_cards) {
	int i;
	const int name_length = 10;

	for(i = 0; i < number_of_cards; i++) {
		card_names[i] = calloc(name_length, sizeof(char));
		strcpy(*(card_names + i), "testi.txt");
		card_names[i][4] = i + '0';
	}
}

FILE* read_cards(FILE** cards, const int number_of_cards) {
	int i, count_asterisks = 0;
	char character;
	FILE* output_file = fopen("output.txt", "w+");
	for(i = 0; i < number_of_cards; i++) {
		while((character = fgetc(cards[i])) != EOF) {
			fputc(character, output_file);
			if(character == '*') {
				if(count_asterisks == 1) {
					fseek(output_file, -2, SEEK_CUR);
					fputc('#', output_file);
					count_asterisks = 0;
				} else {
					count_asterisks++;
				}
			} else {
				count_asterisks = 0;
			}
		}
		printf("hey, finished a card\n");
		fputc(' ', output_file);
	}
	return output_file;
}
