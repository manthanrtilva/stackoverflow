	#include <curl/curl.h>

	#include <errno.h>
	#include <iostream>
	#include <stdio.h>

	#include <sys/stat.h>
	#include <sys/types.h>
	#include <unistd.h>

	#include <string.h>

	int upload(const std::string &filename, const std::string &url) {

	  CURL *curl;
	  CURLcode res;
	  struct stat file_info;
	  curl_off_t speed_upload, total_time;
	  FILE *fd;

	  curl_mime *form = NULL;
	  curl_mimepart *field = NULL;
	  struct curl_slist *headerlist = NULL;
	  static const char buf[] = "Expect:";

	  fd = fopen(filename.c_str(), "rb");
	  if (!fd) {
	    printf("unable to open file: %s\n", strerror(errno));
	    return 1;
	  }
	  if (fstat(fileno(fd), &file_info) != 0) {
	    printf("unable to get file stats: %s\n", strerror(errno));
	    return 2;
	  }

	  std::cout << "filename : " << filename << ":"
	            << std::endl;
	  std::cout << "url : " << url << std::endl;

	  curl = curl_easy_init();
	  if (curl) {
	    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	    form = curl_mime_init(curl);

	    /* Fill in the file upload field */
	    field = curl_mime_addpart(form);
	    curl_mime_name(field, "file");
	    curl_mime_filedata(field, filename.c_str());

	    headerlist = curl_slist_append(headerlist, buf);
	    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
	    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);

	    res = curl_easy_perform(curl);
	    if (res != CURLE_OK) {
	      printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
	    } else {
	      curl_easy_getinfo(curl, CURLINFO_SPEED_UPLOAD, &speed_upload);
	      curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total_time);
	      printf("Speed: %" CURL_FORMAT_CURL_OFF_T
	             " bytes/sec during %" CURL_FORMAT_CURL_OFF_T ".%06ld seconds\n",
	             speed_upload, (total_time / 1000000),
	             (long)(total_time % 1000000));
	    }
	  }
	  return 0;
	}

	int main(int argc, char **argv) { return upload(argv[1], argv[2]); }