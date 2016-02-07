#include <stdio.h>
#include "alerts.h"

#define true  1
#define false 0
 
int isBinary(File * file);

int main(int argc, char ** argv)
{
	/* Check if the minimum required amount of arguments have been supplied. */
	if (argc < 3)
	{
		error("Not enough arguments.");
		return 0;
	}
	else
	{
		/* Open the requested file. */
		FILE * file = fopen(argv[1], "r");

		/* Check that the requested file is existing */
		if (file != NULL)
		{
			/* Check if the file is a binary. */
			if(isBinary(file))
			{
				warning("File is a binary. Might result with incorrect results.");
			}			

			/* Set the file position indicator for the stream  pointed to by file
			   to the beginning of the file. */
			fseek(file, 0L, SEEK_SET);	

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

int isBinary(File * file)
{
	return true;
}
