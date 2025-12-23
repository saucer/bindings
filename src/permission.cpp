#include "permission.impl.hpp"

#include "url.impl.hpp"

extern "C"
{
    void saucer_permission_request_free(saucer_permission_request *request)
    {
        delete request;
    }

    saucer_permission_request *saucer_permission_request_copy(saucer_permission_request *request)
    {
        return saucer_permission_request::make(**request);
    }

    saucer_url *saucer_permission_request_url(saucer_permission_request *request)
    {
        return saucer_url::from((**request)->url());
    }

    saucer_permission_type saucer_permission_request_type(saucer_permission_request *request)
    {
        return static_cast<saucer_permission_type>((**request)->type());
    }

    void saucer_permission_request_accept(saucer_permission_request *request, bool value)
    {
        (**request)->accept(value);
    }
}
