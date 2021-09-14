#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static chapter_info_list chapters;

/**
 * @brief Mutates string so that the HTML code is replaced with an ASCII
 *        character.
 *
 * @param string String to mutate.
 * @param code HTML code to replace.
 * @param character Character to replace the HTML code with.
 * @return A pointer to the placed character in the string if the code is found
 *         else NULL.
 */
char *replace_html_code(char *string, int code, char character) {
    char full_code[20] = {0};
    snprintf(full_code, sizeof(full_code), "&#%u;", code);
    char *location = strstr(string, full_code);
    if (!location) {
        return NULL;
    }
    *location = character;
    int full_code_length = strlen(full_code);
    int move_start_idx = location - string + full_code_length;
    int bytes_to_move = strlen(string) - move_start_idx + 1;
    memmove(location + 1, location + full_code_length, bytes_to_move);
    return location;
}

static char *parse_chapter_list(int book_number,
                                char *const start_of_chapter_list,
                                char *const end_of_chapter_list,
                                char *const li_parsing_format) {
    char *start_of_line_parse = start_of_chapter_list;
    while (true) {
        /* let's go to the start of the <li> tag */
        char *li = strstr(start_of_line_parse, "<li>");
        /* Two loop exit conditions:
            There are no chapters left to parse in the table of contents or
            there are no chapters left to parse in this book. Either case
            means we are done parsing so we just return.
        */
        if (!li || li > end_of_chapter_list) {
            return start_of_line_parse;
        }
        /* next, the href attribute */
        char *href = strstr(li, "href");
        /* time for the fun bit, let's parse out the chapter info and set the
           data fields in the chapter_info struct. */
        chapter_info *the_chapter_info = &chapters.list[chapters.length];
        int n_chars_read;
        int c = sscanf(href, li_parsing_format, the_chapter_info->url,
                       the_chapter_info->name, &n_chars_read);
        if (c != 2) {
            fprintf(stderr,
                    "Couldn't properly parse the chapter url and/or name "
                    "in the Table of Contents:\n"
                    "%200s\n",
                    li);
            return start_of_line_parse;
        }
        // replace the &#8217; html codes with '.
        for (char *loc = the_chapter_info->name; loc != NULL;) {
            loc = replace_html_code(the_chapter_info->name, 8217, '\'');
        }
        // none of these are "extra chapters"
        the_chapter_info->is_extra = false;
        the_chapter_info->book = book_number;
        chapters.length++;
        /* set up the next iteration to start searching from where we just
           finished parsing. */
        start_of_line_parse = href + n_chars_read;
    }
}

chapter_info_list *parser_parse_TOC(char *html) {
    /* The parsing pattern (following a python f-string style)
        for parsing the url and chapter name from each <li> element is:
        "href=\"{url}\">{chapter_name}<". */
    char li_parsing_format[60] = {0};
    snprintf(li_parsing_format, sizeof(li_parsing_format),
             "href=\"%%%zu[^\"]\">%%%zu[^<]<%%n", sizeof(chapters.list[0].url),
             sizeof(chapters.list[0].name));
    /* first we search for <div class="entry-content">
       which is a container for the list of chapters.*/
    char *entry_content = strstr(html, "<div class=\"entry-content\">");
    if (!entry_content) {
        fprintf(stderr, "Couldn't find entry-content div tag\n");
        return &chapters;
    }
    char *start_of_book_parse = entry_content;
    while (true) {
        /* next we find the <h2> tag. we only look for "<h2" since there could
        potentially be attributes in the tag.*/
        char *h2 = strstr(start_of_book_parse, "<h2");
        if (!h2) {
            return &chapters; /* done parsing books */
        }
        /* great, we have the <h2> tag, now let's parse out the book number. */
        int book_number;
        if (sscanf(h2, "<h%*[^>]>Book %d</h2>", &book_number) != 1) {
            fprintf(stderr, "Couldn't parse book number from: \"%25s...\"\n",
                    h2);
            return &chapters;
        }
        /* now we have to get to the start of the chapter list for this book.
        Let's start finding the <ul> tag. Again, we only look for "<ul" to
        account for tag attributes. */
        char *start_of_chapter_list = strstr(h2, "<ul");
        if (!start_of_chapter_list) {
            return &chapters;
        }
        /* we also need to find the end of the list (i.e the </ul> tag), so that
        we know when to stop reading each chapter for this book. */
        char *end_of_chapter_list = strstr(start_of_chapter_list, "</ul>");

        start_of_book_parse =
            parse_chapter_list(book_number, start_of_chapter_list,
                               end_of_chapter_list, li_parsing_format);
    }
}