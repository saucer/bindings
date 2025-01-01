#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <saucer/app.h>

    struct saucer_desktop;

    SAUCER_EXPORT saucer_desktop *saucer_desktop_new(saucer_application *app);
    SAUCER_EXPORT void saucer_desktop_free(saucer_desktop *);

    SAUCER_EXPORT void saucer_desktop_open(saucer_desktop *, const char *path);

    struct saucer_picker_options;

    SAUCER_EXPORT saucer_picker_options *saucer_picker_options_new();
    SAUCER_EXPORT void saucer_picker_options_free(saucer_picker_options *);

    SAUCER_EXPORT void saucer_picker_options_set_initial(saucer_picker_options *, const char *path);
    SAUCER_EXPORT void saucer_picker_options_add_filter(saucer_picker_options *, const char *filter);

    /**
     * @note The returned array will be populated with strings which are themselves dynamically allocated.
     *
     * To properly free the returned array you should:
     * - Free all strings within the array
     * - Free the array itself
     */
    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_desktop_pick_file(saucer_desktop *,
                                                                           saucer_picker_options *options);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT char *saucer_desktop_pick_folder(saucer_desktop *,
                                                                             saucer_picker_options *options);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT char **saucer_desktop_pick_files(saucer_desktop *,
                                                                             saucer_picker_options *options);

    /*[[sc::requires_free]]*/ SAUCER_EXPORT char **saucer_desktop_pick_folders(saucer_desktop *,
                                                                               saucer_picker_options *options);

#ifdef __cplusplus
}
#endif
