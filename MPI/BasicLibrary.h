// Functions and Procedures to manipulate files using MPI

// Print file content
void print_file_content(FILE *file) {
	char character;
	character = fgetc(file);
	while(character != EOF) 
	{
		printf("%c",character);
		character = fgetc(file);
	}
}