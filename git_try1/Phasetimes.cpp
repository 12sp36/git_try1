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
