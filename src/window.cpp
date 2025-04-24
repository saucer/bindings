#include "window.h"

#include "icon.hpp"
#include "webview.hpp"

#include "utils/wrap.hpp"
#include "utils/string.hpp"

#include <utility>

#include <saucer/window.hpp>

extern "C"
{
    bool saucer_window_visible(saucer_handle *handle)
    {
        return handle->visible();
    }

    bool saucer_window_focused(saucer_handle *handle)
    {
        return handle->focused();
    }

    bool saucer_window_minimized(saucer_handle *handle)
    {
        return handle->minimized();
    }

    bool saucer_window_maximized(saucer_handle *handle)
    {
        return handle->maximized();
    }

    bool saucer_window_resizable(saucer_handle *handle)
    {
        return handle->resizable();
    }

    bool saucer_window_decorations(saucer_handle *handle)
    {
        return handle->decorations();
    }

    bool saucer_window_always_on_top(saucer_handle *handle)
    {
        return handle->always_on_top();
    }

    bool saucer_window_click_through(saucer_handle *handle)
    {
        return handle->click_through();
    }

    char *saucer_window_title(saucer_handle *handle)
    {
        return bindings::alloc(handle->title());
    }

    void saucer_window_size(saucer_handle *handle, int *width, int *height)
    {
        std::tie(*width, *height) = handle->size();
    }

    void saucer_window_max_size(saucer_handle *handle, int *width, int *height)
    {
        std::tie(*width, *height) = handle->max_size();
    }

    void saucer_window_min_size(saucer_handle *handle, int *width, int *height)
    {
        std::tie(*width, *height) = handle->min_size();
    }

    void saucer_window_hide(saucer_handle *handle)
    {
        handle->hide();
    }

    void saucer_window_show(saucer_handle *handle)
    {
        handle->show();
    }

    void saucer_window_close(saucer_handle *handle)
    {
        handle->close();
    }

    void saucer_window_focus(saucer_handle *handle)
    {
        handle->focus();
    }

    void saucer_window_start_drag(saucer_handle *handle)
    {
        handle->start_drag();
    }

    void saucer_window_start_resize(saucer_handle *handle, SAUCER_WINDOW_EDGE edge)
    {
        handle->start_resize(static_cast<saucer::window_edge>(edge));
    }

    void saucer_window_set_minimized(saucer_handle *handle, bool enabled)
    {
        handle->set_minimized(enabled);
    }

    void saucer_window_set_maximized(saucer_handle *handle, bool enabled)
    {
        handle->set_maximized(enabled);
    }

    void saucer_window_set_resizable(saucer_handle *handle, bool enabled)
    {
        handle->set_resizable(enabled);
    }

    void saucer_window_set_decorations(saucer_handle *handle, bool enabled)
    {
        handle->set_decorations(enabled);
    }

    void saucer_window_set_always_on_top(saucer_handle *handle, bool enabled)
    {
        handle->set_always_on_top(enabled);
    }

    void saucer_window_set_click_through(saucer_handle *handle, bool enabled)
    {
        handle->set_click_through(enabled);
    }

    void saucer_window_set_icon(saucer_handle *handle, saucer_icon *icon)
    {
        handle->set_icon(icon->value());
    }

    void saucer_window_set_title(saucer_handle *handle, const char *title)
    {
        handle->set_title(title);
    }

    void saucer_window_set_size(saucer_handle *handle, int width, int height)
    {
        handle->set_size(width, height);
    }

    void saucer_window_set_max_size(saucer_handle *handle, int width, int height)
    {
        handle->set_max_size(width, height);
    }

    void saucer_window_set_min_size(saucer_handle *handle, int width, int height)
    {
        handle->set_min_size(width, height);
    }

    void saucer_window_clear(saucer_handle *handle, SAUCER_WINDOW_EVENT event)
    {
        handle->clear(static_cast<saucer::window_event>(event));
    }

    void saucer_window_remove(saucer_handle *handle, SAUCER_WINDOW_EVENT event, uint64_t id)
    {
        handle->remove(static_cast<saucer::window_event>(event), id);
    }

    void saucer_window_once(saucer_handle *handle, SAUCER_WINDOW_EVENT event, void *callback)
    {
        using saucer::window_event;
        using events = saucer::window::events;

        switch (event)
        {
        case SAUCER_WINDOW_EVENT_DECORATED:
            return handle->once<window_event::decorated>(
                bindings::callback<events::type<window_event::decorated>>(handle, callback));
        case SAUCER_WINDOW_EVENT_CLOSE:
            return handle->once<window_event::close>(
                bindings::callback<events::type<window_event::close>>(handle, callback));
        case SAUCER_WINDOW_EVENT_CLOSED:
            return handle->once<window_event::closed>(
                bindings::callback<events::type<window_event::closed>>(handle, callback));
        case SAUCER_WINDOW_EVENT_FOCUS:
            return handle->once<window_event::focus>(
                bindings::callback<events::type<window_event::focus>>(handle, callback));
        case SAUCER_WINDOW_EVENT_MINIMIZE:
            return handle->once<window_event::minimize>(
                bindings::callback<events::type<window_event::minimize>>(handle, callback));
        case SAUCER_WINDOW_EVENT_MAXIMIZE:
            return handle->once<window_event::maximize>(
                bindings::callback<events::type<window_event::maximize>>(handle, callback));
        case SAUCER_WINDOW_EVENT_RESIZE:
            return handle->once<window_event::resize>(
                bindings::callback<events::type<window_event::resize>>(handle, callback));
        }

        std::unreachable();
    }

    uint64_t saucer_window_on(saucer_handle *handle, SAUCER_WINDOW_EVENT event, void *callback)
    {
        using saucer::window_event;
        using events = saucer::window::events;

        switch (event)
        {
        case SAUCER_WINDOW_EVENT_DECORATED:
            return handle->on<window_event::decorated>(
                bindings::callback<events::type<window_event::decorated>>(handle, callback));
        case SAUCER_WINDOW_EVENT_CLOSE:
            return handle->on<window_event::close>(
                bindings::callback<events::type<window_event::close>>(handle, callback));
        case SAUCER_WINDOW_EVENT_CLOSED:
            return handle->on<window_event::closed>(
                bindings::callback<events::type<window_event::closed>>(handle, callback));
        case SAUCER_WINDOW_EVENT_FOCUS:
            return handle->on<window_event::focus>(
                bindings::callback<events::type<window_event::focus>>(handle, callback));
        case SAUCER_WINDOW_EVENT_MINIMIZE:
            return handle->on<window_event::minimize>(
                bindings::callback<events::type<window_event::minimize>>(handle, callback));
        case SAUCER_WINDOW_EVENT_MAXIMIZE:
            return handle->on<window_event::maximize>(
                bindings::callback<events::type<window_event::maximize>>(handle, callback));
        case SAUCER_WINDOW_EVENT_RESIZE:
            return handle->on<window_event::resize>(
                bindings::callback<events::type<window_event::resize>>(handle, callback));
        }

        std::unreachable();
    }
}
