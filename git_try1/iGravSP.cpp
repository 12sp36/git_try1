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


using namespace std;

void display(Phasetimes x)
{
	string ph = x.get_phase();
	int mn = x.get_mins();
	int sc = x.get_secs();

	if (mn == 999)
	{
		cout << "Phase: " << right << setw(7) << ph << "   --------------------------------------------" << endl;
	}
	else
	{
		cout << "Phase: " << right << setw(7) << ph << "   time: " << right << setw(10) << mn << "  minutes" << right << setw(10) << sc << "  seconds" << endl;
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
			//search by City
			if (input == 1)
			{
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

				if (citycheck == citysrcin)
				{
					srcfound = true;
					sourceline.str(line);
				}
			}
			//search by lat/long
			if (input == 2)
			{
				int j = i;
				while (!isspace(line[j]))
				{
					j++;
				}
				string longneg;
				string longvalue = line.substr(i, j - 1);
				string longcheck;
				
				if (i = 1)
				{
					longneg = "-";
					longneg.append(longvalue);
					longcheck = longneg;
				}
				else
				{
					longcheck = longvalue;
				}
			
				while (!isalpha(line[i]))
				{
					i++;
				}
				//if (!isdigit(line[j + 1]))
				//{
				//	j++;
				//}
				string latcheck = line.substr(j + 1, i - 2 - j);

				double longstatindoub = stod(longstatin);
				double latstatindoub = stod(latstatin);
				double longsrcindoub = stod(longsrcin);
				double latsrcindoub = stod(latsrcin);
				double longcheckdoub = stod(longcheck);
				double latcheckdoub = stod(latcheck);

				//check if line matches station
				bool statlongequal = doub_is_equal(longstatindoub, longcheckdoub);
				bool statlatequal = doub_is_equal(latstatindoub, latcheckdoub);
				if (statlongequal == true && statlatequal == true)
				{
					statfound = true;
					stationline.str(line);
				}

				//check if line matches source
				bool srclongequal = doub_is_equal(longsrcindoub, longcheckdoub);
				bool srclatequal = doub_is_equal(latsrcindoub, latcheckdoub);
				if (srclongequal == true && srclatequal == true)
				{
					srcfound = true;
					sourceline.str(line);
				}
			}
		}
	}
	
	string citystation;
	string citysource;
	double stationLat;
	double stationLong;
	double sourceLat;
	double sourceLong;

	stationline >> stationLong >> stationLat >> citystation;
	sourceline >> sourceLong >> sourceLat >> citysource;

	cout << "station: " << fixed << right << setw(12) << setprecision(2) << stationLong << "  " << stationLat << "    " << citystation << endl;
	cout << "source: " << right << setw(13) << sourceLong << "  " << sourceLat << "  " << citysource << endl << endl;

	double centralangle = get_central(sourceLat, stationLat, sourceLong, stationLong);
	double distancekm = get_distance(centralangle);
	double azimuth = get_azimuth(sourceLat, stationLat, sourceLong, stationLong);

	cout << setw(18) << "Distance in Km:  " << right << setw(19) << setprecision(2) << distancekm << "  Km" << endl;
	cout << setw(18) << "Central Angle:  " << right << setw(17) << setprecision(2) << centralangle << "  rad" << endl;
	cout << setw(18) << "Azimuth from station:  " << right << setw(15) << setprecision(2) << azimuth << "  degrees" << endl << endl;

	double distmetres = convertkm_tomet(distancekm);
	int distdegree = convertmet_todegree(distmetres);
	string traveltimedata = get_TravelTimes(distdegree);
	if (traveltimedata == "ERR1")
	{
		return -1;
	}
	if (traveltimedata == "ERR2")
	{
		return -2;
	}

	stringstream strm;
	istringstream strmvalues;
	string P = "P", PP = "PP", PcP = "PcP", PKPab = "PKPab", PKPbc = "PKPbc", PKPdf = "PKPsf", S = "S", SS = "SS", ScS = "ScS", SKSac = "SKSac", SKSdf = "SKSdf";

	int distdeg;
	int Pmin, PPmin, PcPmin, PKPabmin, PKPbcmin, PKPdfmin, Smin, SSmin, ScSmin, SKSacmin, SKSdfmin, SPDIFFmin, Psec, PPsec, PcPsec, PKPabsec, PKPbcsec, PKPdfsec, Ssec, SSsec, ScSsec, SKSacsec, SKSdfsec, SPDIFFsec;
	
	strm.str(traveltimedata);
	
	strm >> distdeg >> Pmin >> Psec >> PPmin >> PPsec >> PcPmin >> PcPsec >> PKPabmin >> PKPabsec >> PKPbcmin >> PKPbcsec >> PKPdfmin >> PKPdfsec >> Smin >> Ssec >> SSmin >> SSsec >> ScSmin >> ScSsec >> SKSacmin >> SKSacsec >> SKSdfmin >> SKSdfsec;

	SPDIFFmin = Smin - Pmin;
	SPDIFFsec = Ssec - Psec;

	Phasetimes Pw;
	Pw.add_phasetime(P, Pmin, Psec);
	display(Pw);
	Phasetimes PPw;
	PPw.add_phasetime(PP, PPmin, PPsec);
	display(PPw);
	Phasetimes PcPw;
	PcPw.add_phasetime(PcP, PcPmin, PcPsec);
	display(PcPw);
	Phasetimes PKPabw;
	PKPabw.add_phasetime(PKPab, PKPabmin, PKPabsec);
	display(PKPabw);
	Phasetimes PKPbcw;
	PKPbcw.add_phasetime(PKPbc, PKPbcmin, PKPbcsec);
	display(PKPbcw);
	Phasetimes PKPdfw;
	PKPdfw.add_phasetime(PKPdf, PKPdfmin, PKPdfsec);
	display(PKPdfw);
	Phasetimes Sw;
	Sw.add_phasetime(S, Smin, Ssec);
	display(Sw);
	Phasetimes SSw;
	SSw.add_phasetime(SS, SSmin, SSsec);
	display(SSw);
	Phasetimes ScSw;
	ScSw.add_phasetime(ScS, ScSmin, ScSsec);
	display(ScSw);
	Phasetimes SKSacw;
	SKSacw.add_phasetime(SKSac, SKSacmin, SKSacsec);
	display(SKSacw);
	Phasetimes SKSdfw;
	SKSdfw.add_phasetime(SKSdf, SKSdfmin, SKSdfsec);
	display(SKSdfw);

	return 0;
}