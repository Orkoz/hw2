#ifndef AIRPOET_H_
#define AIRPOET_H_

#ifndef EX2_H_
#include "ex2.h"
#endif

#ifndef RUNWAY_H_
#include "runway.h"
#endif

#ifndef FLIGHT_H_
#include "flight.h"
#endif

//#include "stdio.h"
//#include "stdlib.h"

typedef struct airport_t AIRPORT;
typedef struct runway_item RUNWAY_ITEM;
Result addRunway(int runway_num, FlightType runway_type);
Result removeRunway(int runway_num);
Result addFlightToAirport(int flight_num, FlightType flight_type, char destination[], BOOL emergency);
Result departFromRunway(int runway_num, int number_of_flights);
Result changeDest(char destination[],char new_destination[]);
Result delay(char destination[]);
void printAirport();
void destroyAirport();
RUNWAY* runway_num_exists(int runway_num);
BOOL create_airport();


#endif /* AIRPOET_H_*/


