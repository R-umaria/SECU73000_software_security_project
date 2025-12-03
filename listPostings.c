#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "globals.h"

void listPostings(int sock, FILE *logfile, char *action)
{
	char buf[100];
	FILE *list;

	logData(logfile, "user has requested a list of postings");

	/* i wish i had more time! i wouldnt have to write
	   this code using system() to call things! */

	memset(buf, 0, sizeof(buf));
	system(LISTCOMMAND);

	list = fopen("list.txt", "r");

	while (fgets(buf, sizeof(buf)-1, list))
	{
		writeSock(sock, buf, strlen(buf));	
	}

	fclose(list);
	return;	
}

