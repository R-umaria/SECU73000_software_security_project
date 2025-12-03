#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "globals.h"

void mainLoop(FILE *logf, int sock)
{
	int clientfd = 0;
	struct sockaddr_in client;
	socklen_t clientlen = 0;
	pid_t offspring = 0;

	memset((char *)&client, 0, sizeof(client));
	
	logData(logf, "entering main loop...");

	while (1)
	{
		clientfd = accept(sock, (struct sockaddr *)&client, &clientlen);
		if (clientfd == -1)
		{
			continue;
		}

		offspring = fork();
	
		if (offspring == -1)
		{
			continue;
		}

		if (offspring == 0)
		{
			handleConnection(logf, clientfd);
			close(clientfd);
			exit(0);
		}

		close(clientfd);
	}
}

