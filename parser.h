/*
 * The parser module is reponsible for extracting the relevant information
 * from webpages fetched by the data module
 */
#ifndef PRACTICAL_PARSER_H
#define PRACTICAL_PARSER_H

#include <stdbool.h>

/* A safe number, I don't expect the author to post more than these number of
 * chapters. */
#define MAX_CHAPTERS 5000

/* Maximum number of characters that can be in a quote.  The book 1 prologue
 * (https://practicalguidetoevil.wordpress.com/2015/03/25/prologue/) is around
 * 1000 characters so this number should be more than enough. */
#define QUOTE_MAX_SIZE 5000

/* The size of the quote author. E.g. “Two Hundred Heroic Axioms”, author
 * unknown */
#define QUOTE_SOURCE_MAX_SIZE 200
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
 * @brief Structure to hold a quote at the start of each chapter.
 */
typedef struct {
    char quote[QUOTE_MAX_SIZE];         // The actual quote.
    char source[QUOTE_SOURCE_MAX_SIZE]; // The quote author.
} chapter_quote;

/**
 * @brief Parses the Table of Contents.
 *
 * @param html The html string to parse. This is from the Table of Contents page
 *             on the webpage.
 * @return A pointer to a list of chapter metadata.
 */
chapter_info_list *parser_parse_TOC(char *html);

/**
 * @brief Parses the quote at the start of the chapter.
 *
 * @param chapter_quote_buffer Buffer to store the quote in.
 * @param html The html string to parse. This needs to be a chapter.
 */
void parse_chapter_quote(chapter_quote *chapter_quote_buffer, const char *html);

#endif // PRACTICAL_PARSER_H