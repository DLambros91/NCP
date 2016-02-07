#include <stdio.h>

int main(int argc, char ** argv)
{
	/* Check if the minimum required amount of arguments have been supplied. */
	if (argc < 3)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return 0;
	}
	else
	{
		FILE * file = fopen(argv[1], "r");
		if (file != NULL)
		{
			fclose(file);
			return 0;
		}
		else
		{
			/* Inform the user that the file does not exist. */
			fprintf(stderr, "File does not exist\n");
			return 0;
		}
	}
}
