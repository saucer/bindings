#include "icon.h"
#include "icon.hpp"

#include "stash.hpp"

extern "C"
{
    void saucer_icon_free(saucer_icon *handle)
    {
        delete handle;
    }

    bool saucer_icon_empty(saucer_icon *handle)
    {
        return handle->value().empty();
    }

    saucer_stash *saucer_icon_data(saucer_icon *handle)
    {
        return saucer_stash::from(handle->value().data());
    }

    void saucer_icon_save(saucer_icon *handle, const char *path)
    {
        handle->value().save(path);
    }

    void saucer_icon_from_file(saucer_icon **result, const char *file)
    {
        auto icon = saucer::icon::from(file);

        if (!icon)
        {
            return;
        }

        *result = saucer_icon::from(std::move(icon.value()));
    }

    void saucer_icon_from_data(saucer_icon **result, saucer_stash *stash)
    {
        auto icon = saucer::icon::from(stash->value());

        if (!icon)
        {
            return;
        }

        *result = saucer_icon::from(std::move(icon.value()));
    }
}
