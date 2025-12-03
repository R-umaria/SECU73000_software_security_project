#include <sys/socket.h>

#include "globals.h"

int writeSock(int sock, char *buf, size_t len)
{
	ssize_t byteswrote = 0;
	ssize_t ret = 0;

	while (byteswrote < len)
	{
		ret = send(sock, buf + byteswrote, len - byteswrote, 0);
		
		if (ret < 0)
		{
			return -1;
		}

		if (ret == 0)
		{
			break;
		}
		
		byteswrote += ret;
	}

	return byteswrote;
}
