#ifndef RUNWAY_H_
#define RUNWAY_H_

#ifndef EX2_H_
#include "ex2.h"
#endif

#ifndef FLIGHT_H_
#include "flight.h"
#endif

//#include "stdio.h"
//#include "stdlib.h"

typedef struct runway_t RUNWAY;
typedef struct flight_item FLIGHT_ITEM;

RUNWAY* createRunway (int runway_num, FlightType runway_type);
void destroyRunway (RUNWAY* runway);
bool isFlightExists (RUNWAY* runway, int flight_num);
FLIGHT* isFlightDest(RUNWAY* runway, char dest[]);
int getFlightNum (RUNWAY* runway);
Result addFlight (RUNWAY* runway, FLIGHT* flight);
Result removeFlight(RUNWAY* runway, int flight_num);
Result depart (RUNWAY* runway);
void printRunway (RUNWAY* runway);
int get_runway_num(RUNWAY* runway);
FlightType get_runway_type(RUNWAY* runway);

#endif /* RUNWAY_H_*/
