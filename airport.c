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

static AIRPORT* airport;

BOOL create_airport()
{
	airport = (AIRPORT*)malloc(sizeof(AIRPORT));
	if (airport != NULL)
		return TRUE;
	return FALSE;
}

Result addRunway(int runway_num, FlightType runway_type){

	
	if (runway_num_exists(runway_num) != NULL)
		return FAILURE;
		
	RUNWAY* new_runway = createRunway(runway_num, runway_type);
	RUNWAY_ITEM* new_runway_item = (RUNWAY_ITEM*)malloc(sizeof(RUNWAY_ITEM));
	if (new_runway_item !=NULL){
		new_runway_item->runway = new_runway;
		new_runway_item->next_runway = NULL;
		airport->last_runway->next_runway = new_runway_item;
		airport->last_runway = new_runway_item;
		return SUCCESS;
	}
	return FAILURE;
}

RUNWAY* runway_num_exists(int runway_num){

	RUNWAY_ITEM* temp_runway = airport->runway_list;
	while (temp_runway != NULL)
	{
		if (get_runway_num(temp_runway->runway) == runway_num)
			return temp_runway->runway;
		temp_runway = temp_runway->next_runway;
	}
	return NULL;
}

Result removeRunway(int runway_num){
	if (airport->runway_list == NULL)
		return FAILURE;
	if (runway_num_exists(runway_num) == NULL)
		return FAILURE;
	
	RUNWAY_ITEM* deleted_runway_item;
	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	
	// dealing with first runway item
	if (get_runway_num(temp_runway_item->runway) == runway_num)
	{
		airport->runway_list = temp_runway_item->next_runway;
		destroyRunway(temp_runway_item->runway);
		free(temp_runway_item);
		return SUCCESS;
	}
	
	// dealing with mid or end of list
	
	while (temp_runway_item != NULL)
	{
		if (get_runway_num(temp_runway_item->next_runway->runway) == runway_num)
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

Result addFlightToAirport(int flight_num, FlightType flight_type, char destination[], BOOL emergency)
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
			if (get_runway_type(temp_runway_item->runway) == flight_type)
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


Result departFromRunway(int runway_num, int number_of_flights){
	RUNWAY* temp_runway = runway_num_exists(runway_num);

	if ((temp_runway == NULL) || (getFlightNum(temp_runway) < number_of_flights)) {
		return FAILURE;
	}

	for (int i = 0; i < number_of_flights; ++i) {
		depart(temp_runway);
	}

	return SUCCESS;
}

Result changeDest(char destination[],char new_destination[]){
	if (!(is_destination_valid(destination) && is_destination_valid(new_destination)))
		return FAILURE;

	RUNWAY_ITEM* temp_runway_item = airport->runway_list;

	while (temp_runway_item != NULL){
		FLIGHT* temp_flight = isFlightDest(temp_runway_item->runway, destination);
		while (temp_flight != NULL) {
			change_flight_dest(temp_flight, destination);
			temp_flight = isFlightDest(temp_runway_item->runway, destination);
		}
		temp_runway_item = temp_runway_item->next_runway;
	}

	return SUCCESS;

}

Result delay(char destination[]){
	if (!(is_destination_valid(destination)))
		return FAILURE;

	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	RUNWAY* temp_runway = createRunway(get_runway_num(temp_runway_item->runway), get_runway_type(temp_runway_item->runway));

	while (temp_runway_item != NULL){
		FLIGHT* temp_flight = isFlightDest(temp_runway_item->runway, destination);
		while (temp_flight != NULL) {
			addFlight(temp_runway, temp_flight);
			removeFlight(temp_runway_item->runway, get_flight_num(temp_flight));
			temp_flight= isFlightDest(temp_runway_item->runway, destination);
		}

		temp_flight = isFlightDest(temp_runway, destination);
		while (temp_flight != NULL) {
			addFlight(temp_runway_item->runway, temp_flight);
			removeFlight(temp_runway, get_flight_num(temp_flight));
			temp_flight = isFlightDest(temp_runway, destination);
		}

		temp_runway_item = temp_runway_item->next_runway;
	}

	destroyRunway(temp_runway);
	return SUCCESS;
}


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
