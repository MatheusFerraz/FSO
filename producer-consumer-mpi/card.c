#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
#define CHARACTERS_PER_ROW 80

/************************* Public Functions *************************/

/**
 * Generates a new card with random valid characters as content.
 * parameters: name of the new card and its number of lines
 * return: the brand new card
 */
FILE* generate_card(const char * const card_name, const int number_of_lines) {
	FILE* new_card;
	char generate_random_character(void);
	void generate_new_seed(void);
	generate_new_seed();
	if(new_card = fopen(card_name, "w+")) {
	  int i, j;
	  char character;
	  for(i = 0; i < number_of_lines; i++) {
      for(j = 0; j < CHARACTERS_PER_ROW; j++) {
	      character = generate_random_character();
	      fputc(character, new_card);
      }
      fputc('\n', new_card);
	  }
	} else {
		perror("Card coult not be created: ");
	}

	printf("A new card has been created!\n");

	rewind(new_card);

	return new_card;
}

/**
 * Fills an array of strings responsible to store the name of multiple cards.
 * The names follow the pattern 'card<nº>.txt' (e.g. card3.txt for the third card).
 * parameters: the array of strings that will store the name of the cards and the number of cards
 * return: none
 */
char** generate_cards_names(const int number_of_cards) {
	int i;
	char** cards_names = calloc(number_of_cards, sizeof(char *));
	char file_number[4];
	char file_name[8] = "card";
	const int name_length = 15;
	for(i = 0; i < number_of_cards; i++) {
		cards_names[i] = calloc(name_length, sizeof(char));
		sprintf(file_number, "%d", i);
		strcat(file_name, file_number);
		strcpy(cards_names[i], strcat(file_name, ".txt"));
		file_name[4] = '\0';
	}

	for(i = 0; i < number_of_cards; i++) {
		printf("Generated %dº card name: %s\n", i + 1, cards_names[i]);
	}
	printf("finished generating cards\n");
	return cards_names;
}

/**
 * Read the contents of a file and stores it in a string.
 * parameters: the card to be read
 * return: a string storing the contents of the file that has been read
 */
char* read_card(FILE* card) {
	size_t get_file_size(FILE*);
	char* file_content = calloc((int) get_file_size(card) + 1, sizeof(char));
	char character;
	int i = 0;
	while((character = fgetc(card)) != EOF) {
		file_content[i++] = character;
	}
	file_content[i] = '\0';
	return file_content;
}

/**
 * Add new content to a file. It has as restriction replace any 
 * couple of '*' found to '#'.
 * parameters: the card to be written and the message with the new content
 * return: none
 */
void write_card(FILE* card, const char * const message) {
	int i = 0, count_asterisks = 0, word_count = 0;
	char character;

	printf("\n\nMessage that will be written\n\n%s\n\n", message);

	while(character = message[i++]) {
		if(character == '\n') {
			count_asterisks = 0;
			continue;
		}

		fputc(character, card);
		word_count++;
		if(character == '*') {
			if(count_asterisks == 1) {
				fseek(card, -2, SEEK_CUR);
				fputc('#', card);
				word_count--;
				count_asterisks = 0;
			} else {
				count_asterisks++;
			}
		} else {
			count_asterisks = 0;
		}

		if((word_count % 125) == 0) {
			fputc('\n', card);
		}
	}

	fputc(' ', card);
	printf("Content has been added to the output file!\n");
}


/************************* Private Functions *************************/

size_t get_file_size(FILE* file) {
	size_t file_size;
	fseek(file, 0L, SEEK_END);
	file_size = ftell(file);
	fseek(file, 0L, SEEK_SET);
	return file_size;
}

/**
 * Generates a random valid character. It has more or less 10% of chance 
 * of generate '*' characters in function of the context of the project.
 * parameters: none
 * return: a random character
 */
char generate_random_character(void) {
	char random_character = 33 + rand() % 94;
	random_character = random_character > 80 ? '*' : random_character;
	return random_character == '#' ? generate_random_character() : random_character;
}
 
void generate_new_seed(void) {
	srand((int) time(NULL));
}