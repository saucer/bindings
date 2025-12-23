#include "scheme.impl.hpp"

#include "stash.impl.hpp"
#include "url.impl.hpp"

#include "utils/range.hpp"

#include <ranges>

extern "C"
{
    void saucer_scheme_response_free(saucer_scheme_response *response)
    {
        delete response;
    }

    saucer_scheme_response *saucer_scheme_response_new(saucer_stash *data, const char *mime)
    {
        return saucer_scheme_response::from(saucer::scheme::response{.data = **data, .mime = mime});
    }

    void saucer_scheme_response_append_header(saucer_scheme_response *response, const char *header, const char *value)
    {
        (*response)->headers.emplace(header, value);
    }

    void saucer_scheme_response_set_status(saucer_scheme_response *response, int status)
    {
        (*response)->status = status;
    }

    void saucer_scheme_request_free(saucer_scheme_request *request)
    {
        delete request;
    }

    saucer_scheme_request *saucer_scheme_request_copy(saucer_scheme_request *request)
    {
        return saucer_scheme_request::make(**request);
    }

    saucer_url *saucer_scheme_request_url(saucer_scheme_request *request)
    {
        return saucer_url::from((*request)->url());
    }

    void saucer_scheme_request_method(saucer_scheme_request *request, char *method, size_t *size)
    {
        saucer::bindings::return_range((*request)->method(), method, size);
    }

    saucer_stash *saucer_scheme_request_content(saucer_scheme_request *request)
    {
        return saucer_stash::from((*request)->content());
    }

    void saucer_scheme_request_headers(saucer_scheme_request *request, char *headers, size_t *size)
    {
        auto fmt = [](auto &header)
        {
            return std::format("{}: {}", header.first, header.second);
        };

        auto rtn = (*request)->headers()         //
                   | std::views::transform(fmt)  //
                   | std::views::join_with('\0') //
                   | std::ranges::to<std::string>();

        saucer::bindings::return_range(rtn, headers, size);
    }

    void saucer_scheme_executor_free(saucer_scheme_executor *executor)
    {
        delete executor;
    }

    saucer_scheme_executor *saucer_scheme_executor_copy(saucer_scheme_executor *executor)
    {
        return saucer_scheme_executor::make(**executor);
    }

    void saucer_scheme_executor_reject(saucer_scheme_executor *executor, saucer_scheme_error error)
    {
        (*executor)->reject(static_cast<saucer::scheme::error>(error));
    }

    void saucer_scheme_executor_accept(saucer_scheme_executor *executor, saucer_scheme_response *response)
    {
        (*executor)->resolve(**response);
    }
}
