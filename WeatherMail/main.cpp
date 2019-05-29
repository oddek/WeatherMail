#include "Http_to_Txt.h"
#include "Curl_Mail.h"
#include "Weather.h"


const char* forecast_file = "forecast.txt";
const char* output_file = "output.txt";

int main()
{
	Http_to_Txt* h = new Http_to_Txt();
	h->fetch_to_file("http://www.yr.no/sted/Norge/Buskerud/Drammen/Drammen/varsel.xml", "test.txt");
	

	
	Weather* w = new Weather();
	w->read(forecast_file);
	w->print_weather();
	w->create_output(output_file);
	Curl_Mail* cm = new Curl_Mail("output.txt", "*EMAIL*");
	
	return cm->code;
}


