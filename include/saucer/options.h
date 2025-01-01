#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

    struct saucer_options;

    SAUCER_EXPORT saucer_options *saucer_options_new(const char *id);
    SAUCER_EXPORT void saucer_options_free(saucer_options *);

    SAUCER_EXPORT void saucer_options_set_argc(saucer_options *, int argc);
    SAUCER_EXPORT void saucer_options_set_argv(saucer_options *, char **argv);

    SAUCER_EXPORT void saucer_options_set_threads(saucer_options *, size_t threads);

#ifdef __cplusplus
}
#endif
