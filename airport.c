#include "ex2.h"
#include "runway.h"
#include "flight.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

extern AIRPORT airport;

typedef struct airport_t{
	RUNWAY* runway_list;
	RUNWAY* last_runway;
}AIRPORT;


AIRPORT* createAirport(){
	AIRPORT* airport = (AIRPORT*)malloc(sizeof(AIRPORT));
	airport->runway_list = NULL;
	airport->last_runway = NULL;
}

Result addRunway{int runway_num, FlightType runway_type){
	RUNWAY* new_runway = createRunway (runway_num, runway_type);
	
	if (new_runway != NULL && flight_doesnt_exists()){
		airport->last_runway->pNaxt = new_runway;
		airport->last_runway = new_runway;
		return SUCCESS;
	}
	
	return FAILURE;
}

bool flight_doesnt_exists(RUNWAY* runway, int flight_num){
	RUNWAY* temp_runway = airport->runway_list;
	while (temp_runway != NULL{
		isFlightExists (RUNWAY* runway, int flight_num)
	
}

Result removeRunway{int runway_num);
Result addFlightToAirport{int flight_num, FlightType flight_type, char destination[], BOOL emergency);
Result departFromRunway{int runway_num, int number_of_flights);
Result changeDest{char destination[],char new_destination[]);
Result delay{char destination[]);
void printAirport{)
void destroyAirport();
