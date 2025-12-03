/*
Vulnerable Software.

 Vulnerabilities may include:
    1) dangerous methods
    2) improper logic
    3) unchecked returns
    4) unhandled exceptions
 
SECU73000 Project - to be completed individually

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "globals.h"

int main(int argc, char *argv[])
{
	int sock;
	FILE *logf;

	/* setup log file */
	logf = fopen("logfile.txt", "w"); 

	if (!logf)
	{
		perror("unable to open log file\n");
		exit(1);
	}

	/* go daemon */
	daemon(0,0);
	
	/* setup socket */
	sock = setupSock(logf, PORT);
	
	if (sock == -1)
	{
		logData(logf, "failed to setup socket, exiting");
		exit(1);
	}

	logData(logf, "intial socket setup complete");
	
	mainLoop(logf, sock);	

	/* this should never execute */
	exit(0);
}
