#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "app.h"
#include "export.h"

#include <stdbool.h>

    struct saucer_desktop;
    struct saucer_picker_options;

    SAUCER_DESKTOP_EXPORT saucer_picker_options *saucer_picker_options_new();
    SAUCER_DESKTOP_EXPORT void saucer_picker_options_free(saucer_picker_options *);

    SAUCER_DESKTOP_EXPORT void saucer_picker_options_set_initial(saucer_picker_options *, const char *);
    /**
     * @remark Expects the filters in the format of: "filter1\0filter2\0filter3\0"
     */
    SAUCER_DESKTOP_EXPORT void saucer_picker_options_set_filters(saucer_picker_options *, const char *, size_t);

    SAUCER_DESKTOP_EXPORT void saucer_desktop_free(saucer_desktop *);
    SAUCER_DESKTOP_EXPORT saucer_desktop *saucer_desktop_new(saucer_application *);

    SAUCER_DESKTOP_EXPORT void saucer_desktop_mouse_position(saucer_desktop *, int *x, int *y);

    SAUCER_DESKTOP_EXPORT void saucer_picker_pick_file(saucer_desktop *, saucer_picker_options *, char *, size_t *,
                                                       int *error);
    SAUCER_DESKTOP_EXPORT void saucer_picker_pick_folder(saucer_desktop *, saucer_picker_options *, char *, size_t *,
                                                         int *error);
    SAUCER_DESKTOP_EXPORT void saucer_picker_pick_files(saucer_desktop *, saucer_picker_options *, char *, size_t *,
                                                        int *error);

    SAUCER_DESKTOP_EXPORT void saucer_picker_save(saucer_desktop *, saucer_picker_options *, char *, size_t *,
                                                  int *error);

    SAUCER_DESKTOP_EXPORT void saucer_desktop_open(saucer_desktop *, const char *);

#ifdef __cplusplus
}
#endif
