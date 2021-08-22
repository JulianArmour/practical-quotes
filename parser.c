#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static chapter_info_list chapters;

chapter_info_list* parser_parse_TOC(char *html) {
    /* first we search for <div class="entry-content">
       which is a container for the list of chapters.*/
    char *entry_content = strstr(html, "<div class=\"entry-content\">");
    if (!entry_content) {
        fprintf(stderr, "Couldn't find entry-content div tag\n");
        return &chapters;
    }
    /* next we find the <h2> tag. we only look for "<h2" since there could
       potentially be attributes in the tag.*/
    char *h2 = strstr(entry_content, "<h2");
    if (!h2) {
        return &chapters;
    }
    /* great, we have the <h2> tag, now let's parse out the book number. */
    int book_number;
    if (sscanf(h2, "<h%*[^>]>Book %d</h2>", &book_number) != 1) {
        fprintf(stderr, "Couldn't parse book number from: \"%25s...\"\n", h2);
        return &chapters;
    }
    /* now we have to get to the start of the chapter list for this book.
       Let's start finding the <ul> tag. Again, we only look for "<ul" to
       account for tag attributes. */
    char *start_of_chapter_list = strstr(h2, "<ul");
    if (!start_of_chapter_list) {
        return &chapters;
    }
    /* now let's go to the start of the <li> tag */
    char *li = strstr(start_of_chapter_list, "<li");
    if (!li) {
        return &chapters;
    }
    /* next, the href attribute */
    char *href = strstr(li, "href");
    /* time for the fun bit, let's parse out the chapter info and set the data
       fields in the chapter_info struct. */
    chapter_info *the_chapter_info = &chapters.list[chapters.length];
    /* The parsing pattern (following a python f-string style)
       is: "href=\"{url}\">{chapter_name}<". */
    char format[60] = {0};
    snprintf(format, sizeof(format), "href=\"%%%zu[^\"]\">%%%zu[^<]<",
             sizeof(the_chapter_info->url), sizeof(the_chapter_info->name));

    int c = sscanf(href, format, the_chapter_info->url, the_chapter_info->name);
    if (c != 2) {
        fprintf(stderr, "%s\n", "Couldn't parse the chapter url and/or name");
        return &chapters;
    }
    the_chapter_info->is_extra = false;  // none of these are "extra chapters"
    the_chapter_info->book = book_number;
    chapters.length++;

    return &chapters;
}