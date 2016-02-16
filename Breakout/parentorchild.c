#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 6;	/* External variable in initialized data */
char buf[] = "a write to stdout\n";

void err_sys(const char* x) 
{ 
    perror(x); 
    exit(1); 
}

int main(void)
{
	int var;	/* Automatic variable on the stack */
	pid_t pid;
	
	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error");
	printf("before fork\n"); /* We don't flush stdout */

	if ( (pid = fork()) < 0)
		err_sys("fork error");
	else if (pid == 0)
	{			/* Child */
		glob++;		/* Modify variables */
		var++;
	}
	else
		sleep(2);	/* Parent */
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}
