#include <signal.h>
#include <string.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include "globals.h"


int setupSock(FILE *logf, unsigned short port)
{
	int sock = 0;
	struct sockaddr_in sin;
	int opt = 0;

	if (signal(SIGCHLD, spawnhandler)== SIG_ERR)
	{
		perror("fork() spawn handler setup failed!");
		return -1;
	}
	
	memset((char *)&sin, 0, sizeof(sin));

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == -1)
	{
		logData(logf, "socket() failed");
		return -1;
	}

	opt = 1;

	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		logData(logf,"setsockopt() failed");
		return -1;
	}

	if (bind(sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		logData(logf, "bind() failed");
		return -1;
	}

	if (listen(sock, 10) == -1)
	{
		logData(logf, "listen() failed");
		return -1;
	}

	return sock;
}


