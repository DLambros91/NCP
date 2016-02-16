#include <stdio.h>
#include "alerts.h"
#include <string.h>
#include <ctype.h>
#include <strings.h>

/* Define true and false to be the values 1 and 0, respectively. */
#define true  1
#define false 0

/* Name: Demetrios Lambropoulos
   Date: Monday, February 1, 2016
  
   */

int isBinary(FILE * file);

int main(int argc, char ** argv)
{
	/* Check if the minimum require3 amount of arguments hav3 been supplied. */
	if (argc < 3)
	{
		/* Inform the user that not enough arguments have been provided.  */
		error("Not enough arguments.");
	
		/* Exit the program */
		return 0;
	}
	else
	{
		/* Open the requested file. */
		FILE * file = fopen(argv[1], "r");
		
		/* Indicates the number of substrings to search for. */
		int i = argc - 2;
		
		/* Indicates the current substring argument. */
		int cur = 2;

		/* Check that the requested file is existing. */
		if (file != NULL)
		{
			/* Check if the file is a binary. */
			if(isBinary(file))
			{
				/* Provide a warning to the user that this might cause errors. */
				warning("File is a binary. Might result with incorrect results.");
			}			
			
			/* While there is still more substrings. Search for occurrances. */
			while(i != 0)
			{
				/* Current substring to look for. */
				char * substring = argv[cur];
				
				/* Size of the substring. */
				int size = strlen(substring);

				/* Chunk of file equal to the length of the substring. */
				char c[size];

				/* The amount of matches that were detected. */
				int matches = 0;

				/* Current cursor in the file */
				int cursor = 1;

				/* While the file is not EOF, continue looking for matches. */
				while (fgets(c, size + 1, file) != NULL)
				{
					/* Compare if the two character arrays match, disregarding case. */
					if (strcasecmp(c, substring) == 0)
					{
						/* Increment the amount of matches. */
						matches++;
					}
				
					/* Set the offset of the beginning of the file equal to cursor. */
					fseek(file, cursor, SEEK_SET);

					/* Increment the value of cursor. */
					cursor++;
				}
				
				/* Display the amount of matches to the user. */	
				printf("%d\n", matches);

				/* Set the file position indicator for the stream  pointed to by file
			   	to the beginning of the file. */
				fseek(file, 0L, SEEK_SET);
				
				/* Go to the next argument. */
				i--;
				cur++;
			}

			/* Close the file when finished. */
			fclose(file);

			/* Terminate the program. */
			return 0;
		}
		else
		{
			/* Inform the user that the file does not exist. */
			error("File does not exist");

			/* Terminate the program. */
			return 0;
		}
	}
}

/* Checks if the file is a binary */
int isBinary(FILE * file)
{
	int binary = false;
	int ch;

	while((ch = fgetc(file)) != EOF)
	{	
		if(isprint(ch) == 0 && (char) ch != '\n' && (char) ch != '\t' && (char) ch != '\v' && (char) ch != '\n' && (char) ch != '\f' && (char) ch != '\b' && (char) ch != '\r' && (char) ch != '\'' && (char) ch != '\\' && (char) ch != '\"' && (char) ch != '\a') 
		{
			binary = true;
			break;
		}
	}
	
	/* Set the file position indicator for the stream  pointed to by file
           to the beginning of the file. */
        fseek(file, 0L, SEEK_SET);

	return binary;
}
