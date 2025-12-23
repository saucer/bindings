#include "url.impl.hpp"
#include "icon.impl.hpp"
#include "permission.impl.hpp"

#include "app.impl.hpp"
#include "window.impl.hpp"
#include "webview.impl.hpp"

#include "native.hpp"
#include "utils/extract.hpp"

extern "C"
{
    void saucer_application_native(saucer_application *app, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((*app)->native(), idx, result, size);
    }

    void saucer_window_native(saucer_window *window, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((**window)->native(), idx, result, size);
    }

    void saucer_webview_native(saucer_webview *webview, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((*webview)->native(), idx, result, size);
    }

    void saucer_icon_native(saucer_icon *icon, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((*icon)->native(), idx, result, size);
    }

    void saucer_url_native(saucer_url *url, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((*url)->native(), idx, result, size);
    }

    void saucer_permission_request_native(saucer_permission_request *request, size_t idx, void *result, size_t *size)
    {
        saucer::bindings::extract((**request)->native(), idx, result, size);
    }
}
