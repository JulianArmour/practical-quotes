#include "parser.h"
#include <string.h>


chapter_info_list parser_parse_TOC(char *html) {
    chapter_info_list chapters = {0};
    /* first we search for <div class="entry-content">
       which is a container for the list of chapters*/
    char *entry_content = strstr(html, "<div class=\"entry-content\">");
    if (!entry_content) {
        //todo finish
    }
    return chapters;
}