//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

#include "ex2.h"
#include "flight.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct flight_t{
	int flight_num;
	FlightType flight_type;
	char destination[DEST_CHAR_NUM];
	BOOL emergency;
	FLIGHT* pNext;
}FLIGHT;


//*************************************************************************
//* Function name: createFlight.
//* Description: creates a flight struct according to the inputted parameters.
//* Parameters: 
//*		-	flight_num – the flight number
//*		-	flight_type-  the flight type
//*		-	destination[] – an array[3] of the destination of the flight,
//*		-	emergency -  is the flight emergency (boolean).
//* Return Value: a pointer to a flight struct.
//*************************************************************************

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency){
	
	bool valid = is_num_valid(flight_num) && is_type_valid(flight_type) && is_destination_valid(destination) && is_emergency_valid(emergency);
	
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
	FLIGHT* temp_flight = flight->pNext;
	*flight=*temp_flight;
	// in case *flight=*temp_flight dont work:
		// flight->flight_num=temp_flight->flight_num;
		// flight->flight_type=temp_flight->flight_type;
		// flight->destination=temp_flight->destination;
		// flight->emergency=temp_flight->emergency;
	free(temp_flight);
}


//*************************************************************************
//* Function name: printFlight.
//* Description: prints to the user to description of the input flight.
//* Parameters:
//* 		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void printFlight(FLIGHT* flight){
	char emg = R;
	char type = D;
	if (emergency==TRUE) emg = E;
	if (FlightType==INTERNATIONAL) type = I;
	printf("Flight %n %d %s %d/n", flight->flight_num,type,flight->destination,emg);
}

//*************************************************************************
//* Function name: is_num_valid.
//* Description: checks if the input flight or runway number is valid (a number between 1 to MAX_ID).
//* Parameters:
//*		-	num – flight or runway number.
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_num_valid(int num){
	if (num >= 1 && num <= MAX_ID)
		return 1;
	
	fprintf(stderr, "Invalid input number.\n Please enter a number between 1 to %d\n", MAX_ID);
	return 0;
}


//*************************************************************************
//* Function name: is_type_valid.
//* Description: checks if the input flight or runway type is valid (either DOMESTIC or INTERNATIONAL).
//* Parameters:
//*		-	type – flight or runway type (enum FlightType).
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_type_valid(FlightType type){
	if (type == DOMESTIC || type == INTERNATIONAL)
		return 1;
	
	fprintf(stderr, "Invalid input type.\n Please enter either DOMESTIC or INTERNATIONAL\n");
	return 0;
}


//*************************************************************************
//* Function name: is_destination_valid.
//* Description: checks if the input flight destination is valid (3 capital letters array).
//* Parameters:
//*		-	destination – a char array of the flight destination.
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_destination_valid(char destination[]){
	length = strlen(destination);
	
	if (length != 3){
		fprintf(stderr, "Invalid input destination.\n Please enter destination length in 3 charters\n");
		return 0;
	}
	
    for (i=0;i<length;i++){
		if((destination[i] < 'A' && destination[i] > 'Z')) {
			fprintf(stderr, "Invalid input destination.\n Please enter destination in capital letters\n");
			return 0;
		}
	}
	
	return 1;
}


//*************************************************************************
//* Function name: is_emergency_valid.
//* Description: checks if the input flight emergency parameter is valid (TRUE or FALSE).
//* Parameters:
//*		-	emergency – flight emergency parameter (enum BOOL).
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_emergency_valid(BOOL emergency){
	if (emergency == TRUE || emergency == FALSE)
		return 1;
	
	fprintf(stderr, "Invalid input emergency parameter.\n Please enter either TRUE or FALSE\n");
	return 0;
}

bool compare_flight_num(FLIGHT* flight,int flight_num){
	if (flight->flight_num == flight_num)
	{
		return TRUE;
	} else
	{
		return FALSE;
	}
}
