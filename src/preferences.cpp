#include "preferences.h"
#include "preferences.hpp"

#include "app.hpp"

extern "C"
{
    saucer_preferences *saucer_preferences_new(saucer_application *app)
    {
        return saucer_preferences::from({
            .application = app->value(),
        });
    }

    void saucer_preferences_free(saucer_preferences *handle)
    {
        delete handle;
    }

    void saucer_preferences_set_persistent_cookies(saucer_preferences *handle, bool enabled)
    {
        handle->value().persistent_cookies = enabled;
    }

    void saucer_preferences_set_hardware_acceleration(saucer_preferences *handle, bool enabled)
    {
        handle->value().hardware_acceleration = enabled;
    }

    void saucer_preferences_set_storage_path(saucer_preferences *handle, const char *path)
    {
        handle->value().storage_path = path;
    }

    void saucer_preferences_add_browser_flag(saucer_preferences *handle, const char *flag)
    {
        handle->value().browser_flags.emplace(flag);
    }

    void saucer_preferences_set_user_agent(saucer_preferences *handle, const char *user_agent)
    {
        handle->value().user_agent = user_agent;
    }
}
