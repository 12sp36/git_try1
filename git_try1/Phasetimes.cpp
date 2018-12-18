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

vector<int> Phasetimes::calc_arrivals(int eventhrs, int eventmins, int eventsecs, int travelmins, int travelsecs, int offset)
{
	int arrivalhrs = eventhrs + offset;
	int arrivalmins = eventmins + travelmins;
	int arrivalsecs = eventsecs + travelsecs;

	if (arrivalhrs < 0)
	{
		arrivalhrs = (24 + arrivalhrs);
	}
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

	vector<int> arrivals;
	arrivals.push_back(arrivalhrs);
	arrivals.push_back(arrivalmins);
	arrivals.push_back(arrivalsecs);
	return arrivals;
}

string Phasetimes::get_arrival(int eventhrs, int eventmins, int eventsecs, int travelmins, int travelsecs, int offset)
{
	vector<int> arrivals = calc_arrivals(eventhrs, eventmins, eventsecs, travelmins, travelsecs, offset);

	int arrivalhrs = arrivals[0];
	int arrivalmins = arrivals[1];
	int arrivalsecs = arrivals[2];

	string arrivaltime;
	string hrsstr;
	string minsstr;
	string secsstr;
	string zero = "0";

	//store arrival hours, mins, secs
	hrsstr = (to_string(arrivalhrs)).append(":");
	if (hrsstr.length() < 3)
	{
		hrsstr = zero.append(hrsstr);
		zero = "0";
	}
	minsstr = (to_string(arrivalmins)).append(":");
	if (minsstr.length() < 3)
	{
		minsstr = zero.append(minsstr);
		zero = "0";
	}
	secsstr = to_string(arrivalsecs);
	if (secsstr.length() < 2)
	{
		secsstr = zero.append(secsstr);
	}
	
	arrivaltime = (hrsstr.append(minsstr)).append(secsstr);

	return arrivaltime;
}

int Phasetimes::get_UTCoffset(double longstation)
{
	int offset;
	if (longstation < -172.50 && longstation > -180.00)
	{
		offset = -12;
	}
	else if (longstation < -157.50)
	{
		offset = -11;
	}
	else if (longstation < -142.50)
	{
		offset = -10;
	}
	else if (longstation < -127.5)
	{
		offset = -9;
	}
	else if (longstation < -112.50)
	{
		offset = -8;
	}
	else if (longstation < -97.50)
	{
		offset = -7;
	}
	else if (longstation < -82.50)
	{
		offset = -6;
	}
	else if (longstation < -67.50)
	{
		offset = -5;
	}
	else if (longstation < -52.50)
	{
		offset = -4;
	}
	else if (longstation < -37.50)
	{
		offset = -3;
	}
	else if (longstation < -22.50)
	{
		offset = -2;
	}
	else if (longstation < -7.50)
	{
		offset = -1;
	}
	else if (longstation < 7.50)
	{
		offset = 0;
	}
	else if (longstation < 22.50)
	{
		offset = 1;
	}
	else if (longstation < 37.50)
	{
		offset = 2;
	}
	else if (longstation < 52.50)
	{
		offset = 3;
	}
	else if (longstation < 67.50)
	{
		offset = 4;
	}
	else if (longstation < 82.50)
	{
		offset = 5;
	}
	else if (longstation < 97.50)
	{
		offset = 6;
	}
	else if (longstation < 112.50)
	{
		offset = 7;
	}
	else if (longstation < 127.50)
	{
		offset = 8;
	}
	else if (longstation < 142.50)
	{
		offset = 9;
	}
	else if (longstation < 157.50)
	{
		offset = 10;
	}
	else if (longstation < 172.50)
	{
		offset = 11;
	}
	else if (longstation < 180.00)
	{
		offset = 12;
	}
	else
	{
		offset = 999;
	}
	return offset;
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



