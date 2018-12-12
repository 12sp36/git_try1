#include <iostream>
#include <cmath>

using namespace std;

//mean Earth radius (spherical Earth) WGS84 ellipsoid
const int RADIUS = 6371;
const double PI = 3.141592653589793238463;

//global params


double convert_torad(double decdegrees)
{
	double rad = decdegrees * PI / 180.0;
	return rad;
}

double convert_todeg(double rad)
{
	double deg = rad * 180.0 / PI;
	return deg;
}

double change_long(double longsource, double longstation)
{
	double radsource = convert_torad(longsource);
	double radstation = convert_torad(longstation);
	double longchange = abs(radsource - radstation);
	return longchange;
}


double get_central(double latsource, double latstation, double longsource, double longstation)
{
	double latsrc = convert_torad(latsource);
	double latstat = convert_torad(latstation);
	double deltalong = change_long(longsource, longstation);


	double central = acos((sin(latsrc) * sin(latstat)) + (cos(latsrc) * cos(latstat) * cos(deltalong)));
	return central;
}

double get_distance(double centralangle)
{
	double distance = centralangle * RADIUS;
	return distance;
}

double convertkm_tomet(double km)
{
	double metres = km * 1000.0;
	return metres;
}

bool doub_is_equal(double a, double b, double epsilon = 0.001)
{
	if (abs(a - b) < epsilon)
	{
		return true;
	}
}

double get_azimuth(double latsource, double latstation, double longsource, double longstation)
{
	double deltalongaz = change_long(longsource, longstation);
	double latsourcerad = convert_torad(latsource);
	double latstatrad = convert_torad(latstation);
	double longsourcerad = convert_torad(longsource);
	double longstatrad = convert_torad(longstation);

	double x = cos(latstatrad) * sin(latsourcerad) - sin(latstatrad) * cos(latsourcerad) * cos(deltalongaz);
	double y = sin(deltalongaz) * cos(latsourcerad);

	double azimuthrad = atan2(y, x);
	int azimuthdegUN = convert_todeg(azimuthrad);

	int azimuth;
	if (azimuthdegUN < 0)
	{
		azimuth = (azimuthdegUN + 360) % 360;
	}
	else
	{
		azimuth = azimuthdegUN;
	}
		
	
	return azimuth;
}