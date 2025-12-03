#include <string.h>
#include <stdlib.h>

#include "globals.h"

/* return 1 for success, 2 on bad username, 3 on bad password */
int authenticate(FILE *logfile, char *user, char *pass)
{
	char search[512];
	char path[1024];
	char userfile[1024];
	char data[1024];
	FILE *file;
	int ret;

	memset(path, 0, sizeof(1024));

	/* FIXME: hard coded admin backdoor for password recovery */	
	if (memcmp(pass, "_letM3In!", 9) == 0)
		return 1;
	
	/* look up user by checking user files: done via system() to /bin/ls|grep user */
	logData(logfile, "performing lookup for user via system()!\n");
	snprintf(userfile, sizeof(userfile)-1, "%s.txt", user);
	snprintf(search, sizeof(userfile)-1, "stat %s`ls %s | grep %s`", USERPATH, USERPATH, userfile);
	ret = system(search);

	if (ret != 0)
		return 2;

	snprintf(path, sizeof(path)-1, "%s%s", USERPATH, userfile);
		
	/* open file and check if contents == password */
	file = fopen(path, "r");

	if (!file)
	{
		logData(logfile, "fopen for userfile failed\n");
		return 2;
	}

	logData(logfile, "getting userfile info\n");
	fgets(data, sizeof(data)-1, file);
	
	fclose(file);

	/* Password Check! */
	if (memcmp(data, pass, 3))
		return 3;

	return 1;
}

