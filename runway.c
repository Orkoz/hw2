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
	struct FLIGHT_ITEM* first_flight; // not sure this is the right notation
}	RUNWAY;

typedef struct flight_item{
	FLIGHT* this_flight;
	FLIGHT_ITEM* next_flight_item;
}	FLIGHT_ITEM;

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

RUNWAY* createRunway (int runway_num, FlightType runway_type)
{
	// Do we need to check input vars here or in main?
	RUNWAY* temp_runway = (RUNWAY*)malloc(sizeof(RUNWAY));
	if (temp_runway != NULL)
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
	// Do we need to check input vars here or in main?
	if (runway == NULL)
		return;
	FLIGHT_ITEM* flight_item;
	flight_item = runway->first_flight;
	while (flight_item != NULL)
	{
		FLIGHT* temp_flight;
		temp_flight  = flight_item->this_flight;
		destroyFlight(temp_flight);
		
		FLIGHT_ITEM* temp_flight_item;
		temp_flight_item = flight_item;
		flight_item = flight_item->next_flight_item;
		free(temp_flight_item);
	}
	free(runway);
	return;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

bool isFlightExists (*RUNWAY runway, int flight_num)
{
	if (runway == NULL || is_num_valid(flight_num) == 0)
		return FALSE;
	FLIGHT_ITEM* temp_flight_item;
	temp_flight_item = runway->first_flight;
	
	while (temp_flight_item != NULL)
	{
		if (compare_flight_num(temp_flight_item->this_flight, flight_num) == TRUE)
			return TRUE;
		temp_flight_item = temp_flight_item->next_flight_item;
	}
	return FALSE;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

int getFlightNum (*RUNWAY runway)
{
	if (runway == NULL)
		return -1;
	int counter = 0;
	FLIGHT_ITEM* flight_item;
	flight_item = runway->first_flight;
	while (flight_item != NULL)
	{
		if (flight_item->this_flight != NULL)
			counter++;
		flight_item = flight_item->next_flight_item;	
	}
	return counter;
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
//* 			The only part in the program we need to remove a flight is when
//* 			we destroy the airport. In that case each time we will remove
//* 			only the first flight again and again. This is way it is not
//* 			necessary to link the list again. 
//* Parameters:
//* Return Value:
//*************************************************************************

Result removeFlight(*RUNWAY runway, int flight_num)
{
	if (runway == NULL || runway->first_flight == NULL ||  is_num_valid(flight_num) == 0)
		return FAILURE;
	
	FLIGHT_ITEM* temp_flight;
	temp_flight = runway->first_flight;
	
	
	
	
/* 	if (temp_flight->this_flight->flight_num == flight_num)
	{
		destroyFlight(temp_flight->this_flight);
		runway->first_flight = temp_flight->next_flight_item;
		free(temp_flight);
		return SUCCESS;
	}
	
	return FAILURE; */

	
/* 	while (temp_flight_item != NULL)
	{
		if (compare_flight_num(temp_flight_item->this_flight, flight_num) == TRUE)
			
			return TRUE;
		temp_flight_item = temp_flight_item->next_flight_item;
	} */
	//return FAILURE;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result depart (*RUNWAY runway)
{
	if (runway == NULL || runway->first_flight == NULL)
		return FAILURE;
	
	
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
