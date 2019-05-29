#pragma once
class Location
{
public:
	Location();
	Location(double _altitude, double _longditude, double _latitude);
	~Location();
	double get_altitude();
	double get_longditude();
	double get_latitude();
	void set_altitude(double alt);
	void set_longditude(double lon);
	void set_latitude(double lat);

private:
	double altitude;
	double longditude;
	double latitude;
};

