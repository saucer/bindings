#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "url.h"
#include "export.h"

#include <stdbool.h>

    /**
     * @remark A navigation cannot be copied.
     */
    struct saucer_navigation;

    SAUCER_EXPORT saucer_url *saucer_navigation_url(saucer_navigation *);
    SAUCER_EXPORT bool saucer_navigation_new_window(saucer_navigation *);
    SAUCER_EXPORT bool saucer_navigation_redirection(saucer_navigation *);
    SAUCER_EXPORT bool saucer_navigation_user_initiated(saucer_navigation *);

#ifdef __cplusplus
}
#endif
