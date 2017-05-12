/* flight.h - intarface to an Flight ADT which implements a singal flight*/


#ifndef FLIGHT_H_
#define FLIGHT_H_

#include <stdbool.h>

#ifndef EX2_H_
#include "ex2.h"
#endif

//#include "stdio.h"
//#include "stdlib.h"

typedef struct flight_t FLIGHT;

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency);
void destroyFlight(FLIGHT* flight);
void printFlight(FLIGHT* flight);


BOOL is_num_valid(int num);
BOOL is_destination_valid(char destination[]);
BOOL compare_flight_num(FLIGHT* flight,int flight_num);
bool compare_flight_dest(FLIGHT* flight, char destination[]);
void change_flight_dest(FLIGHT* flight, char destination[]);
int get_flight_num(FLIGHT* flight);


#endif /* FLIGHT_H_*/