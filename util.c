#include "util.h"






// -----------------------------
// Global parameters
// -----------------------------
static const char *enableFlags = NULL;	// controls which LOGGER messages are printed


// -----------------------------
// Local functions
// -----------------------------
void LOGGER_Init (const char *flagList)
{
	enableFlags = flagList;
}


int LOGGER_IsEnabled (char flag)
{
	if (enableFlags == NULL)
		return 0;

	return	(0 != strchr(enableFlags, flag)) ||
			(0 != strchr(enableFlags, LOGGER_FLAG_ALL));
}


void myPrint(char flag, const char *format, ...)
{
	if ((flag == LOGGER_FLAG_ALL) || (LOGGER_IsEnabled (flag)))
	{
		va_list ap;
		va_start (ap, format);
		fprintf(stdout, LOGGER_HEADER);
		vfprintf (stdout, format, ap);
		va_end (ap);
		fflush (stdout);
	}
}


const char* LOGGER_error(int exit_b, const char *format, ...)
{
	fprintf(stdout, "\n\n**********************************\n");
	fprintf(stdout, "******** ERROR\n******** ");
	va_list ap;

	va_start (ap, format);
	vfprintf (stdout, format, ap);
	va_end (ap);
	fflush (stdout);

	fprintf(stdout, "\n**********************************\n");
	fflush (stdout);

	if (exit_b)
		exit(2);

	return "ERROR";
}


void LOGGER_force(const char *format, ...)
{
	va_list ap;

	va_start (ap, format);
	vfprintf (stdout, format, ap);
	va_end (ap);
	fflush (stdout);
}


/**
 * \details Read the parameters from the command line and put them into the output parameters
 */
void extractParameter(int argc, char **argv, char * loggerFlag, unsigned int *nbIteration)
{
	int i;

	// Initialize parameters with default value
	sprintf(loggerFlag,		"%c", DEFAULT_LOGGER_FLAG);
	*nbIteration = DEFAULT_NB_ITERATION;

	for (i=1; i<argc; i+=2)
	{
		if (!strcmp(argv[i], PARAMETER_PRINT_HELP))
		{
			printHelp(1);
		}
		if (i == argc-1) LOGGER_error(1, "Missing value after parameter: %s", argv[i]);
		else if (!strcmp(argv[i], PARAMETER_LOGGER_FLAG))			sprintf	(loggerFlag,	"%s", argv[i+1]);
		else if (!strcmp(argv[i], PARAMETER_NB_ITERATION))			*nbIteration = atoi(argv[i+1]);
		else
		{
			LOGGER_error(0, "Unknown parameter %s", argv[i]);
			printHelp(1);
		}
	}
	ASSERT(*nbIteration > 0);
}


void printHelp(char exit_b)
{
	LOGGER_force("\nUsage: \n");
	LOGGER_force("\t%s\t <Flgs indicating which part of code prints its traces (\'%c\' to print all)>\n",	PARAMETER_LOGGER_FLAG, LOGGER_FLAG_ALL);
	LOGGER_force("\t%s\t\t to print the current help\n",													PARAMETER_PRINT_HELP);

	if (exit_b)
		exit(2);
}
