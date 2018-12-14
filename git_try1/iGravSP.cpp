#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <iterator>
#include <algorithm>

#include "GreatCircle.h"
#include "Traveltimes.h"
#include "Phasetimes.h"
#include "iGravSP.h"

using namespace std;

int srctimeMIN, srctimeSEC, srctimeHR;

//display phase and time results to user
void display(Phasetimes x, bool a, double stationLong)
{
	int offset = x.get_UTCoffset(stationLong);
	if (offset == 999)
	{
		cout << "Error: UTC offset returned invalid value.";
		return;
	}
	string arrivaltime;
	string ph = x.get_phase();
	int mn = x.get_mins();
	int sc = x.get_secs();

	if (a == true)
	{
		 arrivaltime = x.get_arrival(srctimeHR, srctimeMIN, srctimeSEC, mn, sc, offset);
	}
	else
	{
		arrivaltime = "N/A";
	}
	
	//check for no data or partial data entries
	if (sc == 999)
	{
		sc = 0;
	}
	if (mn == 999 && sc == 0)
	{
		cout << right << setw(7) << ph << "     --------------------------------------------------" << endl;
	}
	else
	{
		cout << right << setw(7) << ph << right << setw(7) << mn << "  minutes" << right << setw(7) << sc << "  seconds" << right << setw(18) << arrivaltime << endl;
	}
}

