#include "data.h"
#include "parser.h"
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // initialize the libcurl
    curl_global_init(CURL_GLOBAL_ALL);

    char *webpage_html = NULL;
    int success = data_fetch_page(&webpage_html,
                                  "https://practicalguidetoevil.wordpress.com/"
                                  "table-of-contents/");
    if (!success) {
        fprintf(stderr, "FATAL: %s\n", "Couldn't fetch the webpage");
        exit(EXIT_FAILURE);
    }
    chapter_info_list *chapter_data = parser_parse_TOC(webpage_html);
    free(webpage_html);

    /* fetch each chapter's quotes */
    for (size_t chapter_idx = 0; chapter_idx < chapter_data->length;
         chapter_idx++) {
        success =
            data_fetch_page(&webpage_html, chapter_data->list[chapter_idx].url);
        if (!success) {
            fprintf(stderr, "FATAL: Couldn't fetch the chapter webpage\n");
            exit(EXIT_FAILURE);
        }
        chapter_quote quote;
        parse_chapter_quote(&quote, webpage_html);
        free(webpage_html);
        printf("Book %d - %s\n"
               "%s\n"
               "- %s\n\n",
               chapter_data->list[chapter_idx].book,
               chapter_data->list[chapter_idx].name, quote.quote, quote.source);
    }
    // clean up libcurl
    curl_global_cleanup();
    return 0;
}