#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

#include "Phasetimes.h"

using namespace std;

double convertdeg_tometres(double degrees)
{
	//assume 1 degree = 111,139 metres
	double meters = degrees * 111139;
	return meters;
}

int convertmet_todegree(double metres)
{
	//assume 1 degree = 111,139 metres
	double degrees = metres / 111139.0;

	if (degrees < 10)
	{
		degrees = floor(((2 * degrees) + 0.5) / 2);
		return degrees;
	}
	else if (degrees >= 10 && degrees <= 180)
	{
		degrees = nearbyint(degrees);
		return degrees;
	}
	else
	{
		return -1;
	}
}

string get_TravelTimes(int degrees)
{
	string error1 = "ERR1";
	string error2 = "ERR2";

	ifstream in_file;
	in_file.open("TravelTimes0km999.txt");
	if (in_file.fail())
	{
		cout << "Could not open TravelTimes0km999.txt" << endl;
		return error1;
	}

	string line;
	string degstr;

	while (getline(in_file, line))
	{
		int i = 0;
		while (!isspace(line[i]))
		{
			i++;
		}
		degstr = line.substr(0, i);
		
		ostringstream degreestrm;
		degreestrm << degrees;
		string degreestring = degreestrm.str();

		
		if (degstr == degreestring)
		{
			return line;
			
		}	
	}
	cout << "Could not find a match for this distance." << endl;
	return error2;
}




