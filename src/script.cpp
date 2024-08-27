#include "script.h"
#include "script.hpp"

extern "C"
{
    saucer_script *saucer_script_new(const char *code, SAUCER_LOAD_TIME time)
    {
        return saucer_script::from(saucer::script{.code = code, .time = static_cast<saucer::load_time>(time)});
    }

    void saucer_script_free(saucer_script *handle)
    {
        delete handle;
    }

    void saucer_script_set_frame(saucer_script *handle, SAUCER_WEB_FRAME frame)
    {
        handle->value().frame = static_cast<saucer::web_frame>(frame);
    }

    void saucer_script_set_permanent(saucer_script *handle, bool permanent)
    {
        handle->value().permanent = permanent;
    }
}
