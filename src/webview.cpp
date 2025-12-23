#include "webview.impl.hpp"

#include "icon.impl.hpp"
#include "stash.impl.hpp"
#include "window.impl.hpp"

#include "url.impl.hpp"
#include "scheme.impl.hpp"

#include "permission.impl.hpp"
#include "navigation.impl.hpp"

#include "utils/map.hpp"
#include "utils/wide.hpp"
#include "utils/range.hpp"
#include "utils/convert.hpp"

template <>
struct saucer::bindings::converter<saucer::policy>
{
    static auto convert(const saucer_policy &value)
    {
        return static_cast<saucer::policy>(value);
    }
};

template <>
struct saucer::bindings::converter<saucer::status>
{
    static auto convert(const saucer_status &status)
    {
        return static_cast<saucer::status>(status);
    }
};

template <>
struct saucer::bindings::converter<saucer::state>
{
    static auto convert(const saucer::state &value)
    {
        return static_cast<saucer_state>(value);
    }
};

template <>
struct saucer::bindings::converter<saucer::navigation>
{
    static auto convert(const saucer::navigation &navigation)
    {
        return saucer_navigation{std::addressof(navigation)};
    }
};

template <>
struct saucer::bindings::converter<saucer::icon>
{
    static auto convert(const saucer::icon &icon)
    {
        return saucer_icon{icon};
    }
};

template <>
struct saucer::bindings::converter<saucer::url>
{
    static auto convert(const saucer::url &url)
    {
        return saucer_url{url};
    }
};

template <>
struct saucer::bindings::converter<std::shared_ptr<saucer::permission::request>>
{
    static auto convert(const std::shared_ptr<saucer::permission::request> &request)
    {
        return saucer_permission_request{request};
    }
};

