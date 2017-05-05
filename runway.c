//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"
#include "flight.h"

/*
typedef יוצר קיצור של טיפוס מורכב
enum מייצר טיפוס חדש
*/

typedef struct runway_t{
	int runway_num;
	FlightType runway_type;
	struct FLIGHT* first_flight; // not sure this is the right notation
}	RUNWAY;

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

RUNWAY* createRunway (int runway_num, FlightType runway_type)
{
	RUNWAY* temp_runway = (RUNWAY*)malloc(sizeof(RUNWAY));
	if (temp_runway)
	{
		temp_runway->runway_num=runway_num;
		temp_runway->runway_type=runway_type;
		temp_runway->first_flight=NULL;
		return temp_runway;
	} else {
		return NULL;
	}
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

void destroyRunway (*RUNWAY runway)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

bool isFlightExists (*RUNWAY runway, int flight_num)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

int getFlightNum (*RUNWAY runway)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result addFlight (*RUNWAY runway, *FLIGHT flight)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result removeFlight(*RUNWAY runway, int flight_num)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result depart (*RUNWAY runway)
{
	
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

void printRunway (*RUNWAY runway)
{
	
	
}
