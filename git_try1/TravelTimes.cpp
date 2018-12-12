#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>

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
	else if (degrees >= 10 && degrees <= 106)
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
	//bool found = false;
	string error1 = "ERR1";
	string error2 = "ERR2";

	ifstream in_file;
	in_file.open("traveltime30KM.txt");
	if (in_file.fail())
	{
		cout << "Could not open traveltime30KM.txt" << endl;
		return error1;
	}

	string line;
	string degstr;

	while (getline(in_file, line))
	{
		if (degrees < 10 || degrees > 99)
		{
			degstr = line.substr(0, 3);
		}
		else
		{
			degstr = line.substr(0, 2);

		}
		
		//deg = stod(degstr);
		ostringstream degreestrm;
		degreestrm << degrees;
		string degreestring = degreestrm.str();

		
		if (degstr == degreestring)
		{
			return line;
			
		}	
	}
	cout << "Could not find a match" << endl;
	return error2;
}
