#include "Timestamp.h"



Timestamp::Timestamp()
{
}

Timestamp::Timestamp(std::string s) :
	stamp(s)
{
	std::stringstream ss;
	ss << s;
	std::string temp;
	int num;
	std::vector<int> numbers{ 0,0,0,0,0,0 };
	int index = 0;
	while (!ss.eof() && index < 4)
	{
		ss >> num;
		numbers[index] = num;
		ss.get();
		index++;
	}
	year = numbers[0];
	month = numbers[1];
	day = numbers[2];
	hour = numbers[3];
	minute = numbers[4];
	second = numbers[5];
}

Timestamp::Timestamp(int _hour, int _day, int _month, int _year):
	hour(_hour), day(_day), month(_month), year(_year)
{
}


Timestamp::Timestamp(int _day, int _month, int _year):
	day(_day), month(_month), year(_year)
{
}

Timestamp::~Timestamp()
{
}
