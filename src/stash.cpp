#include "stash.impl.hpp"

extern "C"
{
    const uint8_t *saucer_stash_data(saucer_stash *stash)
    {
        return (*stash)->data();
    }

    size_t saucer_stash_size(saucer_stash *stash)
    {
        return (*stash)->size();
    }

    void saucer_stash_free(saucer_stash *stash)
    {
        delete stash;
    }

    saucer_stash *saucer_stash_copy(saucer_stash *stash)
    {
        return saucer_stash::make(**stash);
    }

    saucer_stash *saucer_stash_new_from(uint8_t *data, size_t size)
    {
        return saucer_stash::from(saucer::stash::from({data, data + size}));
    }

    saucer_stash *saucer_stash_new_view(const uint8_t *data, size_t size)
    {
        return saucer_stash::from(saucer::stash::view({data, data + size}));
    }

    saucer_stash *saucer_stash_new_lazy(saucer_stash_lazy_callback callback, void *userdata)
    {
        auto fn = [callback, userdata]()
        {
            auto *stash = callback(userdata);
            auto rtn    = **stash;
            saucer_stash_free(stash);
            return rtn;
        };

        return saucer_stash::from(saucer::stash::lazy(fn));
    }

    saucer_stash *saucer_stash_new_from_str(const char *str)
    {
        return saucer_stash::from(saucer::stash::from_str(str));
    }

    saucer_stash *saucer_stash_new_view_str(const char *str)
    {
        return saucer_stash::from(saucer::stash::view_str(str));
    }

    saucer_stash *saucer_stash_new_empty()
    {
        return saucer_stash::from(saucer::stash::empty());
    }
}
