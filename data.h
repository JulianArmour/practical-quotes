/**
 * The data module is reponsible for fetching web pages from 
 * https://practicalguidetoevil.wordpress.com
 */
#ifndef PRACTICAL_DATA_H
#define PRACTICAL_DATA_H

/*
 * Fetches the html from the provided url and stores the result into an 
 * allocated buffer. The buffer's address is written into webpage_result.
 * The caller is reponsible for freeing this buffer.
 *
 * Example:
 *  char *webpage_result;
 *  int res_code = webpage_result(&webpage_result, "http://practicalguide...");
 *  printf("%s\n", webpage_result);
 *  free(webpage_result);
 *
 * @param webpage_result The pointer to the webpage buffer.
 * @param url The url for the webpage to fetch.
 * @return 0 on success. All other values are failures.
 */
int data_fetch_page(char **webpage_result, const char *url);

#endif