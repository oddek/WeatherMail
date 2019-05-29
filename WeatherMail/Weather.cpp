#include "Weather.h"

Weather::Weather()
{
}


Weather::~Weather()
{
}

void Weather::create_output(const char* filename)
{
	std::ofstream ost(filename);
	ost << "From: *NAME* <*EMAIL*>\n";
	ost << "To: *NAME* <*EMAIL*>\n";
	ost << "Subject: " << forecasts[0].get_symbol() << "\n";
	ost << "Date: " << get_time_str() << "\n";


	ost << "God morgen!\n\n";
	//Morgen
	//Symbol og temp
	ost << "Akkurat nå er det " << forecasts[0].get_symbol() << " og " << forecasts[0].get_temperature() << " grader ute.\n";
	//Regn
	if (forecasts[0].get_precipitation() > 0) ost << "Ute regner det dessverre, ca " << forecasts[0].get_precipitation() << "mm, frem til " << forecasts[0].get_to().hour;
	//Vind
	ost << "Det blåser " << forecasts[0].get_wind_name() << ", ca " << forecasts[0].get_wind_speed() << "m/s.\n\n\n";

	//12-18
	//Symbol og temp
	ost << "Fra 12 til 18 blir det " << forecasts[1].get_symbol() << " og " << forecasts[1].get_temperature() << " grader.\n";
	//Regn
	if (forecasts[1].get_precipitation() > 0) ost << "Det kommer dessverre til å regne ca " << forecasts[1].get_precipitation() << "mm.\n";
	//Vind
	ost << "Det vil blåse " << forecasts[1].get_wind_name() << ", ca " << forecasts[1].get_wind_speed() << "m/s.\n\n\n";

	//18-00
	//Symbol og temp
	ost << "I kveld blir det " << forecasts[2].get_symbol() << " og " << forecasts[2].get_temperature() << " grader.\n";
	//Regn
	if (forecasts[2].get_precipitation() > 0) ost << "Det kommer dessverre til å regne ca " << forecasts[2].get_precipitation() << "mm\n";
	//Vind
	ost << "Det vil blåse " << forecasts[2].get_wind_name() << ", ca " << forecasts[2].get_wind_speed() << "m/s.\n\n\n";

	//00-06
	//Symbol og temp
	ost << "Når natten kommer blir det " << forecasts[3].get_symbol() << " og " << forecasts[3].get_temperature() << " grader.\n";
	//Regn
	if (forecasts[3].get_precipitation() > 0) ost << "Det vil regne ca" << forecasts[3].get_precipitation() << "mm\n";
	//Vind
	ost << "Det vil blåse " << forecasts[3].get_wind_name() << ", ca " << forecasts[3].get_wind_speed() << "m/s.\n\n\n";

	//Avslutning
	ost << "Ha en fin dag.";
}


void Weather::read(const char* filename)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);
	if (doc.ErrorID() == 0)
	{
		tinyxml2::XMLElement *pRoot;
		tinyxml2::XMLElement *current;
		pRoot = doc.FirstChildElement("weatherdata");

		while (pRoot)
		{
			city = pRoot->FirstChildElement("location")->FirstChildElement("name")->GetText();
			
			loc.set_altitude(pRoot->FirstChildElement("location")->FirstChildElement("location")->DoubleAttribute("altitude"));
			loc.set_latitude(pRoot->FirstChildElement("location")->FirstChildElement("location")->DoubleAttribute("latitude"));
			loc.set_longditude(pRoot ->FirstChildElement("location")->FirstChildElement("location")->DoubleAttribute("longitude"));
			sunrise = Timestamp(pRoot->FirstChildElement("sun")->Attribute("rise"));
			sunset = Timestamp(pRoot->FirstChildElement("sun")->Attribute("set"));


			current = pRoot->FirstChildElement("forecast")->FirstChildElement("tabular")->FirstChildElement("time");

			while (current)
			{
				Forecast f{};
				f.set_from(Timestamp(current->Attribute("from")));
				f.set_to(Timestamp(current->Attribute("to")));
				f.set_symbol(current->FirstChildElement("symbol")->Attribute("name"));
				f.set_precipitation(current->FirstChildElement("precipitation")->DoubleAttribute("value"));
				f.set_wind_direction(current->FirstChildElement("windDirection")->Attribute("name"));
				f.set_wind_speed(current->FirstChildElement("windSpeed")->DoubleAttribute("mps"));
				f.set_wind_name(current->FirstChildElement("windSpeed")->Attribute("name"));
				f.set_temperature(current->FirstChildElement("temperature")->DoubleAttribute("value"));

				forecasts.push_back(f);

				current = current->NextSiblingElement("time");
			}

			pRoot = pRoot->NextSiblingElement("weatherdata");
			std::cout << "iteration" << "\n";
			//pRoot = pRoot->NextSiblingElement();
		}
	}
}

void Weather::print_weather()
{
	std::cout << city << "\n";
	std::cout << loc.get_altitude() << "\n" << loc.get_latitude() << "\n" << loc.get_longditude() << "\n";
	std::cout << "Dato: " << date.stamp << "\nSunrise: " << sunrise.stamp << "\nSunset: " << sunset.stamp << std::endl;

	for (auto i : forecasts)
	{
		std::cout << "Fra: " << i.get_from().hour << ", til: " << i.get_to().hour << "\n";
		std::cout << "\nVær: " << i.get_symbol() << "\nPrecipitation: " << i.get_precipitation() << "\nWind-dir: " << i.get_wind_direction() << "\nTemp: " << i.get_temperature() << std::endl;
	}
}

std::string Weather::get_time_str()
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string s(30, '\0');
	std::strftime(&s[0], s.size(), "%d-%m-%Y %H:%M:%S", std::localtime(&now));
	return s;
}



	


	
