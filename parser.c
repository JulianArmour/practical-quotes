#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


chapter_info_list parser_parse_TOC(char *html) {
    chapter_info_list chapters = {0};
    /* first we search for <div class="entry-content">
       which is a container for the list of chapters.*/
    char *entry_content = strstr(html, "<div class=\"entry-content\">");
    if (!entry_content) {
        fprintf(stderr, "Couldn't find entry-content div tag\n");
        return chapters;
    }
    /* next we find the <h2> tag. we only look for "<h2" since there could
       potentially be attributes in the tag.*/
    char *h2 = strstr(entry_content, "<h2");
    if (!h2) {
        return chapters;
    }

    int book_number;
    if (sscanf(h2, "<h2%*[^>]>Book %d</h2>", &book_number) != 1) {
        fprintf(stderr, "Couldn't parse book number from: \"%25s...\"\n", h2);
        return chapters;
    }
    chapters.list = calloc(1, sizeof(*chapters.list));
    chapters.length++;
    chapters.list[0] = (chapter_info) {.book = book_number};
    return chapters;
}