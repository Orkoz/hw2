#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ex2.h"
#include "flight.h"

typedef struct flight_t{
	int flight_num;
	FlightType flight_type;
	char destination[DEST_CHAR_NUM+1];
	BOOL emergency;
}FLIGHT;


//*************************************************************************
//* Function name: createFlight.
//* Description: creates a flight struct according to the inputted parameters.
//* Parameters: 
//*		-	flight_num – the flight number (a number from 1 to MAX_ID).
//*		-	flight_type-  the flight type (DOMESTIC or INTERNATIONAL).
//*		-	destination[] – an array[3] of the destination of the flight.
//*		-	emergency -  is the flight emergency (BOOL).
//* Return Value: a pointer to the new FLIGHT struct.
//*************************************************************************

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency){

	BOOL valid = (BOOL) (is_num_valid(flight_num) && is_destination_valid(destination)); 
	
	if (valid){
		FLIGHT* temp_flight = (FLIGHT*)malloc(sizeof(FLIGHT));
		if (temp_flight != NULL){
			temp_flight->flight_num=flight_num;
			temp_flight->flight_type=flight_type;
			strcpy(temp_flight->destination,destination);
			temp_flight->emergency=emergency;
			return temp_flight;
		}
	}
	return NULL;
}


//*************************************************************************
//* Function name: destroyFlight.
//* Description: removes a flight from the flight list of the runway its belong to.
//* Parameters: 
//*		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void destroyFlight(FLIGHT* flight){

	free(flight);
}


//*************************************************************************
//* Function name: printFlight.
//* Description: prints to the user to description of the input flight.
//* Parameters:
//* 		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void printFlight(FLIGHT* flight){
	char emg = 'R';
	char type = 'D';
	if (flight->emergency==TRUE)
		emg = 'E';
	if (flight->flight_type==INTERNATIONAL) 
		type = 'I';
	printf("Flight %i %d %s %d\n", flight->flight_num,type,flight->destination,emg);
}


//*************************************************************************
//* Function name: is_num_valid.
//* Description: checks if the input flight or runway number is valid (a number between 1 to MAX_ID).
//* Parameters:
//*		-	num – flight or runway number.
//* Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL is_num_valid(int num){
	if (num >= 1 && num <= MAX_ID)
		return TRUE;
	
	//fprintf(stderr, "Invalid input number.\n Please enter a number between 1 to %d\n", MAX_ID);
	return FALSE;
}


//*************************************************************************
//* Function name: is_destination_valid.
//* Description: checks if the input flight destination is valid (3 capital letters array).
//* Parameters:
//*		-	destination – a char array of the flight destination.
//* Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL is_destination_valid(char destination[]){
	int length = strlen(destination);
	
	if (length != DEST_CHAR_NUM){
		return FALSE;
	}
	
    for (int i=0;i<length;i++){
		if((destination[i] < 'A' && destination[i] > 'Z')) {
			return FALSE;
		}
	}
	
	return TRUE;
}


//*************************************************************************
//* Function name: is_emergency_valid.
//* Description: checks if the input flight emergency parameter is valid (TRUE or FALSE).
//* Parameters:
//*		-	emergency – flight emergency parameter (enum BOOL).
//* Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL compare_flight_num(FLIGHT* flight,int flight_num){
	if (flight->flight_num == flight_num)
	{
		return TRUE;
	} else
	{
		return FALSE;
	}
}


//*************************************************************************
//* Function name: compare_flight_dest
//* Description: compare between two 3 char string - the destination of the flight and the given destination
//* Parameters:
//*		-	flight - a pointer to the flight
//*		-	destination - a 3 char string to compare to.
//* Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL compare_flight_dest(FLIGHT* flight, char destination[]){
	if (strcmp(flight->destination, destination))
	{
		return FALSE;
	} else
	{
		return TRUE;
	}
}


//*************************************************************************
//* Function name: change_flight_dest
//* Description: change the destination of the flight to the given destination
//* Parameters:
//*		-	flight - a pointer to the flight
//*		-	destination - a 3 char string to change to.
//* Return Value: None.
//*************************************************************************

void change_flight_dest(FLIGHT* flight, char destination[]){
	strcpy(flight->destination,destination);
}


//*************************************************************************
//* Function name: get_flight_num
//* Description: return the number of the given flight.
//* Parameters:
//*		-	flight - a pointer to the flight
//* Return Value: int - the number of the flight (a number between 1 to MAX_ID)
//*************************************************************************

int get_flight_num(FLIGHT* flight){
	return flight->flight_num;
}


//*************************************************************************
//* Function name: get_flight_type
//* Description: return the type of the given flight.
//* Parameters:
//*		-	flight - a pointer to the flight
//* Return Value: FlightType (DOMESTIC or INTERNATIONAL)
//*************************************************************************

FlightType get_flight_type(FLIGHT* flight){
	return flight->flight_type;
}


//*************************************************************************
//* Function name: get_flight_dest
//* Description: return the destination of the given flight.
//* Parameters:
//*		-	flight - a pointer to the flight
//* Return Value: 3 character array (the destination of the flight).
//*************************************************************************

char* get_flight_dest(FLIGHT* flight){
	return flight->destination;
}


//*************************************************************************
//* Function name: get_flight_emerg
//* Description: return if the given flight is an emergency flight.
//* Parameters:
//*		-	flight - a pointer to the flight
//*  Return Value: BOOL (TRUE if valid and FALSE if not).
//*************************************************************************

BOOL get_flight_emerg(FLIGHT* flight){
	return flight->emergency;
}