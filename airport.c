#ifndef STRING_H_
#include <string.h>
#endif

#ifndef STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#include <stdlib.h>
#endif

#ifndef EX2_H_
#include "ex2.h"
#endif

#ifndef RUNWAY_H_
#include "runway.h"
#endif

#ifndef FLIGHT_H_
#include "flight.h"
#endif

#ifndef AIRPORT_H_
#include "airport.h"
#endif

typedef struct runway_item{
	RUNWAY* runway;
	RUNWAY_ITEM* next_runway;
}RUNWAY_ITEM;

typedef struct airport_t{
	RUNWAY_ITEM* runway_list;
	RUNWAY_ITEM* last_runway;
}AIRPORT;

static AIRPORT airport = (AIRPORT)malloc(sizeof(AIRPORT));

Result addRunway{int runway_num, FlightType runway_type){
	
	if (runway_num_exists(runway_num) == TRUE)
		return FAILURE;
		
	RUNWAY* new_runway = createRunway(runway_num, runway_type);
	RUNWAY_ITEM* temp_runway_item = (RUNWAY_ITEM)malloc(sizeof(RUNWAY_ITEM));
	
	if (new_runway != NULL && temp_runway_item !=NULL){
		temp_runway_item->runway = new_runway;
		temp_runway_item->next_runway = NULL;
		// ????????????
		airport->last_runway->next_runway = temp_runway_item;
		airport->last_runway = temp_runway_item;
		destroyRunway (new_runway);
		return SUCCESS;
	}
	
	return FAILURE;
}

bool runway_num_exists(int runway_num){
	
	RUNWAY* temp_runway = airport->runway_list;
	while (temp_runway != NULL)
	{
		if (temp_runway->runway->runway_num == runway_num)
			return TRUE;
		temp_runway = temp_runway->next_runway;
	}
	return FALSE;
}

Result removeRunway{int runway_num){
	if (airport->runway_list == NULL)
		return FAILURE;
	if (runway_num_exists(runway_num) == FALSE)
		return FAILURE;
	
	RUNWAY_ITEM* deleted_runway_item;
	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	
	// dealing with first runway item
	if (temp_runway_item->runway->runway_num == runway_num)
	{
		airport->runway_list = temp_runway_item->next_runway;
		destroyRunway(temp_runway_item->runway);
		free(temp_runway_item);
		return SUCCESS;
	}
	
	// dealing with mid or end of list
	
	while (temp_runway_item != NULL)
	{
		if (temp_runway_item->next_runway->runway->runway_num == runway_num)
		{
			deleted_runway_item = temp_runway_item->next_runway;
			temp_runway_item->next_runway = deleted_runway_item->next_runway;
			destroyRunway(deleted_runway_item->runway);
			free(deleted_runway_item);
			return SUCCESS;
		} else
		{
			temp_runway_item = temp_runway_item->next_runway;
		}
	}
	return FAILURE;
}

Result addFlightToAirport{int flight_num, FlightType flight_type, char destination[], BOOL emergency)
	{
		if (airport->runway_list == NULL)
			return FAILURE;
		
		//  creating flight, checking parameters in module flight
		FLIGHT* flight = createFlight(flight_num, flight_type, destination, emergency);
		if (flight == NULL)
			return FAILURE;
		

		// Going through every runway checking if flight num exists
		// Also checking for the runway with minimal flights in list
		RUNWAY_ITEM* temp_runway_item = airport->runway_list;
		int counter = 0;
		RUNWAY_ITEM* minimal_flights_runway = NULL;
		
		while (temp_runway_item != NULL)
		{
			// Checking for same flight number
			if (isFlightExists(temp_runway_item->runway, flight_num) == TRUE)
			{
				destroyFlight(flight);
				return FAILURE;
			}
			
			// Checking for minimal flights in runway list
			if (temp_runway_item->runway->runway_type == flight_type)
			{
				if (minimal_flights_runway == NULL)
				{
					minimal_flights_runway = temp_runway_item;
					counter = getFlightNum(minimal_flights_runway->runway);
				} else
				{
					if (getFlightNum(temp_runway_item->runway) < counter)
					{
						minimal_flights_runway = temp_runway_item;
						counter = getFlightNum(minimal_flights_runway->runway);
					}
				}
			}
			temp_runway_item = temp_runway_item->next_runway;
		}
		
		if (addFlight(minimal_flights_runway->runway, flight) == SUCCESS)
		{
			destroyFlight(flight);
			return SUCCESS;
		} else
		{
			destroyFlight(flight);
			return FAILURE;
		}
	}

Result departFromRunway{int runway_num, int number_of_flights);
Result changeDest{char destination[],char new_destination[]);
Result delay{char destination[]);

void printAirport()
{
	printf("Airport status:/n");
	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	while (temp_runway_item != NULL)
	{
		printRunway(temp_runway_item->runway);
		temp_runway_item = temp_runway_item->next_runway;
	}
}

void destroyAirport()
{
	RUNWAY_ITEM* deleted_runway_item = airport->runway_list;
	RUNWAY_ITEM* temp_runway_item = NULL;
	while (deleted_runway_item != NULL)
	{
		destroyRunway (deleted_runway_item->runway);
		temp_runway_item = deleted_runway_item;
		deleted_runway_item = deleted_runway_item->next_runway;
		free(temp_runway_item);
	}
	free(airport);
}
