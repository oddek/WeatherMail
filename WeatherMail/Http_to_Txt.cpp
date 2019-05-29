#include "Http_to_Txt.h"

Http_to_Txt::Http_to_Txt()
{
}

Http_to_Txt::~Http_to_Txt()
{
}

void Http_to_Txt::fetch_to_file(std::string url, const char* outfilename)
{
	CURL *curl;
	FILE *fp;
	CURLcode res;
	//string url = "https://data.ssb.no/api/v0/dataset/567324.csv?lang=no";
	//std::string url = "https://www.yr.no/sted/Norge/Buskerud/Drammen/Drammen/forecast.xml";
	//const char* outfilename = "./forecast_drammen.txt";
	curl = curl_easy_init();
	if (curl) {
		fp = fopen(outfilename, "wb");
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		fclose(fp);
	}
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
	size_t written;
	written = fwrite(ptr, size, nmemb, stream);
	return written;
}