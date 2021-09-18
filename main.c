#include "data.h"
#include "parser.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // initialize the libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    char *webpage = NULL;
    int success =
        data_fetch_page(&webpage, "https://practicalguidetoevil.wordpress.com/"
                                  "table-of-contents/");
    if (!success) {
        fprintf(stderr, "FATAL: %s\n", "Couldn't fetch the webpage");
        exit(EXIT_FAILURE);
    }
    chapter_info_list *chapter_data = parser_parse_TOC(webpage);
    free(webpage);

    success = data_fetch_page(&webpage, chapter_data->list[0].url);
    if (!success) {
        fprintf(stderr, "FATAL: %s\n", "Couldn't fetch the chapter webpage");
        exit(EXIT_FAILURE);
    }
    printf("%s\n", webpage);
    free(webpage);

    // clean up libcurl
    curl_global_cleanup();
    return 0;
}