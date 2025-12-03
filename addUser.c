#include <string.h>

#include "globals.h"

void addUser(FILE *log, int sock, char *action)
{
	char *p;
	char buf[1024];

	p = strchr(&action[1], ':');

	if (!p)
	{
		return;
	}

	*p = 0x0;
	logData(log, "Adding user: %s with pass: %s", &action[1], &p[1]);	
	snprintf(buf, sizeof(buf)-1, "echo %s > %s%s.txt", &p[1], USERPATH, &action[1]);
	return;
}
