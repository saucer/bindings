#include "url.impl.hpp"

#include "utils/wide.hpp"
#include "utils/range.hpp"

extern "C"
{
    void saucer_url_free(saucer_url *url)
    {
        delete url;
    }

    saucer_url *saucer_url_copy(saucer_url *url)
    {
        return saucer_url::make(**url);
    }

    saucer_url *saucer_url_new_parse(const char *value, int *error)
    {
        auto rtn = saucer::url::parse(value);

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_url::from(std::move(*rtn));
    }

    saucer_url *saucer_url_new_from(const char *value, int *error)
    {
        auto rtn = saucer::url::from(saucer::bindings::u8path(value));

        if (!rtn.has_value() && error)
        {
            *error = rtn.error().code();
        }

        if (!rtn.has_value())
        {
            return nullptr;
        }

        return saucer_url::from(std::move(*rtn));
    }

    saucer_url *saucer_url_new_opts(const char *scheme, const char *host, size_t *port, const char *path)
    {
        auto options = saucer::url::options{
            .scheme = scheme,
            .path   = saucer::bindings::u8path(path),
        };

        if (host)
        {
            options.host = host;
        }

        if (port)
        {
            options.port = *port;
        }

        return saucer_url::from(saucer::url::make(options));
    }

    void saucer_url_string(saucer_url *url, char *string, size_t *size)
    {
        saucer::bindings::return_range((*url)->string(), string, size);
    }

    void saucer_url_path(saucer_url *url, char *path, size_t *size)
    {
        saucer::bindings::return_range((*url)->path().string(), path, size);
    }

    void saucer_url_scheme(saucer_url *url, char *scheme, size_t *size)
    {
        saucer::bindings::return_range((*url)->scheme(), scheme, size);
    }

    void saucer_url_host(saucer_url *url, char *host, size_t *size)
    {
        saucer::bindings::return_range((*url)->host(), host, size);
    }

    bool saucer_url_port(saucer_url *url, size_t *port)
    {
        auto rtn = (*url)->port();

        if (rtn.has_value())
        {
            *port = *rtn;
        }

        return rtn.has_value();
    }

    void saucer_url_user(saucer_url *url, char *user, size_t *size)
    {
        saucer::bindings::return_range((*url)->user(), user, size);
    }

    void saucer_url_password(saucer_url *url, char *password, size_t *size)
    {
        saucer::bindings::return_range((*url)->password(), password, size);
    }
}
