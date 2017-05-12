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


// Helper function for checking input
BOOL chk_emg_and_typ(char par, int type)
{
	if (type == EMERGENCY)
	{
		if (par == 'E' || par == 'R')
			return TRUE;
	}
	else if (type == F_TYPE)
	{
		if (par == 'I' || par == 'D')
			return TRUE;
	}
	return FALSE;
}




int main()
{
	char szLine[MAX_LINE_SIZE];
	char* delimiters = " \t\n";
	char* command, par1, par2, par3, par4;

	while (fgets(szLine, MAX_LINE_SIZE, stdin))
	{
		command = strtok(szLine, delimiters);
		par1 = strtok(NULL, delimiters);
		par2 = strtok(NULL, delimiters);
		par3 = strtok(NULL, delimiters);
		par4 = strtok(NULL, delimiters);

		switch (command)
		{
		case "Insert":
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Insert failed: not enough parameters./n");
				break;
			}

			int runway_num = atoi(par1);
			if (runway_num == 0 || chk_emg_and_typ(par2, F_TYPE) == FALSE)
			{
				fprintf(stderr, "Insert execution failed./n");
				break;
			}

			FlightType runway_type = ( *par2 == 'D' ? DOMESTIC : INTERNATIONAL );

			if (addRunway(runway_num, runway_type) == FAILURE)
			{
				fprintf(stderr, "Insert execution failed./n");
				break;
			}
			break;

		case "Remove":
			if (par1 == NULL)
			{
				fprintf(stderr, "Remove failed: not enough parameters./n");
				break;
			}
			int runway_num = atoi(par1);
			if (runway_num == 0 || removeRunway(runway_num) == FAILURE)
			{
				fprintf(stderr, "Remove execution failed./n");
				break;
			}
			break;
		case "Add":
			if (par1 == NULL || par2 == NULL || par3 == NULL || par4 == NULL)
			{
				fprintf(stderr, "Add failed: not enough parameters./n");
				break;
			}
			int flight_num = atoi(par1);

			if (flight_num == 0 || chk_emg_and_typ(par2, F_TYPE) == FALSE || chk_emg_and_typ(par4, EMERGENCY) == FALSE)
			{
				fprintf(stderr, "Add execution failed./n");
				break;
			}

			FlightType runway_type = (*par2 == 'D' ? DOMESTIC : INTERNATIONAL);
			BOOL emergency = (*par4 == 'E' ? TRUE : FALSE);

			if (addFlightToAirport(flight_num, flight_type, par3, emergency) == FAILURE)
			{
				fprintf(stderr, "Add execution failed./n");
				break;
			}
			break;
		case "Depart":
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Depart failed: not enough parameters./n");
				break;
			}
			int runway_num = atoi(par1);
			int num_of_flights = atoi(par2);

			if (runway_num == 0 || num_of_flights < 0 || departFromRunway(runway_num, num_of_flights) == FAILURE)
			{
				fprintf(stderr, "Depart execution failed./n");
				break;
			}
			break;
		case "Change":
			if (par1 == NULL || par2 == NULL)
			{
				fprintf(stderr, "Change failed: not enough parameters./n");
				break;
			}
			if (changeDest(par1, par2) == FAILURE)
			{
				fprintf(stderr, "Change execution failed./n");
				break;
			}
			break;
		case "Delay":
			if (par1 == NULL)
			{
				fprintf(stderr, "Delay failed: not enough parameters./n");
				break;
			}
			if (delay(par1) == FAILURE)
			{
				fprintf(stderr, "Delay execution failed./n");
				break;
			}
			break;
		case "Print":
			printAirport();
			break;
		case "Exit":
			destroyAirport();
			return 0;
			break;
		default:
			fprintf(stderr, "Command not found./n");
			break;
		}
	}

	destroyAirport();
	return 0;
}