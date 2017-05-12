#ifndef STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#include <stdlib.h>
#endif

#ifndef STRING_H_
#include <string.h>
#endif

#ifndef EX2_H_
#include "ex2.h"
#endif

#ifndef AIRPORT_H_
#include "airport.h"
#endif

#ifndef RUNWAY_H_
#include "runway.h"
#endif

#ifndef FLIGHT_H_
#include "flight.h"
#endif

#define MAX_LINE_SIZE 256
#define EMERGENCY 0
#define F_TYPE 1

typedef enum command {
	INSERT, REMOVE, ADD, DEPART, CHANGE, DELAY, PRINT, EXIT, ERROR
} Command;

Command select_command(char* command)
{
	if (!strcmp(command, "Insert"))
		return INSERT;
	if (!strcmp(command, "Remove"))
		return REMOVE;
	if (!strcmp(command, "Add"))
		return ADD;
	if (!strcmp(command, "Depart"))
		return DEPART;
	if (!strcmp(command, "Change"))
		return CHANGE;
	if (!strcmp(command, "Delay"))
		return DELAY;
	if (!strcmp(command, "Print"))
		return PRINT;
	if (!strcmp(command, "Exit"))
		return EXIT;
	return ERROR;
}

// Helper function for checking input
BOOL chk_emg_and_typ(char* par, int type)
{
	if (type == EMERGENCY)
	{
		if (!strcmp(par,"E") || !strcmp(par, "R"))
			return TRUE;
	}
	else if (type == F_TYPE)
	{
		if (!strcmp(par, "I") || !strcmp(par, "D"))
			return TRUE;
	}
	return FALSE;
}




int main()
{
	if (!create_airport())
		return 0;

	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* command_string; 
	char* par1;
	char* par2;
	char* par3;
	char* par4;
	Command usr_command;

	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{
		command_string = strtok(szLine, delimiters);
		usr_command = select_command(command_string);
		par1 = strtok(NULL, delimiters);
		par2 = strtok(NULL, delimiters);
		par3 = strtok(NULL, delimiters);
		par4 = strtok(NULL, delimiters);
		int runway_num;
		FlightType runway_type; 
		FlightType flight_type;
		BOOL emergency;

		switch (usr_command)
		{
		case INSERT:
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Insert failed: not enough parameters.\n");
				break;
			}

			runway_num = atoi(par1);
			if (runway_num == 0 || chk_emg_and_typ(par2, F_TYPE) == FALSE)
			{
				fprintf(stderr, "Insert execution failed.\n");
				break;
			}

			runway_type = ( *par2 == 'D' ? DOMESTIC : INTERNATIONAL );

			if (addRunway(runway_num, runway_type) == FAILURE)
			{
				fprintf(stderr, "Insert execution failed.\n");
				break;
			}
			break;

		case REMOVE:
			if (par1 == NULL)
			{
				fprintf(stderr, "Remove failed: not enough parameters.\n");
				break;
			}
			runway_num = atoi(par1);
			if (runway_num == 0 || removeRunway(runway_num) == FAILURE)
			{
				fprintf(stderr, "Remove execution failed.\n");
				break;
			}
			break;
		case ADD:
			if (par1 == NULL || par2 == NULL || par3 == NULL || par4 == NULL)
			{
				fprintf(stderr, "Add failed: not enough parameters.\n");
				break;
			}
			int flight_num = atoi(par1);

			if (flight_num == 0 || chk_emg_and_typ(par2, F_TYPE) == FALSE || chk_emg_and_typ(par4, EMERGENCY) == FALSE)
			{
				fprintf(stderr, "Add execution failed.\n");
				break;
			}

			flight_type = (*par2 == 'D' ? DOMESTIC : INTERNATIONAL);
			emergency = (*par4 == 'E' ? TRUE : FALSE);

			if (addFlightToAirport(flight_num, flight_type, par3, emergency) == FAILURE)
			{
				fprintf(stderr, "Add execution failed.\n");
				break;
			}
			break;
		case DEPART:
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Depart failed: not enough parameters.\n");
				break;
			}
			runway_num = atoi(par1);
			int num_of_flights = atoi(par2);

			if (runway_num == 0 || num_of_flights < 0 || departFromRunway(runway_num, num_of_flights) == FAILURE)
			{
				fprintf(stderr, "Depart execution failed.\n");
				break;
			}
			break;
		case CHANGE:
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Change failed: not enough parameters.\n");
				break;
			}
			if (changeDest(par1, par2) == FAILURE)
			{
				fprintf(stderr, "Change execution failed.\n");
				break;
			}
			break;
		case DELAY:
			if (par1 == NULL)
			{
				fprintf(stderr, "Delay failed: not enough parameters.\n");
				break;
			}
			if (delay(par1) == FAILURE)
			{
				fprintf(stderr, "Delay execution failed.\n");
				break;
			}
			break;
		case PRINT:
			printAirport();
			break;
		case EXIT:
			destroyAirport();
			return 0;
		default:
			fprintf(stderr, "Command not found.\n");
			break;
		}
	}

	destroyAirport();
	return 0;
}