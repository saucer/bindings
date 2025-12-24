
#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stddef.h>
#include <stdbool.h>

    struct saucer_url;

    SAUCER_EXPORT void saucer_url_free(saucer_url *);
    SAUCER_EXPORT saucer_url *saucer_url_copy(saucer_url *);

    SAUCER_EXPORT saucer_url *saucer_url_new_parse(const char *, int *error);
    SAUCER_EXPORT saucer_url *saucer_url_new_from(const char *, int *error);
    SAUCER_EXPORT saucer_url *saucer_url_new_opts(const char *scheme, const char *host, size_t *port, const char *path);

    SAUCER_EXPORT void saucer_url_string(saucer_url *, char *, size_t *);

    SAUCER_EXPORT void saucer_url_path(saucer_url *, char *, size_t *);
    SAUCER_EXPORT void saucer_url_scheme(saucer_url *, char *, size_t *);

    /**
     * @note The url might not contain a host. If this is the case, \param{size} will be set to 0.
     */
    SAUCER_EXPORT void saucer_url_host(saucer_url *, char *, size_t *);
    /**
     * @note The url might not contain a port. If this is the case, \param{port} will be left unchanged and `false` will
     * be returned.
     */
    SAUCER_EXPORT bool saucer_url_port(saucer_url *, size_t *);

    /**
     * @note The url might not contain a user. If this is the case, \param{size} will be set to 0.
     */
    SAUCER_EXPORT void saucer_url_user(saucer_url *, char *, size_t *);
    /**
     * @note The url might not contain a password. If this is the case, \param{size} will be set to 0.
     */
    SAUCER_EXPORT void saucer_url_password(saucer_url *, char *, size_t *);

    /**
     * @note Please refer to the documentation in `application.h` on how to use this function.
     */
    SAUCER_EXPORT void saucer_url_native(saucer_url *, size_t, void *, size_t *);

#ifdef __cplusplus
}
#endif
