/**
 * The data module is reponsible for fetching web pages from 
 * https://practicalguidetoevil.wordpress.com
 */
#ifndef PRACTICAL_DATA_H
#define PRACTICAL_DATA_H

/**
 * Fetches the html from the provided url and stores the result in a buffer.
 * The buffer's address is written into webpage_result.
 *
 * Example:
 *  char *webpage_result;
 *  int result = webpage_result(&webpage_result, "http://practicalguide...");
 *  printf("%s\n", webpage_result);
 *
 * @param webpage_result The pointer to the webpage buffer.
 * @param url The url for the webpage to fetch.
 * @return 0 on success. All other values are failures.
 */
int data_fetch_page(char **webpage_result, const char *url);

#endif