#include "scheme.h"
#include "scheme.hpp"

#include "memory.h"
#include "stash.hpp"

#include <ranges>
#include <cstring>

extern "C"
{
    saucer_scheme_response *saucer_scheme_response_new(saucer_stash *data, const char *mime)
    {
        return saucer_scheme_response::from({{saucer::scheme::response{data->value(), mime, {}}}});
    }

    saucer_scheme_response *saucer_scheme_response_unexpected(SAUCER_SCHEME_ERROR error)
    {
        return saucer_scheme_response::from(
            tl::unexpected<saucer::scheme::error>{static_cast<saucer::scheme::error>(error)});
    }

    void saucer_scheme_response_free(saucer_scheme_response *handle)
    {
        delete handle;
    }

    void saucer_scheme_response_set_status(saucer_scheme_response *handle, int status)
    {
        handle->value()->status = status;
    }

    void saucer_scheme_response_add_header(saucer_scheme_response *handle, const char *header, const char *value)
    {
        handle->value()->headers.emplace(header, value);
    }

    char *saucer_scheme_request_url(saucer_scheme_request *handle)
    {
        auto url = handle->value()->url();

        auto *rtn = static_cast<char *>(saucer_memory_alloc(url.capacity()));
        strncpy(rtn, url.data(), url.capacity());

        return rtn;
    }

    char *saucer_scheme_request_method(saucer_scheme_request *handle)
    {
        auto method = handle->value()->method();

        auto *rtn = static_cast<char *>(saucer_memory_alloc(method.capacity()));
        strncpy(rtn, method.data(), method.capacity());

        return rtn;
    }

    saucer_stash *saucer_scheme_request_content(saucer_scheme_request *handle)
    {
        return saucer_stash::from(handle->value()->content());
    }

    void saucer_scheme_request_headers(saucer_scheme_request *handle, char ***headers, char ***values, size_t *count)
    {
        auto data = handle->value()->headers();
        *count    = data.size();

        *headers = static_cast<char **>(saucer_memory_alloc(*count * sizeof(char *)));
        *values  = static_cast<char **>(saucer_memory_alloc(*count * sizeof(char *)));

        for (auto it = data.begin(); it != data.end(); it++)
        {
            const auto &[header, value] = *it;
            const auto index            = std::distance(data.begin(), it);

            (*headers)[index] = static_cast<char *>(saucer_memory_alloc(header.capacity()));
            (*values)[index]  = static_cast<char *>(saucer_memory_alloc(value.capacity()));

            strncpy((*headers)[index], header.data(), header.capacity());
            strncpy((*values)[index], value.data(), value.capacity());
        }
    }
}
