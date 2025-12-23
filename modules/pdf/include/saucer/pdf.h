#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "export.h"
#include "webview.h"

#include <cstdint>

    struct saucer_pdf;
    struct saucer_pdf_settings;

    enum saucer_pdf_layout : uint8_t
    {
        SAUCER_PDF_LAYOUT_PORTRAIT,
        SAUCER_PDF_LAYOUT_LANDSCAPE,
    };

    SAUCER_PDF_EXPORT void saucer_pdf_settings_free(saucer_pdf_settings *);
    SAUCER_PDF_EXPORT saucer_pdf_settings *saucer_pdf_settings_new(const char *);

    SAUCER_PDF_EXPORT void saucer_pdf_settings_set_size(saucer_pdf_settings *, double w, double h);
    SAUCER_PDF_EXPORT void saucer_pdf_settings_set_orientation(saucer_pdf_settings *, saucer_pdf_layout);

    SAUCER_PDF_EXPORT void saucer_pdf_free(saucer_pdf *);
    SAUCER_PDF_EXPORT saucer_pdf *saucer_pdf_new(saucer_webview *);

    SAUCER_PDF_EXPORT void saucer_pdf_save(saucer_pdf *, saucer_pdf_settings *);

#ifdef __cplusplus
}
#endif
