#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "options.h"

    /**
     * @brief A handle to a saucer::application
     * @note The application will live as long as there are handles to it. So make sure to properly free all handles you
     * obtain to a saucer::application like through e.g. `saucer_application_active`!
     */
    struct saucer_application;

    SAUCER_EXPORT saucer_application *saucer_application_init(saucer_options *options);
    SAUCER_EXPORT void saucer_application_free(saucer_application *);

    SAUCER_EXPORT saucer_application *saucer_application_active();

    SAUCER_EXPORT bool saucer_application_thread_safe(saucer_application *);

    typedef void (*saucer_pool_callback)();

    /**
     * @brief Submits (blocking) the given @param callback to the thread-pool
     */
    SAUCER_EXPORT void saucer_application_pool_submit(saucer_application *, saucer_pool_callback callback);

    /**
     * @brief Emplaces (non blocking) the given @param callback to the thread-pool
     */
    SAUCER_EXPORT void saucer_application_pool_emplace(saucer_application *, saucer_pool_callback callback);

    typedef void (*saucer_post_callback)();
    SAUCER_EXPORT void saucer_application_post(saucer_application *, saucer_post_callback callback);

    SAUCER_EXPORT void saucer_application_quit(saucer_application *);

    SAUCER_EXPORT void saucer_application_run(saucer_application *);
    SAUCER_EXPORT void saucer_application_run_once(saucer_application *);

#ifdef __cplusplus
}
#endif
