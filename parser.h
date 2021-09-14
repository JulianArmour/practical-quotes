/**
 * The parser module is reponsible for extracting the relevant information
 * from webpages fetched by the data module
 */
#ifndef PRACTICAL_PARSER_H
#define PRACTICAL_PARSER_H

#include <stdbool.h>

/* A safe number, I don't expect the author to post more than these number of
   chapters. */
#define MAX_CHAPTERS 5000

typedef struct {
    int book;       // The book number that the chapter is in.
    char name[100]; // Chapter name.
    char url[200];  // URL to the chapter.
    bool is_extra;  // True if this is one of the "Extra Chapters".
} chapter_info;

/**
 * @brief A list of the webnovel's chapters.
 */
typedef struct {
    unsigned int length;             // Number of elements in the list.
    chapter_info list[MAX_CHAPTERS]; // The actual list, it's just an array.
} chapter_info_list;

/**
 * @brief Parses the Table of Contents.
 *
 * @param html The html string to parse. This is from the Table of Contents page
 *             on the webpage.
 * @return A pointer to a list of chapter metadata.
 */
chapter_info_list *parser_parse_TOC(char *html);

#endif // PRACTICAL_PARSER_H