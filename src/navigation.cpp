#include "navigation.h"
#include "navigation.hpp"

#include "utils/string.hpp"

extern "C"
{
    void saucer_navigation_free(saucer_navigation *handle)
    {
        delete handle;
    }

    char *saucer_navigation_url(saucer_navigation *handle)
    {
        return bindings::alloc(handle->value().url());
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
