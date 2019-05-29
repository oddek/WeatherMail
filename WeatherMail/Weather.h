#pragma once

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING

#include <string>
#include <vector>
#include "Location.h"
#include "Forecast.h"
#include <tinyxml2.h>
#include <fstream>
#include <chrono>
#include <ctime>


class Weather
{
public:
	Weather();
	~Weather();
	//void init(const char* filename);
	void create_output(const char* filename);
	void read(const char* filename);
	void print_weather();
private:
	std::string get_time_str();
	std::string city;
	std::string country;
	Location loc;
	Timestamp date;
	Timestamp sunrise;
	Timestamp sunset;

	std::vector<Forecast> forecasts;


	
};

