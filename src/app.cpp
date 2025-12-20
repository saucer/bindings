#include "app.impl.hpp"

template <>
struct saucer::cutils::converter<saucer::screen>
{
    static auto *convert(saucer::screen screen)
    {
        return saucer_screen::from(std::move(screen));
    }
};

extern "C"
{
    void saucer_screen_free(saucer_screen *screen)
    {
        delete screen;
    }

    const char *saucer_screen_name(saucer_screen *screen)
    {
        return (*screen)->name.c_str();
    }

    void saucer_screen_size(saucer_screen *screen, int *w, int *h)
    {
        *w = (*screen)->size.w;
        *h = (*screen)->size.h;
    }

    void saucer_screen_position(saucer_screen *screen, int *x, int *y)
    {
        *x = (*screen)->position.x;
        *y = (*screen)->position.y;
    }

    saucer_application_options *saucer_application_options_new(const char *id)
    {
        return saucer_application_options::from({.id = id});
    }

    void saucer_application_options_free(saucer_application_options *options)
    {
        delete options;
    }

    void saucer_application_options_set_argc(saucer_application_options *options, int argc)
    {
        (*options)->argc = argc;
    }

    void saucer_application_options_set_argv(saucer_application_options *options, char **argv)
    {
        (*options)->argv = argv;
    }

    void saucer_application_options_set_quit_on_last_window_closed(saucer_application_options *options, bool value)
    {
        (*options)->quit_on_last_window_closed = value;
    }

    saucer_application *saucer_application_new(saucer_application_options *options, int *error)
    {
        auto rtn = saucer::application::create(**options);

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_application::from(std::move(rtn.value()));
    }

    void saucer_application_free(saucer_application *app)
    {
        delete app;
    }

    bool saucer_application_thread_safe(saucer_application *app)
    {
        return (*app)->thread_safe();
    }

    void saucer_application_screens(saucer_application *app, saucer_screen **screens, size_t *size)
    {
        saucer::cutils::return_range((*app)->screens(), screens, size);
    }

    int saucer_application_run(saucer_application *app, saucer_run_callback run, saucer_finish_callback finish,
                               void *userdata)
    {
        auto capture = std::make_tuple(app, run, finish, userdata);

        auto fn = [capture](saucer::application *app) -> coco::stray
        {
            auto [application, run, finish, userdata] = capture;
            run(application, userdata);
            co_await app->finish();
            finish(application, userdata);
        };

        return (*app)->run(fn);
    }

    void saucer_application_post(saucer_application *app, saucer_post_callback callback)
    {
        (*app)->post(callback);
    }

    void saucer_application_quit(saucer_application *app)
    {
        (*app)->quit();
    }
}
