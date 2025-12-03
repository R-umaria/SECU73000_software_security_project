#include <string.h>
#include <stdio.h>

#include "globals.h"

void writePosting(int sock, FILE *logfile, char *action)
{
	FILE *file;	
	char *p;
	size_t x, y;
	int complete = 0;
	char buf[1024];
	char path[1024];

	strcpy(path, POSTINGPATH);
	strncat(path, &action[1], sizeof(path));

	logData(logfile, "user writing posting: %s", path);

	file = fopen(&action[1], "w");

	if (!file)
	{
		writeSock(sock, FILENOTAVAIL, sizeof(FILENOTAVAIL));
		return;
	}

	writeSock(sock, BEGINFILE, sizeof(BEGINFILE));

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		x = readSock(sock, buf, sizeof(buf)-1);
		for (y = 0; y < x; ++y)
		{
			if (buf[y] == '!')
			{
				if (buf[y+1] == '!' && buf[y+2] == '!')
				{
					buf[y] = 0x0;
					complete = 1;
				}
			}
		}	
		fputs(buf, file);
		if (complete)
		{
			break;
		}
	}

	writeSock(sock, POSTINGWROTE, sizeof(POSTINGWROTE));
	fclose(file);
}

