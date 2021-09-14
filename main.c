#include "data.h"
#include "parser.h"
#include <curl/curl.h>
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

    for (size_t i = 0; i < chapter_data->length; i++) {
        chapter_info *chapter = &chapter_data->list[i];
        printf("{book=%d, name=%s, url=%s, is_extra=%s}\n", chapter->book,
               chapter->name, chapter->url,
               chapter->is_extra ? "true" : "false");
    }

    // clean up libcurl
    curl_global_cleanup();
    return 0;
}