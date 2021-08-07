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
} data_chapter_info;


int data_fetch_chapter_info(data_chapter_info *results,
                            unsigned int      *results_length);

#endif