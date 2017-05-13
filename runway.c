//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

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

#ifndef FLIGHT_H_
#include "flight.h"
#endif

#ifndef RUNWAY_H_
#include "runway.h"
#endif

/*
typedef יוצר קיצור של טיפוס מורכב
enum מייצר טיפוס חדש
*/


typedef struct runway_t{
	int runway_num;
	FlightType runway_type;
	FLIGHT_ITEM* first_flight; 
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

void destroyRunway (RUNWAY* runway)
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

BOOL isFlightExists (RUNWAY* runway, int flight_num)
{
	if (runway == NULL || is_num_valid(flight_num) == FALSE)
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

FLIGHT* isFlightDest(RUNWAY* runway, char dest[]){
	if (runway == NULL || is_destination_valid(dest) == FALSE)
		return NULL;

	FLIGHT_ITEM* temp_flight_item = runway->first_flight;

	while (temp_flight_item != NULL)
	{
		if (compare_flight_dest(temp_flight_item->this_flight, dest))
			return temp_flight_item->this_flight;
		temp_flight_item = temp_flight_item->next_flight_item;
	}
	return NULL;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

int getFlightNum (RUNWAY* runway)
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

Result addFlight (RUNWAY* runway, FLIGHT* flight)
{
	// checking pointers
	if (runway == NULL || flight == NULL)
		return FAILURE;
	
	// checking runway type and if same flight num exists
	if (runway->runway_type != get_flight_type(flight) || isFlightExists(runway, get_flight_num(flight)) == TRUE)
		return FAILURE;
	
	// creating a copy of the flight
	char dest[DEST_CHAR_NUM+1];
	strcpy(dest, get_flight_dest(flight));
	FLIGHT* flight_copy = createFlight(get_flight_num(flight), get_flight_type(flight), dest, get_flight_emerg(flight));
	// creating a new flight item for the liked list
	FLIGHT_ITEM* new_flight_item = (FLIGHT_ITEM*)malloc(sizeof(FLIGHT_ITEM));
	if (flight_copy == NULL || new_flight_item == NULL)
		return FAILURE;
	
	new_flight_item->this_flight = flight_copy;
	new_flight_item->next_flight_item = NULL;
	
	// dealing the case where there are no flights in the list yet
	if (runway->first_flight == NULL)
	{
		runway->first_flight = new_flight_item;
		return SUCCESS;
	}

	// creating a temp pointer for the loop
	FLIGHT_ITEM* temp_flight_item = runway->first_flight;
	

	
	// dealing with emergency flights
	if (get_flight_emerg(flight_copy) == TRUE)
	{
		// Dealing with the first item in the list
		if (get_flight_emerg(temp_flight_item->this_flight) == FALSE)
		{
			new_flight_item->next_flight_item = temp_flight_item;
			runway->first_flight = new_flight_item;
		} else 
		{		// Dealing with mid or end of the list
			while (temp_flight_item->next_flight_item != NULL && get_flight_emerg(temp_flight_item->next_flight_item->this_flight) == TRUE)
			{
				temp_flight_item = temp_flight_item->next_flight_item;
			}
			new_flight_item->next_flight_item = temp_flight_item->next_flight_item;
			temp_flight_item->next_flight_item = new_flight_item;
		}
	} else	// dealing with adding the flight to the end of the list
	{
		while (temp_flight_item->next_flight_item != NULL)
		{
			temp_flight_item = temp_flight_item->next_flight_item;
		}
		temp_flight_item->next_flight_item = new_flight_item;
	}
	return SUCCESS;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result removeFlight(RUNWAY* runway, int flight_num)
{
	if (runway == NULL || runway->first_flight == NULL || is_num_valid(flight_num) == FALSE)
		return FAILURE;
	
	FLIGHT_ITEM* temp_flight;
	temp_flight = runway->first_flight;
	
	// Dealing with the first item in the list
	if (get_flight_num(temp_flight->this_flight) == flight_num)
	{
		destroyFlight(temp_flight->this_flight);
		runway->first_flight = temp_flight->next_flight_item;
		free(temp_flight);
		return SUCCESS;
	}
	
	// Dealing with mid or end of the list
	
	FLIGHT_ITEM* temp_flight_next;
	temp_flight_next = runway->first_flight->next_flight_item;
	
	while (temp_flight_next != NULL)
	{
		if (get_flight_num(temp_flight_next->this_flight) == flight_num)
		{
			destroyFlight(temp_flight_next->this_flight);
			temp_flight->next_flight_item = temp_flight_next->next_flight_item;
			free(temp_flight_next);
			return SUCCESS;
		}
		temp_flight = temp_flight->next_flight_item;
		temp_flight_next = temp_flight->next_flight_item;
	}
	return FAILURE;
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

Result depart (RUNWAY* runway)
{
	if (runway == NULL || runway->first_flight == NULL)
		return FAILURE;
	int flight_num;
	flight_num = get_flight_num(runway->first_flight->this_flight);
	removeFlight(runway, flight_num);
	return SUCCESS;
	
}

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************


void printRunway (RUNWAY* runway)
{
	int flight_num;
	flight_num = getFlightNum(runway);
	printf("Runway %d ", runway->runway_num);
	if (runway->runway_type == INTERNATIONAL)
	{
		printf("international\n");
	} else
	{
		printf("domestic\n");
	}
	printf("%d flights are waiting:\n", flight_num);
	
	FLIGHT_ITEM* flight = runway->first_flight;
	while (flight_num != 0)
	{
		printFlight(flight->this_flight);
		flight = flight->next_flight_item;
		flight_num--;
	}
}

int get_runway_num(RUNWAY* runway){

	return runway->runway_num;
}

FlightType get_runway_type(RUNWAY* runway){
	return runway->runway_type;
}
