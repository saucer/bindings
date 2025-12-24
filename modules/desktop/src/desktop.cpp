#include "desktop.h"
#include "app.impl.hpp"

#include "utils/wide.hpp"
#include "utils/range.hpp"
#include "utils/opaque.hpp"

#include <saucer/modules/desktop.hpp>

struct saucer_desktop : saucer::bindings::opaque<saucer_desktop, saucer::modules::desktop>
{
};

struct saucer_picker_options : saucer::bindings::opaque<saucer_picker_options, saucer::modules::picker::options>
{
};

template <saucer::modules::picker::type T>
void pick(saucer_desktop *desktop, saucer_picker_options *opts, char *out, size_t *size, int *error)
{
    using result_t                  = saucer::modules::picker::result_t<T>;
    static thread_local auto result = saucer::result<result_t>{};

    if (!out)
    {
        result = (*desktop)->pick<T>(opts ? **opts : saucer::modules::picker::options{});
    }

    if (!result.has_value() && error)
    {
        *error = result.error().code();
    }

    if (!result.has_value())
    {
        return;
    }

    auto final = std::vector<char>{};

    if constexpr (std::ranges::range<result_t>)
    {
        for (const auto &path : *result)
        {
            final.insert_range(final.end(), saucer::bindings::vectorize(path.string()));
            final.emplace_back('\0');
        }

        if (!final.empty())
        {
            final.pop_back();
        }
    }
    else
    {
        final = saucer::bindings::vectorize(result.string());
    }

    saucer::bindings::return_range(final, out, size);
}

extern "C"
{
    saucer_picker_options *saucer_picker_options_new()
    {
        return saucer_picker_options::from({});
    }

    void saucer_picker_options_free(saucer_picker_options *options)
    {
        delete options;
    }

    void saucer_picker_options_set_initial(saucer_picker_options *options, const char *initial)
    {
        (*options)->initial = saucer::bindings::u8path(initial);
    }

    void saucer_picker_options_set_filters(saucer_picker_options *opts, const char *filters, size_t size)
    {
        auto final = std::set<std::string>{};

        for (const char *str = filters; str - filters < size; str += std::char_traits<char>::length(str) + 1)
        {
            final.emplace(str);
        }

        (*opts)->filters = std::move(final);
    }

    void saucer_desktop_free(saucer_desktop *desktop)
    {
        delete desktop;
    }

    saucer_desktop *saucer_desktop_new(saucer_application *app)
    {
        return saucer_desktop::make((*app).ptr());
    }

    void saucer_desktop_mouse_position(saucer_desktop *desktop, int *x, int *y)
    {
        auto pos = (*desktop)->mouse_position();
        *x       = pos.x;
        *y       = pos.y;
    }

    using saucer::modules::picker::type;

    void saucer_picker_pick_file(saucer_desktop *desktop, saucer_picker_options *options, char *file, size_t *size,
                                 int *error)
    {
        pick<type::file>(desktop, options, file, size, error);
    }

    void saucer_picker_pick_folder(saucer_desktop *desktop, saucer_picker_options *options, char *folder, size_t *size,
                                   int *error)
    {
        pick<type::folder>(desktop, options, folder, size, error);
    }

    void saucer_picker_pick_files(saucer_desktop *desktop, saucer_picker_options *options, char *files, size_t *size,
                                  int *error)
    {
        pick<type::files>(desktop, options, files, size, error);
    }

    void saucer_desktop_pick_save(saucer_desktop *desktop, saucer_picker_options *options, char *location, size_t *size,
                                  int *error)
    {
        pick<type::save>(desktop, options, location, size, error);
    }

    void saucer_desktop_open(saucer_desktop *desktop, const char *path)
    {
        (*desktop)->open(path);
    }
}
