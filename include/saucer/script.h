#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stdbool.h>

    enum SAUCER_LOAD_TIME
    {
        SAUCER_LOAD_TIME_CREATION,
        SAUCER_LOAD_TIME_READY,
    };

    enum SAUCER_WEB_FRAME
    {
        SAUCER_WEB_FRAME_TOP,
        SAUCER_WEB_FRAME_ALL,
    };

    struct saucer_script;

    SAUCER_EXPORT saucer_script *saucer_script_new(const char *code, SAUCER_LOAD_TIME time);
    SAUCER_EXPORT void saucer_script_free(saucer_script *);

    SAUCER_EXPORT void saucer_script_set_frame(saucer_script *, SAUCER_WEB_FRAME frame);
    SAUCER_EXPORT void saucer_script_set_permanent(saucer_script *, bool permanent);

#ifdef __cplusplus
}
#endif
