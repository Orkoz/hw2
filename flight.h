/* flight.h - intarface to an Flight ADT which implements a singal flight*/

//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

#ifndef FLIGHT_H_
#define FLIGHT_H_

typedef struct flight_t FLIGHT;

FLIGHT createFlight{int flight_num, FlightType flight_type, char destination[], BOOL emergency};
void destroyFlight{*FLIGHT flight};
void printFlight{*FLIGHT flight};

#endif /* FLIGHT_H_*/