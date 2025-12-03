#include <stdlib.h>

#include "globals.h"

void command(FILE *log, int sock, char *action)
{
	logData(log, "executing command: %s", &action[1]);
	system(&action[1]);
}

