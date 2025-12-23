#include "pdf.h"
#include "webview.impl.hpp"

#include "utils/wide.hpp"
#include "utils/opaque.hpp"

#include <saucer/modules/pdf.hpp>

struct saucer_pdf : saucer::bindings::opaque<saucer_pdf, saucer::modules::pdf>
{
};

struct saucer_pdf_settings : saucer::bindings::opaque<saucer_pdf_settings, saucer::modules::pdf::settings>
{
};

extern "C"
{
    void saucer_pdf_settings_free(saucer_pdf_settings *settings)
    {
        delete settings;
    }

    saucer_pdf_settings *saucer_pdf_settings_new(const char *path)
    {
        return saucer_pdf_settings::from({.file = saucer::bindings::u8path(path)});
    }

    void saucer_pdf_settings_set_size(saucer_pdf_settings *settings, double w, double h)
    {
        (*settings)->size = {.w = w, .h = h};
    }

    void saucer_pdf_settings_set_orientation(saucer_pdf_settings *settings, saucer_pdf_layout layout)
    {
        (*settings)->orientation = static_cast<saucer::modules::pdf::layout>(layout);
    }

    void saucer_pdf_free(saucer_pdf *pdf)
    {
        delete pdf;
    }

    saucer_pdf *saucer_pdf_new(saucer_webview *webview)
    {
        return saucer_pdf::make(**webview);
    }

    void saucer_pdf_save(saucer_pdf *pdf, saucer_pdf_settings *settings)
    {
        (*pdf)->save(**settings);
    }
}
