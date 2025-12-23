#include "loop.h"
#include "app.impl.hpp"

#include "utils/opaque.hpp"

#include <saucer/modules/loop.hpp>

struct saucer_loop : saucer::bindings::opaque<saucer_loop, saucer::modules::loop>
{
};

extern "C"
{
    void saucer_loop_free(saucer_loop *loop)
    {
        delete loop;
    }

    saucer_loop *saucer_loop_new(saucer_application *app)
    {
        return saucer_loop::make(**app);
    }

    void saucer_loop_run(saucer_loop *loop)
    {
        (*loop)->run();
    }

    void saucer_loop_iteration(saucer_loop *loop)
    {
        (*loop)->iteration();
    }

    void saucer_loop_quit(saucer_loop *loop)
    {
        (*loop)->quit();
    }
}
