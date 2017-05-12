//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************



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
	char destination[DEST_CHAR_NUM];
	BOOL emergency;
	//FLIGHT* pNext;
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

	BOOL valid = is_num_valid(flight_num) && is_destination_valid(destination); // && is_emergency_valid(emergency); && is_type_valid(flight_type)
	
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
	//FLIGHT* temp_flight = flight->pNext;
	//*flight=*temp_flight;
	// in case *flight=*temp_flight dont work:
		// flight->flight_num=temp_flight->flight_num;
		// flight->flight_type=temp_flight->flight_type;
		// flight->destination=temp_flight->destination;
		// flight->emergency=temp_flight->emergency;
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
	printf("Flight %n %d %s %d/n", flight->flight_num,type,flight->destination,emg);
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
//* Function name: is_type_valid.
//* Description: checks if the input flight or runway type is valid (either DOMESTIC or INTERNATIONAL).
//* Parameters:
//*		-	type – flight or runway type (enum FlightType).
//* Return Value: BOOLean (true if valid and false if not).
//*************************************************************************

//BOOL is_type_valid(FlightType type){
//	if (type == DOMESTIC || type == INTERNATIONAL)
//		return TRUE;
//	
//	//fprintf(stderr, "Invalid input type.\n Please enter either DOMESTIC or INTERNATIONAL\n");
//	return FALSE;
//}


//*************************************************************************
//* Function name: is_destination_valid.
//* Description: checks if the input flight destination is valid (3 capital letters array).
//* Parameters:
//*		-	destination – a char array of the flight destination.
//* Return Value: BOOLean (true if valid and false if not).
//*************************************************************************

BOOL is_destination_valid(char destination[]){
	int length = strlen(destination);
	
	if (length != 3){
		//fprintf(stderr, "Invalid input destination.\n Please enter destination length in 3 charters\n");
		return FALSE;
	}
	
    for (int i=0;i<length;i++){
		if((destination[i] < 'A' && destination[i] > 'Z')) {
			//fprintf(stderr, "Invalid input destination.\n Please enter destination in capital letters\n");
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
//* Return Value: BOOLean (true if valid and false if not).
//*************************************************************************
//
//BOOL is_emergency_valid(BOOL emergency){
//	if (emergency == TRUE || emergency == FALSE)
//		return TRUE;
//	
//	//fprintf(stderr, "Invalid input emergency parameter.\n Please enter either TRUE or FALSE\n");
//	return FALSE;
//}

BOOL compare_flight_num(FLIGHT* flight,int flight_num){
	if (flight->flight_num == flight_num)
	{
		return TRUE;
	} else
	{
		return FALSE;
	}
}
