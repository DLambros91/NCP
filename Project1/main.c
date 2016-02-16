#include <stdio.h>
#include "alerts.h"
#include <string.h>
#include <ctype.h>
<<<<<<< HEAD
#include <strings.h>
=======
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <strings.h>
#include <stdlib.h>
>>>>>>> f68fdc0c8bb0dc5e852ea0a907c8a923742ebf2a

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
		if (strcasecmp(argv[1], "-s") == 0)
		{
			/* Open the requested file. */
			int file = open(argv[2], O_RDONLY); 

			/* Indicates the number of substrings to search for. */
			int i = argc - 3;

			/* Indicates the current substring argument. */
			int cur = 3;
			
<<<<<<< HEAD
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
=======
			/* Check that the requested file is existing. */
			if (file != -1)
			{
				off_t fsize = lseek(file, 0, SEEK_END);
				lseek(file, 0, SEEK_SET);		
				/*while(i != 0)
				{
					char * substring = argv[cur];

					int size = strlen(substring);
					char c[size];
					int matches = 0;
					int cursor = 1;
					off_t curoffset = 0;
					while(read(file, c, size) != 0)
					{
						if (strcasecmp(c, substring) == 0)
						{
							matches++;
						}
						lseek(file, cursor, SEEK_SET);
						cursor++;
						curoffset += size;
						if ((curoffset + size) > fsize)
						{
							size = (int) (fsize - curoffset);
						}
					}
					printf("%d\n", matches);
					close(file);
					file = open(argv[2], O_RDONLY);
					i--;
					cur++;
				}*/
				while (i != 0)
				{
					char * substring = argv[cur];
					int size = strlen(substring);
					char * c = (char *) calloc(size, sizeof(char *));
					int matches = 0;
					int cursor = 1;
					int j;
						
					while((lseek(file, 0, SEEK_CUR)  != fsize))
					{
						//printf("Current Offset = %ld\n", curoffset);
						for (j = 0; j < size; j++)
						{
							if (lseek(file, 0, SEEK_CUR) != fsize)
							{
								read(file, &c[j], 1);
							}
						}
					//	char * x = strtok(c, " ");
					//	char * y = strtok(substring, " ");
						
						if (strcasecmp(c, substring) == 0)
						{
							matches++;
						}
						lseek(file, cursor, SEEK_SET);
						cursor++;
					}
					printf("%d\n", matches);
					i--;
					cur++;
					lseek(file, 0L, SEEK_SET);
					free(c);
				}
				close(file);
				return 0;
			}
			else
			{
//				fprintf(stderr, "%s: No such file or directory\n", argv[1]);
				//error("File does not exist");
				perror(argv[0]);
			}
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
					char c[size];
					int matches = 0;
					int cursor = 1;
					while (fgets(c, size + 1, file) != NULL)
					{
						if (strcasecmp(c, substring) == 0)
						{
							matches++;
						}	

						fseek(file, cursor, SEEK_SET);
						cursor++;
					}
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
				return 0;
			}
			else
			{
				/* Inform the user that the file does not exist. */
				//error("File does not exist");
				//return 0;
//				fprintf(stderr, "%s: No such file or directory\n", argv[1]);
				perror(argv[0]);
			}
>>>>>>> f68fdc0c8bb0dc5e852ea0a907c8a923742ebf2a
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
