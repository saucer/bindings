#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stdbool.h>

    struct saucer_navigation;

    SAUCER_EXPORT void saucer_navigation_free(saucer_navigation *);

    SAUCER_EXPORT char *saucer_navigation_url(saucer_navigation *);

    SAUCER_EXPORT bool saucer_navigation_new_window(saucer_navigation *);
    SAUCER_EXPORT bool saucer_navigation_redirection(saucer_navigation *);
    SAUCER_EXPORT bool saucer_navigation_user_initiated(saucer_navigation *);

#ifdef __cplusplus
}
#endif
