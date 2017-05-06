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

static AIRPORT airport = (AIRPORT)malloc(sizeof(AIRPORT));

typedef struct airport_t{
	RUNWAY_ITEM* runway_list;
	RUNWAY_ITEM* last_runway;
}AIRPORT;

typedef struct runway_item{
	RUNWAY runway;
	RUNWAY_ITEM* next_runway;
}RUNWAY_ITEM;


Result addRunway{int runway_num, FlightType runway_type){
	RUNWAY* new_runway = createRunway (runway_num, runway_type);
	RUNWAY_ITEM temp_runway = (RUNWAY_ITEM)malloc(sizeof(RUNWAY_ITEM));

	
	if (new_runway != NULL && temp_runway !=NULL && runway_num_doesnt_exists(runway_num)){
		temp_runway->runway = *new_runway;
		temp_runway->next_runway = NULL;
		airport->last_runway->next_runway = temp_runway;
		airport->last_runway = temp_runway;
		destroyRunway (new_runway);
		return SUCCESS;
	}
	
	return FAILURE;
}

bool runway_num_doesnt_exists(int runway_num){
	
	RUNWAY* temp_runway = airport->runway_list;
	while (temp_runway != NULL{
		if (temp_runway->runway_num == runway_num)
			return 0;
		temp_runway = temp_runway->pNaxt;
	}
	
	return 1;
	
}

Result removeRunway{int runway_num){
		RUNWAY* temp_runway = int find_runway(runway_num);
}
Result addFlightToAirport{int flight_num, FlightType flight_type, char destination[], BOOL emergency);
Result departFromRunway{int runway_num, int number_of_flights);
Result changeDest{char destination[],char new_destination[]);
Result delay{char destination[]);
void printAirport{)
void destroyAirport();
