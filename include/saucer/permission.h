#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "url.h"
#include "export.h"

#include <stdint.h>
#include <stdbool.h>

    /**
     * @remark Permission-Requests are reference counted. Please make sure to free all copies to properly release it!
     */
    struct saucer_permission_request;

    enum saucer_permission_type : uint8_t
    {
        SAUCER_PERMISSION_TYPE_UNKNOWN       = 0,
        SAUCER_PERMISSION_TYPE_AUDIO_MEDIA   = 1 << 0,
        SAUCER_PERMISSION_TYPE_VIDEO_MEDIA   = 1 << 1,
        SAUCER_PERMISSION_TYPE_DESKTOP_MEDIA = 1 << 2,
        SAUCER_PERMISSION_TYPE_MOUSE_LOCK    = 1 << 3,
        SAUCER_PERMISSION_TYPE_DEVICE_INFO   = 1 << 4,
        SAUCER_PERMISSION_TYPE_LOCATION      = 1 << 5,
        SAUCER_PERMISSION_TYPE_CLIPBOARD     = 1 << 6,
        SAUCER_PERMISSION_TYPE_NOTIFICATION  = 1 << 7,
    };

    SAUCER_EXPORT void saucer_permission_request_free(saucer_permission_request *);
    SAUCER_EXPORT saucer_permission_request *saucer_permission_request_copy(saucer_permission_request *);

    SAUCER_EXPORT saucer_url *saucer_permission_request_url(saucer_permission_request *);
    SAUCER_EXPORT saucer_permission_type saucer_permission_request_type(saucer_permission_request *);

    SAUCER_EXPORT void saucer_permission_request_accept(saucer_permission_request *, bool);

    /**
     * @note Please refer to the documentation in `application.h` on how to use this function.
     */
    SAUCER_EXPORT void saucer_permission_request_native(saucer_permission_request *, size_t, void *, size_t *);

#ifdef __cplusplus
}
#endif
