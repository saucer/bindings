#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "icon.h"
#include "window.h"

#include "url.h"
#include "scheme.h"

#include "permission.h"
#include "navigation.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

    struct saucer_webview;
    struct saucer_webview_options;

    enum saucer_state
    {
        SAUCER_STATE_STARTED,
        SAUCER_STATE_FINISHED,
    };

    enum saucer_status
    {
        SAUCER_STATE_HANDLED,
        SAUCER_STATE_UNHANDLED,
    };

    enum saucer_script_time
    {
        SAUCER_SCRIPT_TIME_CREATION,
        SAUCER_SCRIPT_TIME_READY,
    };

    enum saucer_webview_event
    {
        SAUCER_WEBVIEW_EVENT_PERMISSION,
        SAUCER_WEBVIEW_EVENT_FULLSCREEN,
        SAUCER_WEBVIEW_EVENT_DOM_READY,
        SAUCER_WEBVIEW_EVENT_NAVIGATED,
        SAUCER_WEBVIEW_EVENT_NAVIGATE,
        SAUCER_WEBVIEW_EVENT_MESSAGE,
        SAUCER_WEBVIEW_EVENT_REQUEST,
        SAUCER_WEBVIEW_EVENT_FAVICON,
        SAUCER_WEBVIEW_EVENT_TITLE,
        SAUCER_WEBVIEW_EVENT_LOAD,
    };

    /**
     * @remark The passed permission requests lifetime ends when the event-callback finishes. To keep it around, it has
     * to be explictly copied!
     */
    typedef saucer_status (*saucer_webview_event_permission)(saucer_webview *, saucer_permission_request *, void *);
    typedef saucer_policy (*saucer_webview_event_fullscreen)(saucer_webview *, bool, void *);
    typedef void (*saucer_webview_event_dom_ready)(saucer_webview *, void *);
    /**
     * @remark The passed urls lifetime ends when the event-callback finishes. To keep it around, it has
     * to be explictly copied!
     */
    typedef void (*saucer_webview_event_navigated)(saucer_webview *, saucer_url *, void *);
    /**
     * @remark The passed navigations lifetime ends when the event-callback finishes. It cannot be copied.
     */
    typedef saucer_policy (*saucer_webview_event_navigate)(saucer_webview *, saucer_navigation *, void *);
    typedef saucer_status (*saucer_webview_event_message)(saucer_webview *, const char *, size_t, void *);
    /**
     * @remark The passed urls lifetime ends when the event-callback finishes. To keep it around, it has
     * to be explictly copied!
     */
    typedef void (*saucer_webview_event_request)(saucer_webview *, saucer_url *, void *);
    /**
     * @remark The passed icons lifetime ends when the event-callback finishes. To keep it around, it has
     * to be explictly copied!
     */
    typedef void (*saucer_webview_event_favicon)(saucer_webview *, saucer_icon *, void *);
    typedef void (*saucer_webview_event_title)(saucer_webview *, const char *, size_t, void *);
    typedef void (*saucer_webview_event_load)(saucer_webview *, saucer_state, void *);

    SAUCER_EXPORT void saucer_webview_options_free(saucer_webview_options *);
    SAUCER_EXPORT saucer_webview_options *saucer_webview_options_new(saucer_window *);

    SAUCER_EXPORT void saucer_webview_options_set_attributes(saucer_webview_options *, bool);
    SAUCER_EXPORT void saucer_webview_options_set_persistent_cookies(saucer_webview_options *, bool);
    SAUCER_EXPORT void saucer_webview_options_set_hardware_acceleration(saucer_webview_options *, bool);

    SAUCER_EXPORT void saucer_webview_options_set_storage_path(saucer_webview_options *, const char *);
    SAUCER_EXPORT void saucer_webview_options_set_user_agent(saucer_webview_options *, const char *);
    SAUCER_EXPORT void saucer_webview_options_append_browser_flag(saucer_webview_options *, const char *);

    SAUCER_EXPORT void saucer_webview_free(saucer_webview *);
    SAUCER_EXPORT saucer_webview *saucer_webview_new(saucer_webview_options *, int *error);

    SAUCER_EXPORT saucer_url *saucer_webview_url(saucer_webview *, int *error);

    SAUCER_EXPORT saucer_icon *saucer_webview_favicon(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_page_title(saucer_webview *, char *, size_t *);

    SAUCER_EXPORT bool saucer_webview_dev_tools(saucer_webview *);
    SAUCER_EXPORT bool saucer_webview_context_menu(saucer_webview *);

    SAUCER_EXPORT bool saucer_webview_force_dark(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_background(saucer_webview *, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a);

    SAUCER_EXPORT void saucer_webview_bounds(saucer_webview *, int *x, int *y, int *w, int *h);

    SAUCER_EXPORT void saucer_webview_set_url(saucer_webview *, saucer_url *);
    SAUCER_EXPORT void saucer_webview_set_url_str(saucer_webview *, const char *);

    SAUCER_EXPORT void saucer_webview_set_html(saucer_webview *, const char *);

    SAUCER_EXPORT void saucer_webview_set_dev_tools(saucer_webview *, bool);
    SAUCER_EXPORT void saucer_webview_set_context_menu(saucer_webview *, bool);

    SAUCER_EXPORT void saucer_webview_set_force_dark(saucer_webview *, bool);
    SAUCER_EXPORT void saucer_webview_set_background(saucer_webview *, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    SAUCER_EXPORT void saucer_webview_reset_bounds(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_set_bounds(saucer_webview *, int x, int y, int w, int h);

    SAUCER_EXPORT void saucer_webview_back(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_forward(saucer_webview *);

    SAUCER_EXPORT void saucer_webview_reload(saucer_webview *);

    SAUCER_EXPORT void saucer_webview_serve(saucer_webview *, const char *);
    SAUCER_EXPORT void saucer_webview_embed(saucer_webview *, const char *path, saucer_stash *content,
                                            const char *mime);

    SAUCER_EXPORT void saucer_webview_unembed_all(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_unembed(saucer_webview *, const char *);

    SAUCER_EXPORT void saucer_webview_execute(saucer_webview *, const char *);
    SAUCER_EXPORT size_t saucer_webview_inject(saucer_webview *, const char *code, saucer_script_time run_at,
                                               bool no_frames, bool clearable);

    SAUCER_EXPORT void saucer_webview_uninject_all(saucer_webview *);
    SAUCER_EXPORT void saucer_webview_uninject(saucer_webview *, size_t);

    SAUCER_EXPORT void saucer_webview_handle_scheme(saucer_webview *, const char *, saucer_scheme_handler);
    SAUCER_EXPORT void saucer_webview_remove_scheme(saucer_webview *, const char *);

    SAUCER_EXPORT size_t saucer_webview_on(saucer_webview *, saucer_webview_event, void *callback, bool clearable,
                                           void *userdata);

    SAUCER_EXPORT void saucer_webview_once(saucer_webview *, saucer_webview_event, void *callback, void *userdata);

    SAUCER_EXPORT void saucer_webview_off(saucer_webview *, saucer_webview_event, size_t);
    SAUCER_EXPORT void saucer_webview_off_all(saucer_webview *, saucer_webview_event);

    SAUCER_EXPORT void saucer_webview_register_scheme(const char *);

    /**
     * @note Please refer to the documentation in `application.h` on how to use this function.
     */
    SAUCER_EXPORT void saucer_webview_native(saucer_webview *, size_t, void *, size_t *);

#ifdef __cplusplus
}
#endif
