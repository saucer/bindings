#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include "app.h"

#include <stddef.h>

    struct saucer_preferences;

    SAUCER_EXPORT saucer_preferences *saucer_preferences_new(saucer_application *app);
    SAUCER_EXPORT void saucer_preferences_free(saucer_preferences *);

    SAUCER_EXPORT void saucer_preferences_set_persistent_cookies(saucer_preferences *, bool enabled);
    SAUCER_EXPORT void saucer_preferences_set_hardware_acceleration(saucer_preferences *, bool enabled);

    SAUCER_EXPORT void saucer_preferences_set_storage_path(saucer_preferences *, const char *path);
    SAUCER_EXPORT void saucer_preferences_add_browser_flag(saucer_preferences *, const char *flag);
    SAUCER_EXPORT void saucer_preferences_set_user_agent(saucer_preferences *, const char *user_agent);

#ifdef __cplusplus
}
#endif
