#ifndef _UTIL_H
#define _UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>





#define LOGGER_FLAG_ALL							'+'				/** <User input flag to print the content of all the modules  */
#define LOGGER_FLAG_MAIN						'm'				/** <User input flag to print the content of the module main.cc  */
#define LOGGER_FLAG_TIME						't'				/** <User input flag to print the time of execution*/
#define LOGGER_FLAG_RESULT						'p'				/** <User input flag to print the result matrix  */
#define LOGGER_FLAG_COMPUTATION					'c'				/** <User input flag to print the computations*/
#define LOGGER_FLAG_UTIL						'u'				/** <User input flag to print the util functions*/

#define PARAMETER_LOGGER_FLAG					"--logger"
#define PARAMETER_PRINT_HELP					"--help"
#define PARAMETER_NB_ITERATION					"--nbIteration"

#define DEFAULT_LOGGER_FLAG						'+'
#define DEFAULT_NB_ITERATION					10
#define LOGGER_HEADER							"\t>>>>>"

/**
 * \brief Returns a constant string containing the value of the input macros
 */
#define MACROS_VALUE_STRING(s)		str(s)
#define str(s)						#s
#define PRINT_FORMAT				(!strcmp("float",	MACROS_VALUE_STRING(DATA_TYPE)))	?	\
										"%15f "												:	\
									(!strcmp("int",		MACROS_VALUE_STRING(DATA_TYPE)))	?	\
										"%15d "												:	\
										LOGGER_error(1, "Data type not handled: \"%s\"", MACROS_VALUE_STRING(DATA_TYPE))




/**
 * \brief Initializes the logger such that only messages with the given flag get printed.
 * \param flagList: String of characters for whose LOGGER messages are to be enabled.
 * If the flagList is "+", we enable all LOGGER messages.
 */
void LOGGER_Init (const char *flagList);


/**
 * \brief Return TRUE (1) if DEBUG messages with "flag" are to be printed.
 */
int LOGGER_IsEnabled (char flag);


/**
 * \brief LOGGER: Prints a message, if flag is enabled (equivalent to printf) and debug flag is set
 * \param flag		: flag corresponding to the type of message to print. If flag is NULL, then we force the print.
 * \param format	: equivalent to printf format
 */
#ifndef DEBUG_LOGGER
	#define LOGGER(...)		((void)0)
#else
	#define LOGGER			myPrint
#endif


/**
 * \brief LOGGER: Prints a message, if flag is enabled (equivalent to printf) and debug flag is set
 * \param flag		: flag corresponding to the type of message to print. If flag is NULL, then we force the print.
 * \param format	: equivalent to printf format
 */
void myPrint(char flag, const char *format, ...);


/**
 * \brief Prints a standardized error message.
 * \details prints also the file and line number of the error in the code.
 */
const char* LOGGER_error(int exit_b, const char *format, ...);


/**
 * \brief Prints a message(equivalent to Like printf)
 * \param format	: equivalent to printf format
 */
void LOGGER_force(const char *format, ...);


/**
 * \details Read the parameters from the command line and put them into the output parameters
 */
void extractParameter(int argc, char **argv, char * loggerFlag, unsigned int *nbIteration);


void printHelp(char exit_b);


/**
 * \brief If condition is false, print a message and dump core.
 * \details Useful for documenting assumptions in the code.
 * \details: needs to be a #define, to be able to print the location where the error occurred.
 * \authors Cf code Thomas Ropars (project dynamic OS allocator)
 */
#define ASSERT(condition)			\
	if (!(condition))				\
	{								\
		fprintf(stderr, "Assertion failed: line %d, file \"%s\"\n", __LINE__, __FILE__);	\
		fflush(stderr);				\
		abort();					\
	}

#endif
