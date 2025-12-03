#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#include "globals.h"

void logData(FILE *logfile, char *format, ...)
{
	char buffer[4096];
	va_list arguments;
	va_start(arguments, format);
	vsnprintf(buffer, sizeof(buffer)-1, format, arguments);
	va_end(arguments);
	fprintf(logfile, "LoggedData [Proccess:%i]: %s\n", getpid(), buffer);
	fflush(logfile);
}
