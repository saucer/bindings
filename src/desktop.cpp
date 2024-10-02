#include "desktop.h"
#include <saucer/desktop.hpp>

extern "C"
{
    void saucer_desktop_open(const char *uri)
    {
        saucer::desktop::open(uri);
    }
}
