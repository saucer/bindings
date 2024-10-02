#include "navigation.h"
#include "navigation.hpp"

#include "memory.h"

#include <cstring>

extern "C"
{
    void saucer_navigation_free(saucer_navigation *handle)
    {
        delete handle;
    }

    char *saucer_navigation_url(saucer_navigation *handle)
    {
        auto url = handle->value().url();

        auto *rtn = static_cast<char *>(saucer_memory_alloc(url.capacity()));
        strncpy(rtn, url.data(), url.capacity());

        return rtn;
    }

    bool saucer_navigation_new_window(saucer_navigation *handle)
    {
        return handle->value().new_window();
    }

    bool saucer_navigation_redirection(saucer_navigation *handle)
    {
        return handle->value().redirection();
    }

    bool saucer_navigation_user_initiated(saucer_navigation *handle)
    {
        return handle->value().user_initiated();
    }
}
