#include <string.h>
#include <stdio.h>

#include "globals.h"

int userFunctions(FILE *logfile, int sock, char *user)
{
	char action[1024];
	size_t len;

	if (0 == strncmp(user, "admin", 5))
	{
		adminFunctions(logfile, sock);
		return 0;
	}
	
	while (1)
	{
		writeSock(sock, READY, sizeof(READY));
		memset(action, 0, sizeof(action));
		len = readSock(sock, action, sizeof(action));	
	
		if (action[0] == LIST_POSTINGS)
		{
			listPostings(sock, logfile, action);
		}
		else if (action[0] == READ_POSTING)
		{
			readPosting(sock, logfile, action);	
		}
		else if (action[0] == WRITE_POSTING)
		{
			writePosting(sock, logfile, action);
		}
		else
		{
			logData(logfile, "unknown action %x", action[0]);
			return;
		}
	}

	return 0;
}
