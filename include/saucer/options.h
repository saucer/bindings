#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stddef.h>

    struct saucer_options;

    SAUCER_EXPORT saucer_options *saucer_options_new();
    SAUCER_EXPORT void saucer_options_free(saucer_options *);

    SAUCER_EXPORT void saucer_options_set_persistent_cookies(saucer_options *, bool enabled);
    SAUCER_EXPORT void saucer_options_set_hardware_acceleration(saucer_options *, bool enabled);

    SAUCER_EXPORT void saucer_options_set_storage_path(saucer_options *, const char *path);
    SAUCER_EXPORT void saucer_options_add_browser_flag(saucer_options *, const char *flag);

#ifdef __cplusplus
}
#endif
