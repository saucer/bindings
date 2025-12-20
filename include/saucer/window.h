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
        top          = 1 << 0,
        bottom       = 1 << 1,
        left         = 1 << 2,
        right        = 1 << 3,
        bottom_left  = bottom | left,
        bottom_right = bottom | right,
        top_left     = top | left,
        top_right    = top | right,
    };

    enum saucer_window_decoration : uint8_t
    {
        none,
        partial,
        full,
    };

    enum saucer_window_event
    {
        DECORATED,
        MAXIMIZE,
        MINIMIZE,
        CLOSED,
        RESIZE,
        FOCUS,
        CLOSE
    };

    typedef void (*saucer_window_event_decorated)(saucer_window *, saucer_window_decoration, void *);
    typedef void (*saucer_window_event_maximize)(saucer_window *, bool, void *);
    typedef void (*saucer_window_event_minimize)(saucer_window *, bool, void *);
    typedef void (*saucer_window_event_closed)(saucer_window *, void *);
    typedef void (*saucer_window_event_resize)(saucer_window *, int, int, void *);
    typedef void (*saucer_window_event_focus)(saucer_window *, bool, void *);
    typedef saucer_policy (*saucer_window_event_close)(saucer_window *, void *);

    SAUCER_EXPORT saucer_window *saucer_window_new(saucer_application *, int *error);
    SAUCER_EXPORT void saucer_window_free(saucer_window *);

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

#ifdef __cplusplus
}
#endif
