#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stddef.h>
#include <stdbool.h>

    struct saucer_screen;
    struct saucer_application;
    struct saucer_application_options;

    enum saucer_policy
    {
        allow,
        block,
    };

    SAUCER_EXPORT void saucer_screen_free(saucer_screen *);

    SAUCER_EXPORT const char *saucer_screen_name(saucer_screen *);
    SAUCER_EXPORT void saucer_screen_size(saucer_screen *, int *w, int *h);
    SAUCER_EXPORT void saucer_screen_position(saucer_screen *, int *x, int *y);

    SAUCER_EXPORT saucer_application_options *saucer_application_options_new(const char *id);
    SAUCER_EXPORT void saucer_application_options_free(saucer_application_options *);

    SAUCER_EXPORT void saucer_application_options_set_argc(saucer_application_options *, int);
    SAUCER_EXPORT void saucer_application_options_set_argv(saucer_application_options *, char **);
    SAUCER_EXPORT void saucer_application_options_set_quit_on_last_window_closed(saucer_application_options *, bool);

    SAUCER_EXPORT saucer_application *saucer_application_new(saucer_application_options *, int *error);
    SAUCER_EXPORT void saucer_application_free(saucer_application *);

    SAUCER_EXPORT bool saucer_application_thread_safe(saucer_application *);
    SAUCER_EXPORT void saucer_application_screens(saucer_application *, saucer_screen **, size_t *size);

    typedef void (*saucer_post_callback)();

    SAUCER_EXPORT void saucer_application_post(saucer_application *, saucer_post_callback);

    typedef void (*saucer_run_callback)(saucer_application *, void *);
    typedef void (*saucer_finish_callback)(saucer_application *, void *);

    SAUCER_EXPORT void saucer_application_quit(saucer_application *);
    SAUCER_EXPORT int saucer_application_run(saucer_application *, saucer_run_callback, saucer_finish_callback, void *);

    // TODO: Expose natives via generic interface
    // TODO: Loop module
    // TODO: Events

#ifdef __cplusplus
}
#endif
