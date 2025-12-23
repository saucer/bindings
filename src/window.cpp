#include "window.impl.hpp"

#include "app.impl.hpp"
#include "icon.impl.hpp"

#include "utils/map.hpp"
#include "utils/range.hpp"
#include "utils/convert.hpp"

template <>
struct saucer::bindings::converter<saucer::window::decoration>
{
    static auto convert(saucer::window::decoration decoration)
    {
        return static_cast<saucer_window_decoration>(decoration);
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
    void saucer_window_free(saucer_window *window)
    {
        delete window;
    }

    saucer_window *saucer_window_new(saucer_application *app, int *error)
    {
        auto rtn = saucer::window::create(app->ptr());

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_window::from(std::move(*rtn));
    }

    bool saucer_window_visible(saucer_window *window)
    {
        return (**window)->visible();
    }

    bool saucer_window_focused(saucer_window *window)
    {
        return (**window)->focused();
    }

    bool saucer_window_minimized(saucer_window *window)
    {
        return (**window)->minimized();
    }

    bool saucer_window_maximized(saucer_window *window)
    {
        return (**window)->maximized();
    }

    bool saucer_window_resizable(saucer_window *window)
    {
        return (**window)->resizable();
    }

    bool saucer_window_fullscreen(saucer_window *window)
    {
        return (**window)->fullscreen();
    }

    bool saucer_window_always_on_top(saucer_window *window)
    {
        return (**window)->always_on_top();
    }

    bool saucer_window_click_through(saucer_window *window)
    {
        return (**window)->click_through();
    }

    void saucer_window_title(saucer_window *window, char *title, size_t *size)
    {
        saucer::bindings::return_range((**window)->title(), title, size);
    }

    void saucer_window_background(saucer_window *window, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a)
    {
        auto background = (**window)->background();
        *r              = background.r;
        *g              = background.g;
        *b              = background.b;
        *a              = background.a;
    }

    int saucer_window_decorations(saucer_window *window)
    {
        return std::to_underlying((**window)->decorations());
    }

    void saucer_window_size(saucer_window *window, int *w, int *h)
    {
        auto size = (**window)->size();
        *w        = size.w;
        *h        = size.h;
    }

    void saucer_window_max_size(saucer_window *window, int *w, int *h)
    {
        auto size = (**window)->max_size();
        *w        = size.w;
        *h        = size.h;
    }

    void saucer_window_min_size(saucer_window *window, int *w, int *h)
    {
        auto size = (**window)->min_size();
        *w        = size.w;
        *h        = size.h;
    }

    void saucer_window_position(saucer_window *window, int *x, int *y)
    {
        auto pos = (**window)->position();
        *x       = pos.x;
        *y       = pos.y;
    }

    saucer_screen *saucer_window_screen(saucer_window *window)
    {
        auto rtn = (**window)->screen();

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_screen::from(std::move(*rtn));
    }

    void saucer_window_hide(saucer_window *window)
    {
        (**window)->hide();
    }

    void saucer_window_show(saucer_window *window)
    {
        (**window)->show();
    }

    void saucer_window_close(saucer_window *window)
    {
        (**window)->close();
    }

    void saucer_window_focus(saucer_window *window)
    {
        (**window)->focus();
    }

    void saucer_window_start_drag(saucer_window *window)
    {
        (**window)->start_drag();
    }

    void saucer_window_start_resize(saucer_window *window, saucer_window_edge edge)
    {
        (**window)->start_resize(static_cast<saucer::window::edge>(edge));
    }

    void saucer_window_set_minimized(saucer_window *window, bool value)
    {
        (**window)->set_minimized(value);
    }

    void saucer_window_set_maximized(saucer_window *window, bool value)
    {
        (**window)->set_maximized(value);
    }

    void saucer_window_set_resizable(saucer_window *window, bool value)
    {
        (**window)->set_resizable(value);
    }

    void saucer_window_set_fullscreen(saucer_window *window, bool value)
    {
        (**window)->set_fullscreen(value);
    }

    void saucer_window_set_always_on_top(saucer_window *window, bool value)
    {
        (**window)->set_always_on_top(value);
    }

    void saucer_window_set_click_through(saucer_window *window, bool value)
    {
        (**window)->set_click_through(value);
    }

    void saucer_window_set_icon(saucer_window *window, saucer_icon *icon)
    {
        (**window)->set_icon(**icon);
    }

    void saucer_window_set_title(saucer_window *window, const char *title)
    {
        (**window)->set_title(title);
    }

    void saucer_window_set_background(saucer_window *window, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        (**window)->set_background({.r = r, .g = g, .b = b, .a = a});
    }

    void saucer_window_set_decorations(saucer_window *window, saucer_window_decoration decoration)
    {
        (**window)->set_decorations(static_cast<saucer::window::decoration>(decoration));
    }

    void saucer_window_set_size(saucer_window *window, int w, int h)
    {
        (**window)->set_size({.w = w, .h = h});
    }

    void saucer_window_set_max_size(saucer_window *window, int w, int h)
    {
        (**window)->set_max_size({.w = w, .h = h});
    }

    void saucer_window_set_min_size(saucer_window *window, int w, int h)
    {
        (**window)->set_min_size({.w = w, .h = h});
    }

    void saucer_window_set_position(saucer_window *window, int x, int y)
    {
        (**window)->set_position({.x = x, .y = y});
    }

    using saucer::bindings::map_enum;
    using saucer::bindings::map_events;

    using events = map_events<map_enum<SAUCER_WINDOW_EVENT_DECORATED, saucer_window_event_decorated>, //
                              map_enum<SAUCER_WINDOW_EVENT_MAXIMIZE, saucer_window_event_maximize>,   //
                              map_enum<SAUCER_WINDOW_EVENT_MINIMIZE, saucer_window_event_minimize>,   //
                              map_enum<SAUCER_WINDOW_EVENT_CLOSED, saucer_window_event_closed>,       //
                              map_enum<SAUCER_WINDOW_EVENT_RESIZE, saucer_window_event_resize>,       //
                              map_enum<SAUCER_WINDOW_EVENT_FOCUS, saucer_window_event_focus>,         //
                              map_enum<SAUCER_WINDOW_EVENT_CLOSE, saucer_window_event_close>          //
                              >;

    size_t saucer_window_on(saucer_window *window, saucer_window_event event, void *callback, bool clearable,
                            void *userdata)
    {
        auto fn = [window, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(window, std::forward<Ts>(args)..., userdata);
        };

        return events::on(fn, ***window, event, clearable);
    }

    void saucer_window_once(saucer_window *window, saucer_window_event event, void *callback, void *userdata)
    {
        auto fn = [window, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(window, std::forward<Ts>(args)..., userdata);
        };

        events::once(fn, ***window, event);
    }

    void saucer_window_off(saucer_window *window, saucer_window_event event, size_t id)
    {
        return (**window)->off(static_cast<saucer::window::event>(event), id);
    }

    void saucer_window_off_all(saucer_window *window, saucer_window_event event)
    {
        return (**window)->off(static_cast<saucer::window::event>(event));
    }
}
