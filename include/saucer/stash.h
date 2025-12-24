#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stdint.h>
#include <stddef.h>

    struct saucer_stash;

    SAUCER_EXPORT const uint8_t *saucer_stash_data(saucer_stash *);
    SAUCER_EXPORT size_t saucer_stash_size(saucer_stash *);

    typedef saucer_stash *(*saucer_stash_lazy_callback)(void *);

    SAUCER_EXPORT void saucer_stash_free(saucer_stash *);
    SAUCER_EXPORT saucer_stash *saucer_stash_copy(saucer_stash *);

    SAUCER_EXPORT saucer_stash *saucer_stash_new_from(uint8_t *, size_t);
    SAUCER_EXPORT saucer_stash *saucer_stash_new_view(const uint8_t *, size_t);
    SAUCER_EXPORT saucer_stash *saucer_stash_new_lazy(saucer_stash_lazy_callback, void *userdata);

    SAUCER_EXPORT saucer_stash *saucer_stash_new_from_str(const char *);
    SAUCER_EXPORT saucer_stash *saucer_stash_new_view_str(const char *);

    SAUCER_EXPORT saucer_stash *saucer_stash_new_empty();

#ifdef __cplusplus
}
#endif
