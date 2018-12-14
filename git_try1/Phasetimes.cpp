#include "phasetimes.h"
#include <string>

Phasetimes::Phasetimes()
{
	minutes = 0;
	seconds = 0;
}

void Phasetimes::add_phasetime(string iphase, int iminutes, int iseconds)
{
	phase.assign(iphase);
	minutes = iminutes;
	seconds = iseconds;
}

string Phasetimes::get_arrival(int eventhrs, int eventmins, int eventsecs, int travelmins, int travelsecs)
{
	int arrivalhrs = eventhrs;
	int arrivalmins = eventmins + travelmins;
	int arrivalsecs = eventsecs + travelsecs;

	if (arrivalmins > 60)
	{
		arrivalhrs++;
		arrivalmins = arrivalmins % 60;
		if (arrivalhrs >= 24)
		{
			arrivalhrs = 0;
		}
	}
	if (arrivalsecs > 60)
	{
		arrivalmins++;
		arrivalsecs = arrivalsecs % 60;
	}

	string arrivaltime;
	string hrsstr;
	string minsstr;
	string secsstr;
	string zero = "0";

	//store arrival hours, mins, secs
	if (arrivalhrs == 0)
	{
		hrsstr = "00:";
	}
	else
	{
		hrsstr = (to_string(arrivalhrs)).append(":");
	}
	minsstr = (to_string(arrivalmins)).append(":");
	if (minsstr.length() < 3)
	{
		minsstr = zero.append(minsstr);
	}
	secsstr = to_string(arrivalsecs);
	if (secsstr.length() < 2)
	{
		secsstr = zero.append(secsstr);
	}
	

	arrivaltime = (hrsstr.append(minsstr)).append(secsstr);

	return arrivaltime;
}

string Phasetimes::get_phase() const
{
	return phase;
}

int Phasetimes::get_mins() const
{
	return minutes;
}

int Phasetimes::get_secs() const
{
	return seconds;
}

