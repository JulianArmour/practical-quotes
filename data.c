#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "data.h"

/**
 * The data passed to write_callback.
 */
struct callback_userdata {
    size_t size;
    char *buffer;
};

static size_t write_callback(char *ptr, size_t size,
                             size_t nmemb, void *userdata)
{
    struct callback_userdata *data = (struct callback_userdata *)userdata;
    // extend the size of buffer to add new data
    size_t new_size = data->size + size * nmemb;
    data->buffer = realloc(data->buffer, new_size);
    if (data->buffer == NULL) {
        fprintf(
            stderr,
            "FAILURE: Couldn't extend buffer when fetching webpage data\n"
        );
        exit(EXIT_FAILURE);
    }
    // update userdata size
    size_t old_size = data->size;
    data->size = new_size;
    // copy the new data into the buffer
    memcpy(data->buffer + old_size - 1, ptr, size * nmemb);
    // make sure the buffer is null-terminated
    data->buffer[new_size - 1] = '\0';
    return size * nmemb;
}

int data_fetch_page(char **webpage_result, const char *url) 
{
    /* set up the callback's userdata.
     * We start with just the null-terminator '\0'.
     */
    struct callback_userdata userdata = {
        .size = 1,
        .buffer = calloc(1, 1)
    };

    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &userdata);
    CURLcode result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    // return result code
    if (result != CURLE_OK) return 1;
    *webpage_result = userdata.buffer;
    return 0;
}