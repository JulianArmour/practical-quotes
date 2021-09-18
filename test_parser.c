#define _POSIX_C_SOURCE 200809L

#include "unity.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
// Unit Under Test: parser.c
#include "parser.h"

#define FAIL_ERRNO(msg)                                                        \
    do {                                                                       \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

char *TOC_buffer;
char *book_1_prologue;

/**
 * @brief Reads the contents of a file into a null-terminated string. The caller
 * is responsible for calling free() when done with the string.
 *
 * @param file_path Path to the file to read.
 * @return The string that holds the content of the file.
 */
static char *read_file_into_buffer(const char *file_path) {
    // set up table of contents test
    FILE *file = fopen(file_path, "rb");
    if (!file) {
        FAIL_ERRNO("Couldn't open TOC_file");
    }
    // get file size
    struct stat sb;
    int file_fd = fileno(file);
    if (file_fd == -1) {
        FAIL_ERRNO("Couldn't get the file descriptor");
    }
    if (fstat(file_fd, &sb) == -1) {
        FAIL_ERRNO("Couldn't get file stats");
    }
    long TOC_file_size = sb.st_size;
    // allocate buffer for the file
    char *buffer = malloc(TOC_file_size + 1); // + 1 for the null-terminator
    if (!buffer) {
        FAIL_ERRNO("Couldn't malloc buffer for TOC_file");
    }
    // read the file into that buffer
    size_t bytes_read = fread((void *)buffer, 1, TOC_file_size, file);
    if (bytes_read != (size_t)TOC_file_size) {
        FAIL_ERRNO("Couldn't read the file into the buffer for TOC_file");
    }
    buffer[TOC_file_size + 1] = '\0';
    fclose(file);
    return buffer;
}

static void TOC_buffer_setup(void) {
    TOC_buffer = read_file_into_buffer("test_toc.html");
}

static void TOC_buffer_teardown() { free(TOC_buffer); }
chapter_info_list *chapters;

void setUp(void) { chapters = parser_parse_TOC(TOC_buffer); }

void tearDown(void) { memset(chapters, 0, sizeof(*chapters)); }

void test_TOC_HTML_LOADED(void) {
    const char *doctype = "<!DOCTYPE html>";
    TEST_ASSERT_EQUAL_INT(0, strncmp(doctype, TOC_buffer, strlen(doctype)));
}

void test_parser_parse_TOC__return_not_empty(void) {
    TEST_ASSERT_GREATER_THAN_UINT(0, chapters->length);
}

void test_parser_parse_TOC__book_1_is_first(void) {
    TEST_ASSERT_EQUAL(1, chapters->list[0].book);
}

void test_parser_parse_TOC__prologue_is_first_chapter(void) {
    TEST_ASSERT_EQUAL_STRING("Prologue", chapters->list[0].name);
}

void test_parser_parse_TOC__knife_is_second_chapter(void) {
    TEST_ASSERT_EQUAL_STRING("Chapter 1: Knife", chapters->list[1].name);
}

void test_parser_parse_TOC__epilogue_is_29th_chapter(void) {
    TEST_ASSERT_EQUAL_STRING("Epilogue", chapters->list[29].name);
}

void test_parser_parse_TOC__prologue_url(void) {
    TEST_ASSERT_EQUAL_STRING(
        "https://practicalguidetoevil.wordpress.com/2015/03/25/prologue/",
        chapters->list[0].url);
}

void test_parser_parse_TOC__30th_chapter_is_book_2(void) {
    TEST_ASSERT_EQUAL_INT(2, chapters->list[30].book);
}

void test_parser_parse_TOC__book2_chapter1_is_prologue(void) {
    TEST_ASSERT_EQUAL_STRING("Prologue", chapters->list[30].name);
}

void test_parser_parse_TOC__book2_chapter1_url(void) {
    TEST_ASSERT_EQUAL_STRING(
        "https://practicalguidetoevil.wordpress.com/2015/11/04/prologue-2/",
        chapters->list[30].url);
}

void test_parser_parse_TOC__last_chapter_is_Grieved(void) {
    TEST_ASSERT_EQUAL_STRING("Chapter 28: Grieved",
                             chapters->list[chapters->length - 1].name);
}

void test_parser_parse_TOC__last_chapter_is_book_7(void) {
    TEST_ASSERT_EQUAL_INT(7, chapters->list[chapters->length - 1].book);
}

void test_parser_parse_TOC__all_chapters_not_extra(void) {
    for (size_t i = 0; i < chapters->length; i++) {
        TEST_ASSERT_EQUAL_INT(false, chapters->list[i].is_extra);
    }
}

void test_parser_parse_TOC__Moroks_plan(void) {
    TEST_ASSERT_EQUAL_STRING("Chapter 23: Morok's Plan",
                             chapters->list[23].name);
}

int main(void) {
    TOC_buffer_setup();

    UNITY_BEGIN();

    RUN_TEST(test_TOC_HTML_LOADED);
    RUN_TEST(test_parser_parse_TOC__return_not_empty);
    RUN_TEST(test_parser_parse_TOC__book_1_is_first);
    RUN_TEST(test_parser_parse_TOC__prologue_is_first_chapter);
    RUN_TEST(test_parser_parse_TOC__all_chapters_not_extra);
    RUN_TEST(test_parser_parse_TOC__knife_is_second_chapter);
    RUN_TEST(test_parser_parse_TOC__prologue_url);
    RUN_TEST(test_parser_parse_TOC__epilogue_is_29th_chapter);
    RUN_TEST(test_parser_parse_TOC__30th_chapter_is_book_2);
    RUN_TEST(test_parser_parse_TOC__book2_chapter1_is_prologue);
    RUN_TEST(test_parser_parse_TOC__book2_chapter1_url);
    RUN_TEST(test_parser_parse_TOC__last_chapter_is_Grieved);
    RUN_TEST(test_parser_parse_TOC__last_chapter_is_book_7);
    RUN_TEST(test_parser_parse_TOC__Moroks_plan);

    TOC_buffer_teardown();
    return UNITY_END();
}