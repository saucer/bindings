#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "stash.h"
#include "export.h"

#include <stdbool.h>

    struct saucer_icon;

    SAUCER_EXPORT bool saucer_icon_empty(saucer_icon *);
    SAUCER_EXPORT saucer_stash *saucer_icon_data(saucer_icon *);

    SAUCER_EXPORT void saucer_icon_save(saucer_icon *, const char *);

    SAUCER_EXPORT void saucer_icon_free(saucer_icon *);
    SAUCER_EXPORT saucer_icon *saucer_icon_copy(saucer_icon *);

    SAUCER_EXPORT saucer_icon *saucer_icon_new_from_file(const char *, int *error);
    SAUCER_EXPORT saucer_icon *saucer_icon_new_from_stash(saucer_stash *, int *error);

    /**
     * @note Please refer to the documentation in `application.h` on how to use this function.
     */
    SAUCER_EXPORT void saucer_icon_native(saucer_icon *, size_t, void *, size_t *);

#ifdef __cplusplus
}
#endif
