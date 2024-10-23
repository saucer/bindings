#include "utils/string.hpp"

#include "memory.h"

char *bindings::alloc(const std::string &value)
{
    const auto size = value.size();
    char *const rtn = static_cast<char *>(saucer_memory_alloc(size + 1));

    value.copy(rtn, size);
    rtn[size + 1] = '\0';

    return rtn;
}
