#ifndef RUNWAY_H_
#define RUNWAY_H_

#include <AirPort_Include_File.h>

typedef struct runway_t RUNWAY;

RUNWAY* createRunway (int runway_num, FlightType runway_type);
void destroyRunway (RUNWAY* runway);
bool isFlightExists (RUNWAY* runway, int flight_num);
int getFlightNum (RUNWAY* runway);
Result addFlight (RUNWAY* runway, FLIGHT* flight);
Result removeFlight(RUNWAY* runway, int flight_num);
Result depart (RUNWAY* runway);
void printRunway (RUNWAY* runway);

#endif /* RUNWAY_H_*/
