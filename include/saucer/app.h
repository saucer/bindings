#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

    struct saucer_application;

    SAUCER_EXPORT saucer_application *saucer_application_acquire(const char *id);
    SAUCER_EXPORT void saucer_application_free(saucer_application *);

    SAUCER_EXPORT bool saucer_application_thread_safe(saucer_application *);

    typedef void (*saucer_post_callback)();
    SAUCER_EXPORT void saucer_application_post(saucer_application *, saucer_post_callback callback);

    SAUCER_EXPORT void saucer_application_quit(saucer_application *);

    SAUCER_EXPORT void saucer_application_run(saucer_application *);
    SAUCER_EXPORT void saucer_application_run_once(saucer_application *);

#ifdef __cplusplus
}
#endif
