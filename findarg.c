#include <string.h>

#include "globals.h"

char *findarg(char *argbuf, char argtype)
{
	char *ptr1;
	char *found = NULL;
	char type = 0;
	size_t size;

	ptr1 = argbuf;

	while (1)
	{	
		memcpy((char *)&size, ptr1, 4);
		if (size == 0)
		{
			break;
		}	
		if (ptr1[4] == argtype)
		{
			found = &ptr1[5];
			break;
		}
		ptr1 += size;
	}

	return found;
}

