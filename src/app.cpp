#include "app.impl.hpp"

#include "utils/map.hpp"
#include "utils/range.hpp"
#include "utils/convert.hpp"

#include "version.hpp"

template <>
struct saucer::bindings::converter<saucer::screen>
{
    static auto *convert(saucer::screen screen)
    {
        return saucer_screen::from(std::move(screen));
    }
};

template <>
struct saucer::bindings::converter<saucer::policy>
{
    static auto convert(const saucer_policy &value)
    {
        return static_cast<saucer::policy>(value);
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

    void saucer_application_options_free(saucer_application_options *options)
    {
        delete options;
    }

    saucer_application_options *saucer_application_options_new(const char *id)
    {
        return saucer_application_options::from({.id = id});
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

    void saucer_application_free(saucer_application *app)
    {
        delete app;
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

    bool saucer_application_thread_safe(saucer_application *app)
    {
        return (*app)->thread_safe();
    }

    void saucer_application_screens(saucer_application *app, saucer_screen **screens, size_t *size)
    {
        saucer::bindings::return_range((*app)->screens(), screens, size);
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

    void saucer_application_post(saucer_application *app, saucer_post_callback callback, void *userdata)
    {
        (*app)->post([callback, userdata] { callback(userdata); });
    }

    void saucer_application_quit(saucer_application *app)
    {
        (*app)->quit();
    }

    using saucer::bindings::map_enum;
    using saucer::bindings::map_events;

    using events = map_events<map_enum<SAUCER_APPLICATION_EVENT_QUIT, saucer_application_event_quit> //
                              >;

    size_t saucer_application_on(saucer_application *app, saucer_application_event event, void *callback,
                                 bool clearable, void *userdata)
    {
        auto fn = [app, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(app, std::forward<Ts>(args)..., userdata);
        };

        return events::on(fn, **app, event, clearable);
    }

    void saucer_application_once(saucer_application *app, saucer_application_event event, void *callback,
                                 void *userdata)
    {
        auto fn = [app, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(app, std::forward<Ts>(args)..., userdata);
        };

        events::once(fn, **app, event);
    }

    void saucer_application_off(saucer_application *app, saucer_application_event event, size_t id)
    {
        (*app)->off(static_cast<saucer::application::event>(event), id);
    }

    void saucer_application_off_all(saucer_application *app, saucer_application_event event)
    {
        (*app)->off(static_cast<saucer::application::event>(event));
    }

    const char *saucer_version()
    {
        return saucer::version;
    }
}