int main()
{
	//get search method from user
	int input;
	do
	{
		cout << "Enter search method number:" << endl << endl;
		cout << fixed << right << setw(20) << "City Name" << "    1" << endl << fixed << right << setw(20) << "Lat/Long" << "    2" << endl;
		cin >> input;
		if (cin.fail())
		{
			cout << endl << "Enter number only" << endl << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip bad input
			
		}
	} while (input < 1 || input > 2);

	//open city location file
	ifstream in_file;
	in_file.open("wcity.txt");
	if (!in_file)
	{
		cout << "could not open wcity.txt file";
		return 1;
	}

	string line;
	istringstream stationline;
	istringstream sourceline;
	bool statfound = false;
	bool srcfound = false;
	string citystatin;
	string citysrcin;

	string longstatin;
	string latstatin;
	string longsrcin;
	string latsrcin;

	if (input == 1)
	{
		cout << endl << "Enter city STATION name using underscore chars for spaces (ex: ""Salt_Lake_City"" or ""St._Louis""): ";
		cin >> citystatin;
		cout << endl << "Station Chosen: " << citystatin << endl << endl;
		cout << "Enter city SOURCE name using underscore chars for spaces (ex: ""Salt_Lake_City"" or ""St._Louis""): ";
		cin >> citysrcin;
		cout << endl << "Source Chosen:  " << citysrcin << endl << endl;
	}
	else if (input == 2)
	{
		cout << endl << "Enter STATION longitude in decimal degrees (ex: ""-113.79"" or ""178.43""): ";
		cin >> longstatin;
		cout << endl << "Enter STATION latitude in decimal degrees (ex: ""-3.66"" or ""64.49""): ";
		cin >> latstatin;
		cout << endl << "Station Long/Lat:  " << longstatin << " / " << latstatin << endl << endl;
		cout << endl << "Enter SOURCE longitude in decimal degrees (ex: ""-113.79"" or ""178.43""): ";
		cin >> longsrcin;
		cout << endl << "Enter SOURCE latitude in decimal degrees (ex: ""-3.66"" or ""64.49""): ";
		cin >> latsrcin;
		cout << endl << "Source Long/Lat:  " << longsrcin << " / " << latsrcin << endl << endl;
	}

	double stationLat;
	double stationLong;
	double sourceLat;
	double sourceLong;

	//check if station location is @ Queen's iGrav
	bool is_Dirk = false;

	//search by City
	if (input == 1)
	{
		
		if (citystatin == "Kingston")
		{
			is_Dirk = true;
		}
		while (getline(in_file, line))
		{
			if (statfound == false || srcfound == false)
			{
				//skip (-) if needed
				int i = 0;
				if (!isdigit(line[i]))
				{
					i++;
				}
				//extract city in line
				while (!isalpha(line[i]))
				{
					i++;
				}
				string citycheck = line.substr(i);
				if (citycheck == citystatin)
				{
					statfound = true;
					stationline.str(line);
				}
				//check for match
				if (citycheck == citysrcin)
				{
					srcfound = true;
					sourceline.str(line);
				}
			}
		}
		if (statfound == false && srcfound == true)
		{
			cout << "Station city not found in database. Please try again or search by Lat/Long." << endl;
			return 2;
		}
		if (srcfound == false && statfound == true)
		{
			cout << "Source city not found in database. Please try again or search by Lat/Long." << endl;
			return 3;
		}
		if (statfound == false && srcfound == false)
		{
			cout << "Station and Source cities not found in database. Please try again or search by Lat/Long." << endl;
			return 4;
		}

		string citystation;
		string citysource;

		stationline >> stationLong >> stationLat >> citystation;
		sourceline >> sourceLong >> sourceLat >> citysource;

		cout << "station: " << right << setw(12) << setprecision(2) << stationLong << "  " << stationLat << "    " << citystation << endl;
		cout << "source: " << right << setw(12) << sourceLong << "  " << sourceLat << "    " << citysource << endl << endl;
	}

	//Calculate using Lat/Long
	if (input == 2)
	{
		stationLong = stod(longstatin);
		stationLat = stod(latstatin);
		sourceLong = stod(longsrcin);
		sourceLat = stod(latsrcin);
		

		if (stationLat < MINLAT || stationLat > MAXLAT || sourceLat < MINLAT || sourceLat > MAXLAT)
		{
			cout << "Latitudes must be between -90 & +90  decimal degrees.";
			return 5;
		}
		if (stationLong < MINLONG || stationLong > MAXLONG || sourceLong < MINLONG || sourceLong > MAXLONG)
		{
			cout << "Longitudes must be between -180 & +180  decimal degrees.";
			return 6;
		}
		
		if ((doub_is_greater(stationLat, KING_MINLAT)) && !(doub_is_greater(stationLat, KING_MAXLAT)))
		{
			is_Dirk = true;
		}
	}

	string srctimestrHRS, srctimestrMIN, srctimestrSEC;

	//track choice to enter time of event or not
	bool UTC = false;

	string YN;
	string srctimestr;
	cout << "Enter time of event (UTC)?   Y/N: " << endl;
	cin >> YN;
	if (YN == "Y" || YN == "y")
	{
		UTC = true;
		do
		{
			cout << "Enter UTC time of source event (ex: ""00:07:56"" or ""21:45:09""):  ";
			cin >> srctimestr;
			if (srctimestr.size() != 8)
			{
				cout << "Invalid time input, try again." << endl;
			}
	
		} while (srctimestr.size() != 8);
		
		srctimestrHRS = srctimestr.substr(0, 2);
		srctimestrMIN = srctimestr.substr(3, 2);
		srctimestrSEC = srctimestr.substr(6, 2);
		srctimeHR = stoi(srctimestrHRS);
		srctimeMIN = stoi(srctimestrMIN);
		srctimeSEC = stoi(srctimestrSEC);
	}
	
	//Calculate angle, distance, and azimuth
	double centralangle = get_central(sourceLat, stationLat, sourceLong, stationLong);
	double distancekm = get_distance(centralangle);
	double azimuth = get_azimuth(sourceLat, stationLat, sourceLong, stationLong);

	//print results
	cout << "Distance in Km:  " << right << setw(17) << setprecision(2) << distancekm << " Km" << endl;
	cout << "Central Angle:  " << right << setw(15) << setprecision(2) << centralangle << " rad" << endl;
	cout << "Azimuth from station:  " << right << setw(10) << setprecision(2) << azimuth << " degrees" << endl << endl;

	//convert values for travel time search
	double distmetres = convertkm_tomet(distancekm);
	int distdegree = convertmet_todegree(distmetres);

	//find travel times
	string traveltimedata = get_TravelTimes(distdegree);
	//check for errors
	if (traveltimedata == "ERR1")
	{
		return -1;
	}
	if (traveltimedata == "ERR2")
	{
		return -2;
	}

	//encapsulate travel time data items
	stringstream strm;
	istringstream strmvalues;
	string P = "P", PP = "PP", PcP = "PcP", PKPab = "PKPab", PKPbc = "PKPbc", PKPdf = "PKPsf", S = "S", SS = "SS", ScS = "ScS", SKSac = "SKSac", SKSdf = "SKSdf";

	int distdeg;
	int Pmin, PPmin, PcPmin, PKPabmin, PKPbcmin, PKPdfmin, Smin, SSmin, ScSmin, SKSacmin, SKSdfmin, SPDIFFmin, Psec, PPsec, PcPsec, PKPabsec, PKPbcsec, PKPdfsec, Ssec, SSsec, ScSsec, SKSacsec, SKSdfsec, SURFmin, SURFsec, SPDIFFsec;
	
	//Surface wave calculation
	int surftime = distmetres / SURF_VEL;
	SURFmin = surftime / 60;
	SURFsec = surftime % 60;

	strm.str(traveltimedata);
	
	strm >> distdeg >> Pmin >> Psec >> PPmin >> PPsec >> PcPmin >> PcPsec >> PKPabmin >> PKPabsec >> PKPbcmin >> PKPbcsec >> PKPdfmin >> PKPdfsec >> Smin >> Ssec >> SSmin >> SSsec >> ScSmin >> ScSsec >> SKSacmin >> SKSacsec >> SKSdfmin >> SKSdfsec;

	// S - P calculation
	SPDIFFmin = Smin - Pmin;
	SPDIFFsec = Ssec + (60 - Psec);
	
	cout << right << setw(7) << "PHASE" << right << setw(25) << " TRAVEL TIME" << right << setw(30) << "ARRIVAL TIME (LOCAL)" << endl << endl;

	Phasetimes Pw;
	Pw.add_phasetime(P, Pmin, Psec);
	display(Pw, UTC, stationLong);
	Phasetimes PPw;
	PPw.add_phasetime(PP, PPmin, PPsec);
	display(PPw, UTC, stationLong);
	Phasetimes PcPw;
	PcPw.add_phasetime(PcP, PcPmin, PcPsec);
	display(PcPw, UTC, stationLong);
	Phasetimes PKPabw;
	PKPabw.add_phasetime(PKPab, PKPabmin, PKPabsec);
	display(PKPabw, UTC, stationLong);
	Phasetimes PKPbcw;
	PKPbcw.add_phasetime(PKPbc, PKPbcmin, PKPbcsec);
	display(PKPbcw, UTC, stationLong);
	Phasetimes PKPdfw;
	PKPdfw.add_phasetime(PKPdf, PKPdfmin, PKPdfsec);
	display(PKPdfw, UTC, stationLong);
	Phasetimes Sw;
	Sw.add_phasetime(S, Smin, Ssec);
	display(Sw, UTC, stationLong);
	Phasetimes SSw;
	SSw.add_phasetime(SS, SSmin, SSsec);
	display(SSw, UTC, stationLong);
	Phasetimes ScSw;
	ScSw.add_phasetime(ScS, ScSmin, ScSsec);
	display(ScSw, UTC, stationLong);
	Phasetimes SKSacw;
	SKSacw.add_phasetime(SKSac, SKSacmin, SKSacsec);
	display(SKSacw, UTC, stationLong);
	Phasetimes SKSdfw;
	SKSdfw.add_phasetime(SKSdf, SKSdfmin, SKSdfsec);
	display(SKSdfw, UTC, stationLong);

	cout << right << setw(7) << "S - P" << right << setw(7) << SPDIFFmin << "  minutes" << right << setw(7) << SPDIFFsec << "  seconds" << endl;
	cout << right << setw(7) << "Surface" << right << setw(7) << SURFmin << "  minutes" << right << setw(7) << SURFsec << "  seconds" << endl;
	return 0;
}