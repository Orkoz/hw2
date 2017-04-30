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

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency){
	
	FLIGHT* temp_flight = (FLIGHT*)malloc(sizeof(FLIGHT));
	temp_flight->flight_num=flight_num;
	temp_flight->flight_type=flight_type;
	temp_flight->destination=destination;
	temp_flight->emergency=emergency;
	
	return temp_flight;
}

void destroyFlight(*FLIGHT flight);
void printFlight(*FLIGHT flight);

