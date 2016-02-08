#include <stdio.h>
#include "alerts.h"
#include <string.h>
#include <ctype.h>

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
			
			while(i != 0)
			{
				char * substring = argv[cur];
				
				int size = strlen(substring);
				int j;
				char c[size];
				for ( j = 0; j < size; j++)
				{
					(char) c[j] = "";
				}
				int matches = 0;

				while (fgets(c, size + 1, file) != NULL)
				{
					fprintf(stderr, "MERP\n");
					if (strcmp(c, substring) == 0)
					{
						matches++;
					}
				}

				/* Set the file position indicator for the stream  pointed to by file
			   	to the beginning of the file. */
				fseek(file, 0L, SEEK_SET);
				
				/* Go to the next argument. */
				i--;
				cur++;
			}
			/* Close the file when finished. */
			fclose(file);
			return 0;
		}
		else
		{
			/* Inform the user that the file does not exist. */
			error("File does not exist");
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
