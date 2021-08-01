#include <stdlib.h>
#include <curl/curl.h>
#include "data.h"

int main(void)
{
    // initialize the libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    char *webpage = NULL;
    int result = data_fetch_page(
        &webpage,
        "https://practicalguidetoevil.wordpress.com/"
        "2019/04/05/chapter-30-weaver-woven/"
    );
    if (result != 0) {
        fprintf(stderr, "FATAL: %s\n", "Couldn't fetch the webpage");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", webpage);

    // clean up libcurl
    curl_global_cleanup();
    return 0;
}