#include <curl/curl.h>

int main(void)
{
    // initialize the libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,
        "https://practicalguidetoevil.wordpress.com/2015/04/01/chapter-1-knife/");
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    // clean up libcurl
    curl_global_cleanup();
    return 0;
}