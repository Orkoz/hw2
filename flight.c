//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

#include <AirPort_Include_File.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flight_t{
	int flight_num;
	FlightType flight_type;
	char destination[3];
	BOOL emergency;
	struct FLIGHT* pNext;
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
	
	FLIGHT* temp_flight = (FLIGHT*)malloc(sizeof(FLIGHT));
	if (temp_flight)
	{
		temp_flight->flight_num=flight_num;
		temp_flight->flight_type=flight_type;
		temp_flight->destination=destination;
		temp_flight->emergency=emergency;
		return temp_flight;
	} else {
		return NULL;
	}

}

//*************************************************************************
//* Function name: destroyFlight.
//* Description: removes a flight from the flight list of the runway its belong to.
//* Parameters: 
//*		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************


void destroyFlight(*FLIGHT flight){
	FLIGHT* temp_flight = flight->pNext;
	flight=delet_flight;
	free(temp_flight);
}

//*************************************************************************
//* Function name: printFlight.
//* Description: prints to the user to description of the input flight.
//* Parameters:
//* 		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void printFlight(*FLIGHT flight){
	char emg = R;
	char type = D;
	if (emergency==TRUE) emg = E;
	if (FlightType==INTERNATIONAL) type = I;
	printf("Flight %n %d %s %d", flight->flight_num,type,flight->destination,emg);
}
