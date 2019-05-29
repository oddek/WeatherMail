#include "Location.h"



Location::Location()
{
}


Location::Location(double _altitude, double _longditude, double _latitude):
	altitude(_altitude), longditude(_longditude), latitude(_latitude)
{
}

Location::~Location()
{
}

double Location::get_altitude()
{
	return altitude;
}

double Location::get_longditude()
{
	return longditude;
}

double Location::get_latitude()
{
	return latitude;
}

void Location::set_altitude(double alt)
{
	altitude = alt;
}

void Location::set_longditude(double lon)
{
	longditude = lon;
}

void Location::set_latitude(double lat)
{
	latitude = lat;
}
