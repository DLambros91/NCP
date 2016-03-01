#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void charatatime(char * str);

int main(void)
{
	pid_t pid;
	if ((pid = fork()) < 0)
		perror("Fork Error");
	else if (pid == 0)
	{
		charatatime("output from child. output from child. output from child.\n");
	}
	else
	{
		charatatime("output from parent. output from parent. output from parent.\n");
	}
	exit(0);
}

static void charatatime(char * str)
{
	char * ptr;
	int    c;
	
	/* set unbuffered */
	setbuf(stdout,NULL);
	for (ptr = str; c = *ptr++;)
		putc(c,stdout);
}
