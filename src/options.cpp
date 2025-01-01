#include "options.h"
#include "options.hpp"

extern "C"
{
    saucer_options *saucer_options_new(const char *id)
    {
        return saucer_options::make(id);
    }

    void saucer_options_free(saucer_options *handle)
    {
        delete handle;
    }

    void saucer_options_set_argc(saucer_options *handle, int argc)
    {
        handle->value().argc = argc;
    }

    void saucer_options_set_argv(saucer_options *handle, char **argv)
    {
        handle->value().argv = argv;
    }

    void saucer_options_set_threads(saucer_options *handle, size_t threads)
    {
        handle->value().threads = threads;
    }
}
