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

void destroyFlight(*FLIGHT flight){
	FLIGHT* temp_flight = flight->pNext;
	flight=delet_flight;
	free(temp_flight);
}
void printFlight(*FLIGHT flight){
	char emg = R;
	char type = D;
	if (emergency==TRUE) emg = E;
	if (FlightType==INTERNATIONAL) type = I;
	printf("Flight %n %d %s %d", flight->flight_num,type,flight->destination,emg);
}
