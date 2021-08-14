#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unity.h"
// Unit Under Test: parser.c
#include "parser.h"


char *TOC_buffer;

static void TOC_buffer_setup(void) {
    // set up table of contents test
    FILE *TOC_file = fopen("test_toc.html", "rb");
    if (!TOC_file) {  // failure
        perror("Couldn't open TOC_file");
        exit(EXIT_FAILURE);
    }
    // get file size
    if (fseek(TOC_file, 0, SEEK_END) == -1) {
        perror("Couldn't seek to the end TOC_file");
        exit(EXIT_FAILURE);
    }
    long TOC_file_size = ftell(TOC_file);
    if (TOC_file_size == -1) {
        perror("Couldn't get the size of TOC_file");
        exit(EXIT_FAILURE);
    }
    rewind(TOC_file);
    // create buffer for the file
    TOC_buffer = malloc(TOC_file_size + 1);  // + 1 for the null-terminator
    if (!TOC_buffer) {
        perror("Couldn't malloc buffer for TOC_file");
        exit(EXIT_FAILURE);
    }
    // read the file into that buffer
    size_t bytes_read = fread((void *)TOC_buffer, 1, TOC_file_size, TOC_file);
    if (bytes_read != (size_t)TOC_file_size) {
        perror("Couldn't read the file into the buffer for TOC_file");
        exit(EXIT_FAILURE);
    }

    TOC_buffer[TOC_file_size + 1] = '\0';
    fclose(TOC_file);
}

static void TOC_buffer_teardown() {
    free(TOC_buffer);
}

void setUp(void) { }

void tearDown(void) { }

void test_TOC_HTML_LOADED(void) {
    const char *doctype = "<!DOCTYPE html>";
    TEST_ASSERT_EQUAL_INT(0, strncmp(doctype, TOC_buffer, strlen(doctype)));
}

void test_parser_parse_TOC__return_not_empty(void) {
    chapter_info_list chapters = parser_parse_TOC(TOC_buffer);
    TEST_ASSERT_GREATER_THAN_UINT(0, chapters.length);
}

void test_parser_parse_TOC__book_1_is_first(void) {
    chapter_info_list chapters = parser_parse_TOC(TOC_buffer);
    TEST_ASSERT_EQUAL(1, chapters.list[0].book);
    free(chapters.list);
}

int main(void) {
    TOC_buffer_setup();

    UNITY_BEGIN();

    RUN_TEST(test_TOC_HTML_LOADED);
    RUN_TEST(test_parser_parse_TOC__return_not_empty);
    RUN_TEST(test_parser_parse_TOC__book_1_is_first);

    TOC_buffer_teardown();
    return UNITY_END();
}