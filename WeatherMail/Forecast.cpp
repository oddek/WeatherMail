#include "Forecast.h"



Forecast::Forecast()
{
}


Forecast::Forecast(Timestamp _to, Timestamp _from,
	std::string _symbol, double _precipitation, std::string _wind_direction, double _wind_speed, double _temperature):
	to(_to), from(_from), symbol(_symbol), precipitation(_precipitation), wind_direction(_wind_direction), wind_speed(_wind_speed), temperature(_temperature)
{
}

Forecast::~Forecast()
{
}

void Forecast::set_to(Timestamp t)
{
	to = t;
}

void Forecast::set_from(Timestamp t)
{
	from = t;
}

void Forecast::set_symbol(std::string s)
{
	symbol = s;
}

void Forecast::set_precipitation(double p)
{
	precipitation = p;
}

void Forecast::set_wind_direction(std::string w)
{
	wind_direction = w;
}

void Forecast::set_wind_speed(double w)
{
	wind_speed = w;
}

void Forecast::set_wind_name(std::string w)
{
	wind_name = w;
}

void Forecast::set_temperature(double t)
{
	temperature = t;
}

Timestamp Forecast::get_to()
{
	return to;
}

Timestamp Forecast::get_from()
{
	return from;
}

std::string Forecast::get_symbol()
{
	return symbol;
}

double Forecast::get_precipitation()
{
	return precipitation;
}

std::string Forecast::get_wind_direction()
{
	return wind_direction;
}

double Forecast::get_wind_speed()
{
	return wind_speed;
}

std::string Forecast::get_wind_name()
{
	return wind_name;
}

double Forecast::get_temperature()
{
	return temperature;
}
