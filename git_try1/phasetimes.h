#ifndef phasetimes_H
#define phasetimes_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

//a triple item object to encaspsulate wave phase, minutes, seconds
class Phasetimes
{
public:
	//constructor (default) empty object
	Phasetimes();

	//add parameters to phasetimes object
	void add_phasetime(string iphase, int iminutes, int iseconds);

	//takes UTC times and travel times as input, returns arrival time as a string
	string get_arrival(int eventhrs, int eventmins, int eventsecs, int travelmins, int travelsecs);

	//gets phase name
	string get_phase() const;

	//gets number of minutes
	int get_mins() const;

	//gets number of seconds
	int get_secs() const;

	string phase;

private:

	int minutes;
	int seconds;
};

#endif
