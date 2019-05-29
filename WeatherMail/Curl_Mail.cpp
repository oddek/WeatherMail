#include "Curl_Mail.h"



static const char *payload_text[] = {
  "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
  "To: " TO "\r\n",
  "From: " FROM " (Example User)\r\n",
  "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
  "rfcpedant.example.org>\r\n",
  "Subject: SMTP SSL example message\r\n",
  "\r\n", /* empty line to divide headers from body, see RFC5322 */
  "The body of the message starts here.\r\n",
  "\r\n",
  "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
  "Check RFC5322.\r\n",
  NULL
};

struct upload_status {
	int lines_read;
};


Curl_Mail::Curl_Mail()
{
}


Curl_Mail::Curl_Mail(const char * _messagefile, const char * _recipient) :
	messagefile(_messagefile), recipient(_recipient)
{
	code = send();
}

Curl_Mail::~Curl_Mail()
{
}

int Curl_Mail::send()
{
	{
		CURL *curl;
		CURLcode res = CURLE_OK;
		struct curl_slist *recipients = NULL;
		struct upload_status upload_ctx;

		//FILE* message;
		//message = fopen("test.txt", "r");

		upload_ctx.lines_read = 0;

		FILE* message;
		message = fopen(messagefile, "r");

		curl = curl_easy_init();
		if (curl) {
			/* Set username and password */
			curl_easy_setopt(curl, CURLOPT_USERNAME, "*EMAIL*");
			curl_easy_setopt(curl, CURLOPT_PASSWORD, "*PASSWORD*");

			/* This is the URL for your mailserver. Note the use of smtps:// rather
			 * than smtp:// to request a SSL based connection. */
			curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");

			/* If you want to connect to a site who isn't using a certificate that is
			 * signed by one of the certs in the CA bundle you have, you can skip the
			 * verification of the server's certificate. This makes the connection
			 * A LOT LESS SECURE.
			 *
			 * If you have a CA cert for the server stored someplace else than in the
			 * default bundle, then the CURLOPT_CAPATH option might come handy for
			 * you. */


			curl_easy_setopt(curl, CURLOPT_CAINFO, "cacert.pem");


#ifdef SKIP_PEER_VERIFICATION
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
#endif

			/* If the site you're connecting to uses a different host name that what
			 * they have mentioned in their server certificate's commonName (or
			 * subjectAltName) fields, libcurl will refuse to connect. You can skip
			 * this check, but this will make the connection less secure. */

#ifdef SKIP_HOSTNAME_VERIFICATION
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
#endif

			/* Note that this option isn't strictly required, omitting it will result
			 * in libcurl sending the MAIL FROM command with empty sender data. All
			 * autoresponses should have an empty reverse-path, and should be directed
			 * to the address in the reverse-path which triggered them. Otherwise,
			 * they could cause an endless loop. See RFC 5321 Section 4.5.5 for more
			 * details.
			 */
			curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);
		

			/* Add two recipients, in this particular case they correspond to the
			 * To: and Cc: addressees in the header, but they could be any kind of
			 * recipient. */
			recipients = curl_slist_append(recipients, recipient);
			//recipients = curl_slist_append(recipients, CC);
			curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

			/* We're using a callback function to specify the payload (the headers and
			 * body of the message). You could just use the CURLOPT_READDATA option to
			 * specify a FILE pointer to read from. */
			//curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
			//curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
			curl_easy_setopt(curl, CURLOPT_READDATA, message);
			curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

			/* Since the traffic will be encrypted, it is very useful to turn on debug
			 * information within libcurl to see what is happening during the
			 * transfer */
			curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

			/* Send the message */
			res = curl_easy_perform(curl);

			/* Check for errors */
			if (res != CURLE_OK)
				fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

			/* Free the list of recipients */
			curl_slist_free_all(recipients);

			/* Always cleanup */
			curl_easy_cleanup(curl);
		}
		return (int)res;
	}
}



size_t Curl_Mail::payload_source(void *ptr, size_t size, size_t nmemb, void *userp)
{
	struct upload_status *upload_ctx = (struct upload_status *)userp;
	const char *data = "";

	if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
		return 0;
	}

	data = payload_text[upload_ctx->lines_read];

	if (data) {
		size_t len = strlen(data);
		memcpy(ptr, data, len);
		upload_ctx->lines_read++;

		return len;
	}

	return 0;
}


