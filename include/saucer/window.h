#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "app.h"
#include "icon.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

    struct saucer_window;

    enum saucer_window_edge : uint8_t
    {
        SAUCER_WINDOW_EDGE_TOP          = 1 << 0,
        SAUCER_WINDOW_EDGE_BOTTOM       = 1 << 1,
        SAUCER_WINDOW_EDGE_LEFT         = 1 << 2,
        SAUCER_WINDOW_EDGE_RIGHT        = 1 << 3,
        SAUCER_WINDOW_EDGE_BOTTOM_LEFT  = SAUCER_WINDOW_EDGE_BOTTOM | SAUCER_WINDOW_EDGE_LEFT,
        SAUCER_WINDOW_EDGE_BOTTOM_RIGHT = SAUCER_WINDOW_EDGE_BOTTOM | SAUCER_WINDOW_EDGE_RIGHT,
        SAUCER_WINDOW_EDGE_TOP_LEFT     = SAUCER_WINDOW_EDGE_TOP | SAUCER_WINDOW_EDGE_LEFT,
        SAUCER_WINDOW_EDGE_TOP_RIGHT    = SAUCER_WINDOW_EDGE_TOP | SAUCER_WINDOW_EDGE_RIGHT,
    };

    enum saucer_window_decoration : uint8_t
    {
        SAUCER_WINDOW_DECORATION_NONE,
        SAUCER_WINDOW_DECORATION_PARTIAL,
        SAUCER_WINDOW_DECORATION_FULL,
    };

    enum saucer_window_event
    {
        SAUCER_WINDOW_EVENT_DECORATED,
        SAUCER_WINDOW_EVENT_MAXIMIZE,
        SAUCER_WINDOW_EVENT_MINIMIZE,
        SAUCER_WINDOW_EVENT_CLOSED,
        SAUCER_WINDOW_EVENT_RESIZE,
        SAUCER_WINDOW_EVENT_FOCUS,
        SAUCER_WINDOW_EVENT_CLOSE,
    };

    typedef void (*saucer_window_event_decorated)(saucer_window *, saucer_window_decoration, void *);
    typedef void (*saucer_window_event_maximize)(saucer_window *, bool, void *);
    typedef void (*saucer_window_event_minimize)(saucer_window *, bool, void *);
    typedef void (*saucer_window_event_closed)(saucer_window *, void *);
    typedef void (*saucer_window_event_resize)(saucer_window *, int, int, void *);
    typedef void (*saucer_window_event_focus)(saucer_window *, bool, void *);
    typedef saucer_policy (*saucer_window_event_close)(saucer_window *, void *);

    SAUCER_EXPORT void saucer_window_free(saucer_window *);
    SAUCER_EXPORT saucer_window *saucer_window_new(saucer_application *, int *error);

    SAUCER_EXPORT bool saucer_window_visible(saucer_window *);
    SAUCER_EXPORT bool saucer_window_focused(saucer_window *);

    SAUCER_EXPORT bool saucer_window_minimized(saucer_window *);
    SAUCER_EXPORT bool saucer_window_maximized(saucer_window *);
    SAUCER_EXPORT bool saucer_window_resizable(saucer_window *);

    SAUCER_EXPORT bool saucer_window_fullscreen(saucer_window *);

    SAUCER_EXPORT bool saucer_window_always_on_top(saucer_window *);
    SAUCER_EXPORT bool saucer_window_click_through(saucer_window *);

    SAUCER_EXPORT void saucer_window_title(saucer_window *, char *, size_t *);

    SAUCER_EXPORT void saucer_window_background(saucer_window *, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a);
    SAUCER_EXPORT int saucer_window_decorations(saucer_window *);

    SAUCER_EXPORT void saucer_window_size(saucer_window *, int *w, int *h);
    SAUCER_EXPORT void saucer_window_max_size(saucer_window *, int *w, int *h);
    SAUCER_EXPORT void saucer_window_min_size(saucer_window *, int *w, int *h);

    SAUCER_EXPORT void saucer_window_position(saucer_window *, int *x, int *y);
    SAUCER_EXPORT saucer_screen *saucer_window_screen(saucer_window *);

    SAUCER_EXPORT void saucer_window_hide(saucer_window *);
    SAUCER_EXPORT void saucer_window_show(saucer_window *);
    SAUCER_EXPORT void saucer_window_close(saucer_window *);

    SAUCER_EXPORT void saucer_window_focus(saucer_window *);

    SAUCER_EXPORT void saucer_window_start_drag(saucer_window *);
    SAUCER_EXPORT void saucer_window_start_resize(saucer_window *, saucer_window_edge);

    SAUCER_EXPORT void saucer_window_set_minimized(saucer_window *, bool);
    SAUCER_EXPORT void saucer_window_set_maximized(saucer_window *, bool);
    SAUCER_EXPORT void saucer_window_set_resizable(saucer_window *, bool);

    SAUCER_EXPORT void saucer_window_set_fullscreen(saucer_window *, bool);

    SAUCER_EXPORT void saucer_window_set_always_on_top(saucer_window *, bool);
    SAUCER_EXPORT void saucer_window_set_click_through(saucer_window *, bool);

    SAUCER_EXPORT void saucer_window_set_icon(saucer_window *, saucer_icon *);
    SAUCER_EXPORT void saucer_window_set_title(saucer_window *, const char *);

    SAUCER_EXPORT void saucer_window_set_background(saucer_window *, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    SAUCER_EXPORT void saucer_window_set_decorations(saucer_window *, saucer_window_decoration);

    SAUCER_EXPORT void saucer_window_set_size(saucer_window *, int w, int h);
    SAUCER_EXPORT void saucer_window_set_max_size(saucer_window *, int w, int h);
    SAUCER_EXPORT void saucer_window_set_min_size(saucer_window *, int w, int h);

    SAUCER_EXPORT void saucer_window_set_position(saucer_window *, int x, int y);

    SAUCER_EXPORT size_t saucer_window_on(saucer_window *, saucer_window_event, void *callback, bool clearable,
                                          void *userdata);

    SAUCER_EXPORT void saucer_window_once(saucer_window *, saucer_window_event, void *callback, void *userdata);

    SAUCER_EXPORT void saucer_window_off(saucer_window *, saucer_window_event, size_t);
    SAUCER_EXPORT void saucer_window_off_all(saucer_window *, saucer_window_event);

    /**
     * @note Please refer to the documentation in `application.h` on how to use this function.
     */
    SAUCER_EXPORT void saucer_window_native(saucer_window *, size_t, void *, size_t *);

#ifdef __cplusplus
}
#endif
