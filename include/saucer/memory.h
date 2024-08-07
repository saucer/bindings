#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <stddef.h>

    SAUCER_EXPORT void saucer_memory_free(void *data);
    SAUCER_EXPORT void *saucer_memory_alloc(size_t size);

#ifdef __cplusplus
}
#endif
