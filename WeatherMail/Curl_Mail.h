#pragma once

#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <iostream>

/* This is a simple example showing how to send mail using libcurl's SMTP
 * capabilities. It builds on the smtp-mail.c example to add authentication
 * and, more importantly, transport security to protect the authentication
 * details from being snooped.
 *
 * Note that this example requires libcurl 7.20.0 or above.
 */

#define FROM    "*EMAIL*"
#define TO "*EMAIL*"



class Curl_Mail
{
public:
	Curl_Mail();
	Curl_Mail(const char* _messagefile, const char* _recipient);
	~Curl_Mail();
	int code;

private:
	const char* messagefile;
	const char* recipient;
	int send();
	static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);




	





	
};



