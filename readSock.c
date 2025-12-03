#include <sys/socket.h>

#include "globals.h"

int readSock(int sock, char *buf, size_t len)
{
	ssize_t ret = 0;
	ssize_t bytesread = 0;

	while (bytesread < len)
	{
		ret = recv(sock, buf + bytesread, len - bytesread, 0);

		if (ret == 0)
		{
			break;
		}	

		if (ret < 0)
		{
			return -1;
		}

		bytesread += ret;
	}
	
	return bytesread;	
}
