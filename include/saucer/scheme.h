#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "url.h"
#include "stash.h"
#include "export.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

    struct saucer_scheme_executor;
    struct saucer_scheme_request;
    struct saucer_scheme_response;

    enum saucer_scheme_error : int16_t
    {
        SAUCER_SCHEME_ERROR_NOT_FOUND = 404,
        SAUCER_SCHEME_ERROR_INVALID   = 400,
        SAUCER_SCHEME_ERROR_DENIED    = 401,
        SAUCER_SCHEME_ERROR_FAILED    = -1
    };

    SAUCER_EXPORT void saucer_scheme_response_free(saucer_scheme_response *);
    SAUCER_EXPORT saucer_scheme_response *saucer_scheme_response_new(saucer_stash *, const char *mime);

    SAUCER_EXPORT void saucer_scheme_response_append_header(saucer_scheme_response *, const char *, const char *);
    SAUCER_EXPORT void saucer_scheme_response_set_status(saucer_scheme_response *, int);

    SAUCER_EXPORT void saucer_scheme_request_free(saucer_scheme_request *);
    SAUCER_EXPORT saucer_scheme_request *saucer_scheme_request_copy(saucer_scheme_request *);

    SAUCER_EXPORT saucer_url *saucer_scheme_request_url(saucer_scheme_request *);
    SAUCER_EXPORT void saucer_scheme_request_method(saucer_scheme_request *, char *, size_t *);

    SAUCER_EXPORT saucer_stash *saucer_scheme_request_content(saucer_scheme_request *);
    /**
     * @remark Headers are returned null delimited, e.g. as "Header: Value\0Another Header: Value"
     */
    SAUCER_EXPORT void saucer_scheme_request_headers(saucer_scheme_request *, char *, size_t *);

    SAUCER_EXPORT void saucer_scheme_executor_free(saucer_scheme_executor *);
    SAUCER_EXPORT saucer_scheme_executor *saucer_scheme_executor_copy(saucer_scheme_executor *);

    SAUCER_EXPORT void saucer_scheme_executor_reject(saucer_scheme_executor *, saucer_scheme_error);
    SAUCER_EXPORT void saucer_scheme_executor_accept(saucer_scheme_executor *, saucer_scheme_response *);

    typedef void (*saucer_scheme_handler)(saucer_scheme_request *, saucer_scheme_executor *);

#ifdef __cplusplus
}
#endif
