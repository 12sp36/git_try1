#ifndef Traveltimes_H
#define Traveltimes_H

#include <string>

using namespace std;

//converts distance in degrees to metres equivalent
double convertdeg_tometres(double degrees);

//converts distance in metres to degrees equivalent
int convertmet_todegree(double metres);

//searches traveltime30KM.txt for distance (in degrees) and returns the matching line of data containing travel times
string get_TravelTimes(int degrees);

#endif


