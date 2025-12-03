#include <string.h>
#include <stdio.h>

#include "globals.h"

void readPosting(int sock, FILE *logfile, char *action)
{
	FILE *file;
	char buf[100];
	char path[100];

	logData(logfile, &action[1]);

	strcpy(path, POSTINGPATH);
	strcat(path, &action[1]);

	logData(logfile, "user request to read posting: %s", path);

	file = fopen(path, "r");

	if (!file)
	{
		writeSock(sock, FILENOTAVAIL, sizeof(FILENOTAVAIL));
		return;
	}
	
	/* fgets for the size of the buffer (100), from the file
	   writing the article to the user each time! */
 
	while (fgets(buf, 1000, file))
		writeSock(sock, buf, strlen(buf));

	fclose(file);

	return;
}
