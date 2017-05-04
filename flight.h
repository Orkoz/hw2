/* flight.h - intarface to an Flight ADT which implements a singal flight*/


#ifndef FLIGHT_H_
#define FLIGHT_H_

#include "AirPort_Include_File.h"

typedef struct flight_t FLIGHT;

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency);
void destroyFlight(FLIGHT* flight);
void printFlight(FLIGHT* flight);

#endif /* FLIGHT_H_*/