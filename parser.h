/**
 * The parser module is reponsible for extracting the relevant information
 * from webpages fetched by the data module
 */
#ifndef PRACTICAL_PARSER_H
#define PRACTICAL_PARSER_H

#include <stdbool.h>


typedef struct {
    int   book;     // The book number that the chapter is in.
    char *name;     // Chapter name.
    char *url;      // URL to the chapter.
    bool  is_extra; // True if this is one of the "Extra Chapters".
} chapter_info;

/**
 * @brief A list of the webnovel's chapters.
 */
typedef struct {
    unsigned int length;  // Length of the list.
    chapter_info *list;   // Pointer to an array of chapter_info structs.
} chapter_info_list;

chapter_info_list parser_parse_TOC(char *html);

#endif  // PRACTICAL_PARSER_H