#include "app.h"
#include "app.hpp"

extern "C"
{
    saucer_application *saucer_application_acquire(const char *id)
    {
        return saucer_application::from(saucer::application::acquire({
            .id = id,
        }));
    }

    void saucer_application_free(saucer_application *handle)
    {
        delete handle;
    }

    bool saucer_application_thread_safe(saucer_application *handle)
    {
        return handle->value()->thread_safe();
    }

    void saucer_application_post(saucer_application *handle, saucer_post_callback callback)
    {
        handle->value()->post(callback);
    }

    void saucer_application_quit(saucer_application *handle)
    {
        handle->value()->quit();
    }

    void saucer_application_run(saucer_application *handle)
    {
        handle->value()->run();
    }

    void saucer_application_run_once(saucer_application *handle)
    {
        handle->value()->run<false>();
    }
}
