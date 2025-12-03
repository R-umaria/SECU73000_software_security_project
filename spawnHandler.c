#include <sys/wait.h>

#include "globals.h"

void spawnhandler(int signumber)
{
	pid_t pid;
	int stat;

	while ((pid = waitpid(-1, &stat, WNOHANG))>0)
	{
		printf("circle of life completed for %i\n", pid);	
	}
}

