#pragma once
#include <string>
#include "Timestamp.h"
class Forecast
{
public:
	Forecast();
	Forecast(Timestamp _to, Timestamp _from,
	std::string _symbol, double _precipitation, std::string _wind_direction, double _wind_speed, double _temperature);
	~Forecast();
	void set_to(Timestamp t);
	void set_from(Timestamp t);
	void set_symbol(std::string s);
	void set_precipitation(double p);
	void set_wind_direction(std::string w);
	void set_wind_speed(double w);
	void set_wind_name(std::string w);
	void set_temperature(double t);

	Timestamp get_to();
	Timestamp get_from();
	std::string get_symbol();
	double get_precipitation();
	std::string get_wind_direction();
	double get_wind_speed();
	std::string get_wind_name();
	double get_temperature();
private:
	Timestamp to;
	Timestamp from;
	std::string symbol;
	double precipitation;
	std::string wind_direction;
	double wind_speed;
	std::string wind_name;
	double temperature;
};

