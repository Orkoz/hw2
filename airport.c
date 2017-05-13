#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"
#include "runway.h"
#include "flight.h"
#include "airport.h"

struct runway_item{
	RUNWAY* runway;
	RUNWAY_ITEM* next_runway;
};

struct airport_t{
	RUNWAY_ITEM* runway_list;
	RUNWAY_ITEM* last_runway;
};


static AIRPORT* airport;


//*************************************************************************
//* Function name: create_airport
//* Description: creates an empty airport ADT.
//* Parameters: None.
//* Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL create_airport()
{
	airport = (AIRPORT*)malloc(sizeof(AIRPORT));
	if (airport != NULL)
	{
		airport->runway_list = NULL;
		airport->last_runway = NULL;
		return TRUE;
	}
	return FALSE;
}


//*************************************************************************
//* Function name: addRunway
//* Description: add a runway to the airport (at the end of the runway list) according to the given parameters.
//* Parameters:
//*		-	runway_num - the ranway number (a number from 1 to MAX_ID).
//*		-	runway_type - the ranway type (DOMESTIC or INTERNATIONAL)
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************

Result addRunway(int runway_num, FlightType runway_type) {
  
	//checks if there is already a runway with the same number.
	if (runway_num_exists(runway_num) != NULL)
		return FAILURE;

	RUNWAY* new_runway = createRunway(runway_num, runway_type);
	RUNWAY_ITEM* new_runway_item = (RUNWAY_ITEM*)malloc(sizeof(RUNWAY_ITEM));
	if ((new_runway_item != NULL) && (new_runway != NULL)){
		new_runway_item->runway = new_runway;
		new_runway_item->next_runway = NULL;

		if (airport->runway_list == NULL) // If this is the first runway added
		{
			airport->runway_list = new_runway_item;
			airport->last_runway = new_runway_item;
		}
		else
		{
			airport->last_runway->next_runway = new_runway_item;
			airport->last_runway = new_runway_item;
		}

		return SUCCESS;
	}
	return FAILURE;
}


//*************************************************************************
//* Function name: isFlightExists.
//* Description: checks if there is already a runway in the airport with the given number.
//* Parameters:
//*		-	runway_num - the ranway number (a number from 1 to MAX_ID).
//*  Return Value: a pointer to the founed RUNWAY struct, NULL if failed.
//*************************************************************************

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


//*************************************************************************
//* Function name: removeRunway.
//* Description: first, remove all the runway's (recognized by its number) flights and then remove the runway itself  from the airport and free all relevant memory.
//* Parameters:
//*		-	runway_num - the ranway number (a number from 1 to MAX_ID).
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************

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


//*************************************************************************
//* Function name: addFlightToAirport
//* Description: add a flight to the airport according to its parameters. the flight inserted to the last of its designated runway: 
//* 			the most 'free' runway the matches the flight type. if there are two match runways with the same number of flights, the flight will 
//* 			be insert into the one with the lower runway_num. emergency flight will be entered after all the other emergency flight that are already 
//* 			in the runway.
//* Parameters: 
//*		-	flight_num – the flight number (a number from 1 to MAX_ID).
//*		-	flight_type-  the flight type (DOMESTIC or INTERNATIONAL).
//*		-	destination[] – an array[3] of the destination of the flight.
//*		-	emergency -  is the flight emergency (BOOL).
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************

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
		
		if (minimal_flights_runway!= NULL){
      if (addFlight(minimal_flights_runway->runway, flight) == SUCCESS)
			  return SUCCESS;
   }
    
    destroyFlight(flight);
    return FAILURE;
	}


//*************************************************************************
//* Function name: departFromRunway.
//* Description: removes the firsts flights from the runway so that the number of flights in the runway will be less than the given number. 
//* 			frees the relevant memory
//* Parameters:
//*		-	runway_num - the ranway number (a number from 1 to MAX_ID).
//*		-	number_of_flights - the max number of flight in the runway.
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************

