#include <string.h>

#include "globals.h"

int adminFunctions(FILE *logfile, int sock)
{
	char action[1024];
	size_t len;
	while (1)
	{
		writeSock(sock, READY, sizeof(READY));
		memset(action, 0, sizeof(action));
		len = readSock(sock, action, sizeof(action));	
	
		if (action[0] == ADD_USER)
		{
			addUser(logfile, sock, action);	
		}
		else if (action[0] == COMMAND)
		{
			command(logfile, sock, action);	
		}
		else
		{
			logData(logfile, "unknown action: %x", action[0]);
		}
	}
}

