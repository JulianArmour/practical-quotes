#include <stdlib.h>
#include <curl/curl.h>
#include "data.h"

int main(void)
{
    // initialize the libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    char *webpage = NULL;
    int success = data_fetch_page(
        &webpage,
        "https://practicalguidetoevil.wordpress.com/"
        "table-of-contents/"
    );
    if (!success) {
        fprintf(stderr, "FATAL: %s\n", "Couldn't fetch the webpage");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", webpage);
    free(webpage);

    // clean up libcurl
    curl_global_cleanup();
    return 0;
}