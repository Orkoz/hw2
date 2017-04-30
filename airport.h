#ifndef AIRPOET_H_
#define AIRPOET_H_

#include <AirPort_Include_File.h>

typedef struct airport_t AIRPORT;

Result addRunway{int runway_num, FlightType runway_type};
Result removeRunway{int runway_num};
Result addFlightToAirport{int flight_num, FlightType flight_type, char destination[], BOOL emergency};
Result departFromRunway{int runway_num, int number_of_flights};
Result changeDest{char destination[],char new_destination[]};
Result delay{char destination[]};
void printAirport{}
void destroyAirport();

#endif /* AIRPOET_H_*/