Result departFromRunway(int runway_num, int number_of_flights){
	
	RUNWAY* temp_runway = runway_num_exists(runway_num);

	if (temp_runway == NULL || getFlightNum(temp_runway) < number_of_flights)
		return FAILURE;
    int i;
    for (i = 0; i < number_of_flights; ++i) {
        depart(temp_runway);
    }

	return SUCCESS;
}


//*************************************************************************
//* Function name: changeDest.
//* Description: change every flight in the airport that it's destination is destination[] to new_destination[]
//* Parameters:
//*		-	destination - an array[3] of the destination of the flight.
//*		-	new_destination - an array[3] of the new destination of the flight.
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************

Result changeDest(char destination[],char new_destination[]){
	if (!(is_destination_valid(destination) && is_destination_valid(new_destination)))
		return FAILURE;
	
	//goes trow every flight in the airport that it's destination is destination[] and change it to new_destination[]
	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	while (temp_runway_item != NULL){
		FLIGHT* temp_flight = isFlightDest(temp_runway_item->runway, destination);
		while (temp_flight != NULL) {
			change_flight_dest(temp_flight, new_destination);
			temp_flight = isFlightDest(temp_runway_item->runway, destination);
		}
		temp_runway_item = temp_runway_item->next_runway;
	}
	return SUCCESS;
}

//*************************************************************************
//* Function name: delay.
//* Description: delay (moves to the end of the relevant runway list) all the flight which there distention equals to the given destination.
//* Parameters:
//*		-	destination - an array[3] of the destination of the flight.
//*  Return Value: FAILURE or SUCCESS
//*************************************************************************


Result delay(char destination[]){
	if (!(is_destination_valid(destination)))
		return FAILURE;
	if (airport->runway_list == NULL)
		return SUCCESS;

	//goes trow every flight in the airport.
	RUNWAY_ITEM* temp_runway_item = airport->runway_list; 	/*a temp runway list which will contain all the runway's flight which there 
															distention equals to the given destination, one runway at the time*/
	while (temp_runway_item != NULL){
		RUNWAY* temp_runway = createRunway(get_runway_num(temp_runway_item->runway), get_runway_type(temp_runway_item->runway)); 	
		FLIGHT* temp_flight = isFlightDest(temp_runway_item->runway, destination); /*find the first flight in the runway which its distention 
																					equals to the given destination.*/
		while (temp_flight != NULL) {
			addFlight(temp_runway, temp_flight); //add this flight to the a temp runway list
			removeFlight(temp_runway_item->runway, get_flight_num(temp_flight));//remove the flight from its original runway
			temp_flight= isFlightDest(temp_runway_item->runway, destination); // get the next flight in this runway
		}

		//put all the flights back in the original runway.
		temp_flight = isFlightDest(temp_runway, destination);
		while (temp_flight != NULL) {
			addFlight(temp_runway_item->runway, temp_flight);
			removeFlight(temp_runway, get_flight_num(temp_flight));
			temp_flight = isFlightDest(temp_runway, destination);
		}

		temp_runway_item = temp_runway_item->next_runway;
		destroyRunway(temp_runway);
	}

	return SUCCESS;
}


//*************************************************************************
//* Function name: printAirport
//* Description: print to the screen the details of the airport.
//* Parameters: None.
//*  Return Value: None.
//*************************************************************************

void printAirport()
{
	printf("Airport status:\n");
	RUNWAY_ITEM* temp_runway_item = airport->runway_list;
	while (temp_runway_item != NULL)
	{
		printRunway(temp_runway_item->runway);
		temp_runway_item = temp_runway_item->next_runway;
	}
	
	printf("\n");
}


//*************************************************************************
//* Function name: destroyAirport
//* Description: first, remove all the runway and then remove the airport and free all relevant memory.
//* Parameters:None.
//*  Return Value: None.
//*************************************************************************

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
