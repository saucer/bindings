#include "desktop.h"

#include "app.hpp"

#include "utils/string.hpp"
#include "utils/handle.hpp"

#include <saucer/memory.h>
#include <saucer/modules/desktop.hpp>

struct saucer_desktop : bindings::handle<saucer_desktop, saucer::modules::desktop>
{
};

struct saucer_picker_options : bindings::handle<saucer_picker_options, saucer::modules::picker::options>
{
};

extern "C"
{
    using saucer::modules::picker::type;

    saucer_desktop *saucer_desktop_new(saucer_application *app)
    {
        return saucer_desktop::make(app->value().get());
    }

    void saucer_desktop_free(saucer_desktop *handle)
    {
        delete handle;
    }

    void saucer_desktop_open(saucer_desktop *handle, const char *path)
    {
        handle->value().open(path);
    }

    saucer_picker_options *saucer_picker_options_new()
    {
        return saucer_picker_options::make();
    }

    void saucer_picker_options_free(saucer_picker_options *handle)
    {
        delete handle;
    }

    void saucer_picker_options_set_initial(saucer_picker_options *handle, const char *path)
    {
        handle->value().initial = path;
    }

    void saucer_picker_options_add_filter(saucer_picker_options *handle, const char *filter)
    {
        handle->value().filters.emplace(filter);
    }

    char *saucer_desktop_pick_file(saucer_desktop *handle, saucer_picker_options *options)
    {
        auto result = handle->value().pick<type::file>(options->value());

        if (!result)
        {
            return nullptr;
        }

        return bindings::alloc(result->string());
    }

    char *saucer_desktop_pick_folder(saucer_desktop *handle, saucer_picker_options *options)
    {
        auto result = handle->value().pick<type::folder>(options->value());

        if (!result)
        {
            return nullptr;
        }

        return bindings::alloc(result->string());
    }

    char **saucer_desktop_pick_files(saucer_desktop *handle, saucer_picker_options *options)
    {
        auto result = handle->value().pick<type::files>(options->value());

        if (!result)
        {
            return nullptr;
        }

        const auto count = result->size();
        auto **rtn       = static_cast<char **>(saucer_memory_alloc(count * sizeof(char *)));

        for (auto i = 0u; result->size() > i; i++)
        {
            rtn[i] = bindings::alloc(result->at(i));
        }

        return rtn;
    }

    char **saucer_desktop_pick_folders(saucer_desktop *handle, saucer_picker_options *options)
    {
        auto result = handle->value().pick<type::files>(options->value());

        if (!result)
        {
            return nullptr;
        }

        const auto count = result->size();
        auto **rtn       = static_cast<char **>(saucer_memory_alloc(count * sizeof(char *)));

        for (auto i = 0u; result->size() > i; i++)
        {
            rtn[i] = bindings::alloc(result->at(i));
        }

        return rtn;
    }
}
