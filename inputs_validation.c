#include <AirPort_Include_File.h>

//*************************************************************************
//* Function name: is_num_valid.
//* Description: checks if the input flight or runway number is valid (a number between 1 to MAX_ID).
//* Parameters:
//*		-	num – flight or runway number.
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_num_valid(int num){
	if (num >= 1 && num <= MAX_ID)
		return 1;
	
	fprintf(stderr, "Invalid input number.\n Please enter a number between 1 to %d\n", MAX_ID);
	return 0;
}


//*************************************************************************
//* Function name: is_type_valid.
//* Description: checks if the input flight or runway type is valid (either DOMESTIC or INTERNATIONAL).
//* Parameters:
//*		-	type – flight or runway type (enum FlightType).
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_type_valid(FlightType type){
	if (type == DOMESTIC || type == INTERNATIONAL)
		return 1;
	
	fprintf(stderr, "Invalid input type.\n Please enter either DOMESTIC or INTERNATIONAL\n");
	return 0;
}


//*************************************************************************
//* Function name: is_destination_valid.
//* Description: checks if the input flight destination is valid (3 capital letters array).
//* Parameters:
//*		-	destination – a char array of the flight destination.
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_destination_valid(char destination[]){
	length = strlen(destination);
	
	if (length != 3){
		fprintf(stderr, "Invalid input destination.\n Please enter destination length in 3 charters\n");
		return 0;
	}
	
    for (i=0;i<length;i++){
		if((destination[i] < 'A' && destination[i] > 'Z')) {
			fprintf(stderr, "Invalid input destination.\n Please enter destination in capital letters\n");
			return 0;
		}
	}
	
	return 1;
}


//*************************************************************************
//* Function name: is_emergency_valid.
//* Description: checks if the input flight emergency parameter is valid (TRUE or FALSE).
//* Parameters:
//*		-	emergency – flight emergency parameter (enum BOOL).
//* Return Value: boolean (true if valid and false if not).
//*************************************************************************

bool is_emergency_valid(BOOL emergency){
	if (emergency == TRUE || emergency == FALSE)
		return 1;
	
	fprintf(stderr, "Invalid input emergency parameter.\n Please enter either TRUE or FALSE\n");
	return 0;
}