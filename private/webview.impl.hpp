#pragma once

#include "webview.h"
#include "utils/opaque.hpp"

#include <saucer/webview.hpp>

struct saucer_webview : saucer::bindings::opaque<saucer_webview, saucer::webview>
{
};

struct saucer_webview_options : saucer::bindings::opaque<saucer_webview_options, saucer::webview::options>
{
};
