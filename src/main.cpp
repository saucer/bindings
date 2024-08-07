#include "memory.h"
#include "scheme.h"
#include "webview.h"

#include <cstring>
#include <print>

void resize(saucer_handle *handle, int width, int height)
{
    auto *title = saucer_window_title(handle);
    std::println("Window '{}' is resized: {} {}", title, width, height);

    saucer_memory_free(title);
}

saucer_response *handle_scheme(saucer_handle *handle, saucer_request *request)
{
    static const char data[] = R"html(
        <!DOCTYPE html>
        <html>
            <body>
                C-BINDINGS!
            </body>
        </html>
        )html";

    static auto *stash = saucer_stash_view(reinterpret_cast<const uint8_t *>(data), sizeof(data));

    auto *url = saucer_request_url(request);
    std::println("Got request for: {}", url);
    saucer_memory_free(url);

    return saucer_response_new(stash, "text/html");
}

int main()
{
    saucer_register_scheme("test");

    auto *handle = saucer_new(nullptr);

    saucer_window_set_title(handle, "Hello!");

    saucer_webview_handle_scheme(handle, "test", handle_scheme);
    saucer_window_on(handle, SAUCER_WINDOW_EVENT_RESIZE, reinterpret_cast<void *>(resize));

    saucer_webview_serve_scheme(handle, "index.html", "test");

    saucer_window_show(handle);
    saucer_window_run(handle);

    saucer_free(handle);

    return 0;
}
