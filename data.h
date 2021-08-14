/**
 * The data module is reponsible for fetching web pages from 
 * https://practicalguidetoevil.wordpress.com
 */
#ifndef PRACTICAL_DATA_H
#define PRACTICAL_DATA_H

#include <stdbool.h>

/**
 * Fetches the html from the provided url and stores the result into an 
 * allocated buffer. The buffer's address is written into webpage_result.
 * The caller is reponsible for freeing this buffer.
 *
 * @param webpage_result The pointer to the webpage buffer.
 * @param url The url for the webpage to fetch.
 * @return true on success and false on failure.
 */
bool data_fetch_page(char **webpage_result, const char *url);



#endif  // PRACTICAL_DATA_H