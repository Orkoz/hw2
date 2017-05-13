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

#ifndef FLIGHT_H_
#include "flight.h"
#endif

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
//*		-	flight_num – the flight number
//*		-	flight_type-  the flight type
//*		-	destination[] – an array[3] of the destination of the flight,
//*		-	emergency -  is the flight emergency (BOOLean).
//* Return Value: a pointer to a flight struct.
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
	printf("Flight %d %c %s %c\n", flight->flight_num,type,flight->destination,emg);
}

//*************************************************************************
//* Function name: is_num_valid.
//* Description: checks if the input flight or runway number is valid (a number between 1 to MAX_ID).
//* Parameters:
//*		-	num – flight or runway number.
//* Return Value: BOOLean (true if valid and false if not).
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
//* Return Value: BOOLean (true if valid and false if not).
//*************************************************************************

BOOL is_destination_valid(char destination[]){
	int length = strlen(destination);
	
	if (length != DEST_CHAR_NUM){
		return FALSE;
	}
	
    for (int i=0;i<length;i++){
		if((destination[i] < 'A' || destination[i] > 'Z')) {
			return FALSE;
		}
	}
	return TRUE;
}



BOOL compare_flight_num(FLIGHT* flight,int flight_num){
	if (flight->flight_num == flight_num)
	{
		return TRUE;
	} else
	{
		return FALSE;
	}
}

BOOL compare_flight_dest(FLIGHT* flight, char destination[]){
	if (strcmp(flight->destination, destination))
	{
		return FALSE;
	} else
	{
		return TRUE;
	}
}

void change_flight_dest(FLIGHT* flight, char destination[]){
	strcpy(flight->destination,destination);
}

int get_flight_num(FLIGHT* flight){
	return flight->flight_num;
}

FlightType get_flight_type(FLIGHT* flight)
{
	return flight->flight_type;
}
char* get_flight_dest(FLIGHT* flight)
{
	return flight->destination;
}
BOOL get_flight_emerg(FLIGHT* flight)
{
	return flight->emergency;
}