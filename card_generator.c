#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER_OF_ROWS 80

FILE* generate_card(const char * const file_name, const int number_of_lines) {
	FILE* new_card;
	char generate_random_character(void);
	void generate_new_seed(void);
	generate_new_seed();
	if(new_card = fopen(file_name, "w")) {
		int i, j;
		char character;
		for(i = 0; i < number_of_lines; i++) {
			for(j = 0; j < NUMBER_OF_ROWS; j++) {
				character = generate_random_character();
				fputc(character, new_card);
			}
			fputc('\n', new_card);
		}
	} else {
		perror("Card coult not be created: ");
	}
	return new_card;
}

char generate_random_character(void) {
	char random_character = 33 + rand() % 94;
	return random_character;
}

void generate_new_seed(void) {
	srand((int) time(NULL));
}