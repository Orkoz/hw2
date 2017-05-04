//*************************************************************************
//* Function name:
//* Description:
//* Parameters:
//* Return Value:
//*************************************************************************

#include <AirPort_Include_File.h>

typedef struct flight_t{
	int flight_num;
	FlightType flight_type;
	char destination[DEST_CHAR_NUM];
	BOOL emergency;
	struct FLIGHT* pNext;
}FLIGHT;


//*************************************************************************
//* Function name: createFlight.
//* Description: creates a flight struct according to the inputted parameters.
//* Parameters: 
//*		-	flight_num – the flight number
//*		-	flight_type-  the flight type
//*		-	destination[] – an array[3] of the destination of the flight,
//*		-	emergency -  is the flight emergency (boolean).
//* Return Value: a pointer to a flight struct.
//*************************************************************************

FLIGHT* createFlight(int flight_num, FlightType flight_type, char destination[], BOOL emergency){
	
	bool valid = is_num_valid(flight_num) && is_type_valid(flight_type) && is_destination_valid(destination) && is_emergency_valid(emergency);
	
	if (valid)
	{
		FLIGHT* temp_flight = (FLIGHT*)malloc(sizeof(FLIGHT));
		temp_flight->flight_num=flight_num;
		temp_flight->flight_type=flight_type;
		strcpy(temp_flight->destination,destination);
		temp_flight->emergency=emergency;
		return temp_flight;
	}

	return null;
}


//*************************************************************************
//* Function name: destroyFlight.
//* Description: removes a flight from the flight list of the runway its belong to.
//* Parameters: 
//*		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void destroyFlight(FLIGHT* flight){
	FLIGHT* temp_flight = flight->pNext;
	*flight=*temp_flight;
	// in case *flight=*temp_flight dont work:
		// flight->flight_num=temp_flight->flight_num;
		// flight->flight_type=temp_flight->flight_type;
		// flight->destination=temp_flight->destination;
		// flight->emergency=temp_flight->emergency;
	free(temp_flight);
}


//*************************************************************************
//* Function name: printFlight.
//* Description: prints to the user to description of the input flight.
//* Parameters:
//* 		-	flight– a pointer to a flight struct.
//* Return Value: None.
//*************************************************************************

void printFlight(FLIGHT* flight){
	char emg = R;
	char type = D;
	if (emergency==TRUE) emg = E;
	if (FlightType==INTERNATIONAL) type = I;
	printf("Flight %n %d %s %d", flight->flight_num,type,flight->destination,emg);
}