extern "C"
{
    void saucer_webview_options_free(saucer_webview_options *options)
    {
        delete options;
    }

    saucer_webview_options *saucer_webview_options_new(saucer_window *window)
    {
        return saucer_webview_options::from({.window = **window});
    }

    void saucer_webview_options_set_attributes(saucer_webview_options *opts, bool value)
    {
        (*opts)->attributes = value;
    }

    void saucer_webview_options_set_persistent_cookies(saucer_webview_options *opts, bool value)
    {
        (*opts)->persistent_cookies = value;
    }

    void saucer_webview_options_set_hardware_acceleration(saucer_webview_options *opts, bool value)
    {
        (*opts)->hardware_acceleration = value;
    }

    void saucer_webview_options_set_storage_path(saucer_webview_options *opts, const char *value)
    {
        (*opts)->storage_path = saucer::bindings::u8path(value);
    }

    void saucer_webview_options_set_user_agent(saucer_webview_options *opts, const char *value)
    {
        (*opts)->user_agent = value;
    }

    void saucer_webview_options_append_browser_flag(saucer_webview_options *opts, const char *value)
    {
        (*opts)->browser_flags.emplace(value);
    }

    void saucer_webview_free(saucer_webview *webview)
    {
        delete webview;
    }

    saucer_webview *saucer_webview_new(saucer_webview_options *opts, int *error)
    {
        auto rtn = saucer::webview::create(**opts);

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_webview::from(std::move(*rtn));
    }

    saucer_url *saucer_webview_url(saucer_webview *webview, int *error)
    {
        auto rtn = (*webview)->url();

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_url::from(std::move(*rtn));
    }

    saucer_icon *saucer_webview_favicon(saucer_webview *webview)
    {
        return saucer_icon::from((*webview)->favicon());
    }

    void saucer_webview_page_title(saucer_webview *webview, char *page_title, size_t *size)
    {
        saucer::bindings::return_range((*webview)->page_title(), page_title, size);
    }

    bool saucer_webview_dev_tools(saucer_webview *webview)
    {
        return (*webview)->dev_tools();
    }

    bool saucer_webview_context_menu(saucer_webview *webview)
    {
        return (*webview)->context_menu();
    }

    bool saucer_webview_force_dark(saucer_webview *webview)
    {
        return (*webview)->force_dark();
    }

    void saucer_webview_background(saucer_webview *webview, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a)
    {
        auto background = (*webview)->background();
        *r              = background.r;
        *g              = background.g;
        *b              = background.b;
        *a              = background.a;
    }

    void saucer_webview_bounds(saucer_webview *webview, int *x, int *y, int *w, int *h)
    {
        auto bounds = (*webview)->bounds();
        *x          = bounds.x;
        *y          = bounds.y;
        *w          = bounds.w;
        *h          = bounds.h;
    }

    void saucer_webview_set_url(saucer_webview *webview, saucer_url *url)
    {
        (*webview)->set_url(**url);
    }

    void saucer_webview_set_url_str(saucer_webview *webview, const char *url)
    {
        (*webview)->set_url(url);
    }

    void saucer_webview_set_html(saucer_webview *webview, const char *html)
    {
        (*webview)->set_html(html);
    }

    void saucer_webview_set_dev_tools(saucer_webview *webview, bool value)
    {
        (*webview)->set_dev_tools(value);
    }

    void saucer_webview_set_context_menu(saucer_webview *webview, bool value)
    {
        (*webview)->set_context_menu(value);
    }

    void saucer_webview_set_force_dark(saucer_webview *webview, bool value)
    {
        (*webview)->set_force_dark(value);
    }

    void saucer_webview_set_background(saucer_webview *webview, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        (*webview)->set_background({.r = r, .g = g, .b = b, .a = a});
    }

    void saucer_webview_reset_bounds(saucer_webview *webview)
    {
        (*webview)->reset_bounds();
    }

    void saucer_webview_set_bounds(saucer_webview *webview, int x, int y, int w, int h)
    {
        (*webview)->set_bounds({.x = x, .y = y, .w = w, .h = h});
    }

    void saucer_webview_back(saucer_webview *webview)
    {
        (*webview)->back();
    }

    void saucer_webview_forward(saucer_webview *webview)
    {
        (*webview)->forward();
    }

    void saucer_webview_reload(saucer_webview *webview)
    {
        (*webview)->reload();
    }

    void saucer_webview_serve(saucer_webview *webview, const char *path)
    {
        (*webview)->serve(saucer::bindings::u8path(path));
    }

    void saucer_webview_embed(saucer_webview *webview, const char *path, saucer_stash *content, const char *mime)
    {
        (*webview)->embed({{
            saucer::bindings::u8path(path),
            saucer::embedded_file{.content = **content, .mime = mime},
        }});
    }

    void saucer_webview_unembed_all(saucer_webview *webview)
    {
        (*webview)->unembed();
    }

    void saucer_webview_unembed(saucer_webview *webview, const char *path)
    {
        (*webview)->unembed(saucer::bindings::u8path(path));
    }

    void saucer_webview_execute(saucer_webview *webview, const char *code)
    {
        (*webview)->execute(code);
    }

    size_t saucer_webview_inject(saucer_webview *webview, const char *code, saucer_script_time run_at, bool no_frames,
                                 bool clearable)
    {
        return (*webview)->inject({
            .code      = code,
            .run_at    = static_cast<saucer::script::time>(run_at),
            .no_frames = no_frames,
            .clearable = clearable,
        });
    }

    void saucer_webview_uninject_all(saucer_webview *webview)
    {
        (*webview)->uninject();
    }

    void saucer_webview_uninject(saucer_webview *webview, size_t id)
    {
        (*webview)->uninject(id);
    }

    void saucer_webview_handle_scheme(saucer_webview *webview, const char *scheme, saucer_scheme_handler handler)
    {
        (*webview)->handle_scheme(
            scheme, [handler](saucer::scheme::request request, saucer::scheme::executor exec)
            { handler(saucer_scheme_request{std::move(request)}, saucer_scheme_executor{std::move(exec)}); });
    }

    void saucer_webview_remove_scheme(saucer_webview *webview, const char *scheme)
    {
        (*webview)->remove_scheme(scheme);
    }

    using saucer::bindings::map_enum;
    using saucer::bindings::map_events;

    using events = map_events<map_enum<SAUCER_WEBVIEW_EVENT_PERMISSION, saucer_webview_event_permission>, //
                              map_enum<SAUCER_WEBVIEW_EVENT_FULLSCREEN, saucer_webview_event_fullscreen>, //
                              map_enum<SAUCER_WEBVIEW_EVENT_DOM_READY, saucer_webview_event_dom_ready>,   //
                              map_enum<SAUCER_WEBVIEW_EVENT_NAVIGATED, saucer_webview_event_navigated>,   //
                              map_enum<SAUCER_WEBVIEW_EVENT_NAVIGATE, saucer_webview_event_navigate>,     //
                              map_enum<SAUCER_WEBVIEW_EVENT_MESSAGE, saucer_webview_event_message>,       //
                              map_enum<SAUCER_WEBVIEW_EVENT_REQUEST, saucer_webview_event_request>,       //
                              map_enum<SAUCER_WEBVIEW_EVENT_FAVICON, saucer_webview_event_favicon>,       //
                              map_enum<SAUCER_WEBVIEW_EVENT_TITLE, saucer_webview_event_title>,           //
                              map_enum<SAUCER_WEBVIEW_EVENT_LOAD, saucer_webview_event_load>              //
                              >;

    size_t saucer_webview_on(saucer_webview *webview, saucer_webview_event event, void *callback, bool clearable,
                             void *userdata)
    {
        auto fn = [webview, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(webview, std::forward<Ts>(args)..., userdata);
        };

        return events::on(fn, **webview, event, clearable);
    }

    void saucer_webview_once(saucer_webview *webview, saucer_webview_event event, void *callback, void *userdata)
    {
        auto fn = [webview, callback, userdata]<typename T, typename... Ts>(std::type_identity<T>, Ts &&...args)
        {
            return reinterpret_cast<T>(callback)(webview, std::forward<Ts>(args)..., userdata);
        };

        return events::once(fn, **webview, event);
    }

    void saucer_webview_off(saucer_webview *webview, saucer_webview_event event, size_t id)
    {
        (*webview)->off(static_cast<saucer::webview::event>(event), id);
    }

    void saucer_webview_off_all(saucer_webview *webview, saucer_webview_event event)
    {
        (*webview)->off(static_cast<saucer::webview::event>(event));
    }

    void saucer_webview_register_scheme(const char *scheme)
    {
        saucer::webview::register_scheme(scheme);
    }
}
