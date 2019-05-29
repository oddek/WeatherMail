#pragma once

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING
#include <curl/curl.h>
#include <string>
#include <iostream>

class Http_to_Txt
{
public:
	Http_to_Txt();
	~Http_to_Txt();
	void fetch_to_file(std::string _url, const char* _outfilename);

	//size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
};

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
