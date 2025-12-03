#include <string.h>

#include "globals.h"

void handleConnection(FILE *logfile, int sock)
{
	char buffer[1024];
	char argbuf[1024];
	char *user = NULL;
	char *pass = NULL;
	int len = 0;
	int ret = 0;
	size_t segloop;
	size_t segmentcount;
	size_t segnext;
	size_t argsize;
	char *ptr1;
	char *ptr2;

	/* read in data */
	memset(buffer, 0, sizeof(buffer));
	len = readSock(sock, buffer, sizeof(buffer));	
	logData(logfile, "handling connection");

	if (len == -1)
		return;
	
	/* parse protocol */
	ptr1 = buffer;
	ptr2 = argbuf;

	/* get count of segments */
	memcpy((char *)&segmentcount, ptr1, 4);

	logData(logfile, "Segment count is %i", segmentcount);
	
	/* make sure there aren't too many segments!
       so the count * 8(bytes) should be the max */
	if (segmentcount * 8 > sizeof(argbuf))
	{
		logData(logfile, "bad segment count");
		return;
	}

	ptr1 += 4;

	memset(argbuf, 0, sizeof(argbuf));

	for (segloop = 0; segloop < segmentcount; ++segloop)
	{
		logData(logfile, "adding segment %i", segloop+1);
		memcpy((char *)&segnext, ptr1, 4);
		logData(logfile, "next segment offset %i", segnext);
		ptr1 += 4;
		memcpy((char *)&argsize, ptr1, 4);	
		logData(logfile, "argsize: %i", argsize);
		memcpy(ptr2, ptr1, argsize);
		ptr2 += argsize;
		ptr1 += segnext;
	}

	logData(logfile, "looking up user args");

	user = findarg(argbuf, USERNAME);
	pass = findarg(argbuf, PASSWORD);

	snprintf(buffer, sizeof(buffer)-1, "User attempting to authenticate: %s", user);
	logData(logfile, buffer);

	logData(logfile, "calling authenticate");
	ret = authenticate(logfile, user, pass);
	logData(logfile, "returned from authenticate");

	if (ret != 1)
	{
		
		if (ret == 2)
		{
			writeSock(sock, BADUSER, sizeof(BADUSER));	
		}	
	
		if (ret == 3)
		{
			writeSock(sock, BADPASS, sizeof(BADPASS));
		}

		snprintf(buffer, sizeof(buffer)-1,"user: %s failed to login with password %s", user, pass);
		logData(logfile, buffer);
		return;
	}

	logData(logfile, "user %s authenticated!", user);
	
	userFunctions(logfile, sock, user);

	return;
} 
