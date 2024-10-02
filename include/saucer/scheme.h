#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "stash.h"
#include "window.h"

    enum SAUCER_SCHEME_ERROR
    {
        SAUCER_REQUEST_ERROR_NOT_FOUND,
        SAUCER_REQUEST_ERROR_INVALID,
        SAUCER_REQUEST_ERROR_ABORTED,
        SAUCER_REQUEST_ERROR_DENIED,
        SAUCER_REQUEST_ERROR_FAILED,
    };

    struct saucer_scheme_response;

    SAUCER_EXPORT saucer_scheme_response *saucer_scheme_response_new(saucer_stash *data, const char *mime);
    SAUCER_EXPORT saucer_scheme_response *saucer_scheme_response_unexpected(SAUCER_SCHEME_ERROR error);

    /**
     * @note Under normal circumstances this function should not be used. Once a saucer_response is
     * returned from within a saucer_scheme_handler it is automatically deleted.
     * You may use this function to free the response in case of an exception.
     */
    SAUCER_EXPORT void saucer_scheme_response_free(saucer_scheme_response *);

    SAUCER_EXPORT void saucer_scheme_response_set_status(saucer_scheme_response *, int status);
    SAUCER_EXPORT void saucer_scheme_response_add_header(saucer_scheme_response *, const char *header,
                                                         const char *value);

    struct saucer_scheme_request;

    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_scheme_request_url(saucer_scheme_request *);
    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_scheme_request_method(saucer_scheme_request *);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT saucer_stash *saucer_scheme_request_content(saucer_scheme_request *);

    /**
     * @note The arrays pointed to by @param headers and @param values will be populated with strings which are
     * themselves dynamically allocated. Both arrays will then hold @param count elements.
     *
     * To properly free the returned arrays you should:
     * - Free all strings within the headers and values array
     * - Free the array itself
     */
    SAUCER_EXPORT void saucer_scheme_request_headers(saucer_scheme_request *, char ***headers, char ***values,
                                                     size_t *count);

    typedef saucer_scheme_response *(*saucer_scheme_handler)(saucer_handle *, saucer_scheme_request *);

#ifdef __cplusplus
}
#endif
