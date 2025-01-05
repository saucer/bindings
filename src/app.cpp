#include "app.h"
#include "app.hpp"

#include "options.hpp"

extern "C"
{
    saucer_application *saucer_application_init(saucer_options *options)
    {
        return saucer_application::from(saucer::application::init(options->value()));
    }

    void saucer_application_free(saucer_application *handle)
    {
        delete handle;
    }

    saucer_application *saucer_application_active()
    {
        return saucer_application::from(saucer::application::active());
    }

    bool saucer_application_thread_safe(saucer_application *handle)
    {
        return handle->value()->thread_safe();
    }

    void saucer_application_pool_submit(saucer_application *handle, saucer_pool_callback callback)
    {
        handle->value()->pool().submit(callback).get();
    }

    void saucer_application_pool_emplace(saucer_application *handle, saucer_pool_callback callback)
    {
        handle->value()->pool().emplace(callback);
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
