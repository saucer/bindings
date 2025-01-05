#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"

#include <saucer/webview.h>

    enum SAUCER_LAYOUT
    {
        SAUCER_LAYOUT_PORTRAIT,
        SAUCER_LAYOUT_LANDSCAPE,
    };

    struct saucer_print_settings;

    SAUCER_PDF_EXPORT saucer_print_settings *saucer_print_settings_new();
    SAUCER_PDF_EXPORT void saucer_print_settings_free(saucer_print_settings *);

    SAUCER_PDF_EXPORT void saucer_print_settings_set_file(saucer_print_settings *, const char *file);
    SAUCER_PDF_EXPORT void saucer_print_settings_set_orientation(saucer_print_settings *, SAUCER_LAYOUT orientation);

    SAUCER_PDF_EXPORT void saucer_print_settings_set_width(saucer_print_settings *, double width);
    SAUCER_PDF_EXPORT void saucer_print_settings_set_height(saucer_print_settings *, double height);

    struct saucer_pdf;

    SAUCER_PDF_EXPORT saucer_pdf *saucer_pdf_new(saucer_handle *webview);
    SAUCER_PDF_EXPORT void saucer_pdf_free(saucer_pdf *);

    SAUCER_PDF_EXPORT void saucer_pdf_save(saucer_pdf *, saucer_print_settings *settings);

#ifdef __cplusplus
}
#endif
