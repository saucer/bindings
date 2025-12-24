#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

    struct saucer_screen;
    struct saucer_application;
    struct saucer_application_options;

    enum saucer_policy : uint8_t
    {
        SAUCER_POLICY_ALLOW,
        SAUCER_POLICY_BLOCK,
    };

    enum saucer_application_event
    {
        SAUCER_APPLICATION_EVENT_QUIT,
    };

    typedef saucer_policy (*saucer_application_event_quit)(saucer_application *, void *);

    SAUCER_EXPORT void saucer_screen_free(saucer_screen *);

    SAUCER_EXPORT const char *saucer_screen_name(saucer_screen *);
    SAUCER_EXPORT void saucer_screen_size(saucer_screen *, int *w, int *h);
    SAUCER_EXPORT void saucer_screen_position(saucer_screen *, int *x, int *y);

    /**
     * @note The application options can be safely free'd after creating an application instance.
     */
    SAUCER_EXPORT void saucer_application_options_free(saucer_application_options *);
    SAUCER_EXPORT saucer_application_options *saucer_application_options_new(const char *id);

    SAUCER_EXPORT void saucer_application_options_set_argc(saucer_application_options *, int);
    SAUCER_EXPORT void saucer_application_options_set_argv(saucer_application_options *, char **);
    SAUCER_EXPORT void saucer_application_options_set_quit_on_last_window_closed(saucer_application_options *, bool);

    /**
     * @attention Please call this after \see{saucer_application_run} returned and not in the finish callback or
     * similar.
     */
    SAUCER_EXPORT void saucer_application_free(saucer_application *);
    SAUCER_EXPORT saucer_application *saucer_application_new(saucer_application_options *, int *error);

    SAUCER_EXPORT bool saucer_application_thread_safe(saucer_application *);
    SAUCER_EXPORT void saucer_application_screens(saucer_application *, saucer_screen **, size_t *size);

    typedef void (*saucer_post_callback)(void *);

    SAUCER_EXPORT void saucer_application_post(saucer_application *, saucer_post_callback, void *userdata);

    typedef void (*saucer_run_callback)(saucer_application *, void *);
    typedef void (*saucer_finish_callback)(saucer_application *, void *);

    SAUCER_EXPORT void saucer_application_quit(saucer_application *);
    /**
     * @note This approximates the run function that uses coroutines. The run callback is called once the application is
     * ready, then `co_await app->finish()` is called internally, afterwards, the finish callback is invoked.
     * @attention You might want to use the loop module instead.
     */
    SAUCER_EXPORT int saucer_application_run(saucer_application *, saucer_run_callback, saucer_finish_callback,
                                             void *userdata);

    SAUCER_EXPORT size_t saucer_application_on(saucer_application *, saucer_application_event, void *callback,
                                               bool clearable, void *userdata);

    SAUCER_EXPORT void saucer_application_once(saucer_application *, saucer_application_event, void *callback,
                                               void *userdata);

    SAUCER_EXPORT void saucer_application_off(saucer_application *, saucer_application_event, size_t);
    SAUCER_EXPORT void saucer_application_off_all(saucer_application *, saucer_application_event);

    /**
     * @brief Allows to access the stable natives of saucer::application.
     * @param idx The index of the member to return, e.g. `0` to access the `AdwApplication *` of the webkitgtk natives.
     * @param result A pointer to a buffer into which the member will be extracted.
     * @param size The size of the buffer.
     * @note To use this function, call it first with \param{result} being `nullptr`, and \param{size} pointing to a
     * variable that will receive the required buffer size. Then call it again with \param{result} pointing to a buffer
     * with sufficient size. Leave \param{size} unchanged in the second invocation.
     */
    SAUCER_EXPORT void saucer_application_native(saucer_application *, size_t idx, void *result, size_t *size);

    /**
     * @note The returned string does not need to be free'd.
     */
    SAUCER_EXPORT const char *saucer_version();

#ifdef __cplusplus
}
#endif
