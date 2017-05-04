#ifndef inputs_validation_H_
#define inputs_validation_H_

#include <AirPort_Include_File.h>

bool is_num_valid(int num);
bool is_type_valid(FlightType type);
bool is_destination_valid(char destination[]);
bool is_emergency_valid(BOOL emergency);

#endif /* inputs_validation_H_*/