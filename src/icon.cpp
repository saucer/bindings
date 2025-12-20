#include "icon.impl.hpp"
#include "stash.impl.hpp"

extern "C"
{
    bool saucer_icon_empty(saucer_icon *icon)
    {
        return (*icon)->empty();
    }

    saucer_stash *saucer_icon_data(saucer_icon *icon)
    {
        return saucer_stash::from((*icon)->data());
    }

    void saucer_icon_save(saucer_icon *icon, const char *path)
    {
        // TODO: widen on windows
        (*icon)->save(path);
    }

    void saucer_icon_free(saucer_icon *icon)
    {
        delete icon;
    }

    saucer_icon *saucer_icon_new_from_file(const char *path, int *error)
    {
        // TODO: widen on windows
        auto rtn = saucer::icon::from(path);

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_icon::from(std::move(*rtn));
    }

    saucer_icon *saucer_icon_new_from_stash(saucer_stash *stash, int *error)
    {
        auto rtn = saucer::icon::from(**stash);

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_icon::from(std::move(*rtn));
    }
}
