#ifndef GreatCircleDist
#define GreatCircleDist

//converts decimal degrees to radians
double convert_torad(double decdegrees);

//converts rad to degrees
double convert_todeg(double rad);

//calculates difference between source and station longitudes
double change_long(double longsource, double longstation);

//calculates the central angle between two locations in radians
double get_central(double latsource, double latstation, double longsource, double longstation);

//calculates great circle distance between two locations in KM
double get_distance(double centralangle);

//converts value in km to metres equivalent
double convertkm_tomet(double km);

//compares two floating point values to see if they are equal (within small fraction)
bool doub_is_equal(double a, double b, double epsilon = 0.001);

//calculates the azimuth from the station to the source location
double get_azimuth(double latsource, double latstation, double longsource, double longstation);

#endif
