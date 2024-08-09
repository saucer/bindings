#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "window.h"
#include "scheme.h"

#include "options.h"

#include <stdbool.h>

    enum SAUCER_LOAD_TIME
    {
        SAUCER_LOAD_TIME_CREATION,
        SAUCER_LOAD_TIME_READY,
    };

    enum SAUCER_WEB_FRAME
    {
        SAUCER_WEB_FRAME_TOP,
        SAUCER_WEB_FRAME_ALL,
    };

    enum SAUCER_WEB_EVENT
    {
        SAUCER_WEB_EVENT_TITLE_CHANGED,
        SAUCER_WEB_EVENT_LOAD_FINISHED,
        SAUCER_WEB_EVENT_ICON_CHANGED,
        SAUCER_WEB_EVENT_LOAD_STARTED,
        SAUCER_WEB_EVENT_URL_CHANGED,
        SAUCER_WEB_EVENT_DOM_READY,
    };

    struct saucer_embedded_file;

    /*[[sc::requires_free]]*/ SAUCER_EXPORT saucer_embedded_file *saucer_embed(saucer_stash *content, const char *mime);
    SAUCER_EXPORT void saucer_embed_free(saucer_embedded_file *);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT saucer_handle *saucer_new(saucer_options *options);
    SAUCER_EXPORT void saucer_free(saucer_handle *);

    typedef bool (*saucer_on_message)(const char *);
    SAUCER_EXPORT void saucer_webview_on_message(saucer_handle *, saucer_on_message callback);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT saucer_icon *saucer_webview_favicon(saucer_handle *);
    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_webview_page_title(saucer_handle *);

    SAUCER_EXPORT bool saucer_webview_dev_tools(saucer_handle *);
    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_webview_url(saucer_handle *);
    SAUCER_EXPORT bool saucer_webview_context_menu(saucer_handle *);

    SAUCER_EXPORT void saucer_webview_background(saucer_handle *, uint8_t *r, uint8_t *g, uint8_t *b, uint8_t *a);
    SAUCER_EXPORT bool saucer_webview_force_dark_mode(saucer_handle *);

    SAUCER_EXPORT void saucer_webview_set_dev_tools(saucer_handle *, bool enabled);
    SAUCER_EXPORT void saucer_webview_set_context_menu(saucer_handle *, bool enabled);

    SAUCER_EXPORT void saucer_webview_set_force_dark_mode(saucer_handle *, bool enabled);
    SAUCER_EXPORT void saucer_webview_set_background(saucer_handle *, uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    SAUCER_EXPORT void saucer_webview_set_file(saucer_handle *, const char *file);
    SAUCER_EXPORT void saucer_webview_set_url(saucer_handle *, const char *url);

    SAUCER_EXPORT void saucer_webview_embed_file(saucer_handle *, const char *name, saucer_embedded_file *file);
    SAUCER_EXPORT void saucer_webview_serve(saucer_handle *, const char *file);
    SAUCER_EXPORT void saucer_webview_serve_scheme(saucer_handle *, const char *file, const char *scheme);

    SAUCER_EXPORT void saucer_webview_clear_scripts(saucer_handle *);

    SAUCER_EXPORT void saucer_webview_clear_embedded(saucer_handle *);
    SAUCER_EXPORT void saucer_webview_clear_embedded_file(saucer_handle *, const char *file);

    SAUCER_EXPORT void saucer_webview_execute(saucer_handle *, const char *code);
    SAUCER_EXPORT void saucer_webview_inject(saucer_handle *, const char *code, SAUCER_LOAD_TIME time,
                                             SAUCER_WEB_FRAME frame);

    /**
     * @note The stash returned from within the @param handler is automatically free'd
     */
    SAUCER_EXPORT void saucer_webview_handle_scheme(saucer_handle *, const char *name, saucer_scheme_handler handler);
    SAUCER_EXPORT void saucer_webview_remove_scheme(saucer_handle *, const char *name);

    SAUCER_EXPORT void saucer_webview_clear(saucer_handle *, SAUCER_WEB_EVENT event);
    SAUCER_EXPORT void saucer_webview_remove(saucer_handle *, SAUCER_WEB_EVENT event, uint64_t id);

    /**
     * @note The @param callback should be a function pointer to a function matching the event, that is:
     * <return-type>(saucer_handle *, <params>...);
     *
     * Where "<return-type>" and "<params>..." are to be
     * substituted according to the given event signature (see the respective C++ header)
     *
     * @example web_event::title_changed => void(*)(saucer_handle *, const char *)
     */

    SAUCER_EXPORT void saucer_webview_once(saucer_handle *, SAUCER_WEB_EVENT event, void *callback);
    SAUCER_EXPORT uint64_t saucer_webview_on(saucer_handle *, SAUCER_WEB_EVENT event, void *callback);

    /*[[sc::before_init]]*/ SAUCER_EXPORT void saucer_register_scheme(const char *name);

#ifdef __cplusplus
}
#endif
