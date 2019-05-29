#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
class Timestamp
{
public:
	Timestamp();
	Timestamp(std::string s);
	Timestamp(int _hour, int _day, int _month, int _year);
	Timestamp(int _day, int _month, int _year);
	~Timestamp();
	std::string stamp;

	int day;
	int month;
	int year;
	int hour;
	int minute;
	int second;
};

