/* flight.h - intarface to an Flight ADT which implements a singal flight*/


#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "ex2.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct flight_t FLIGHT;

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency);
void destroyFlight(FLIGHT* flight);
void printFlight(FLIGHT* flight);

bool is_num_valid(int num);
bool is_type_valid(FlightType type);
bool is_destination_valid(char destination[]);
bool is_emergency_valid(BOOL emergency);

#endif /* FLIGHT_H_*/