#include "pdf.h"

#include "webview.hpp"
#include "utils/handle.hpp"

#include <saucer/modules/pdf.hpp>

struct saucer_print_settings : bindings::handle<saucer_print_settings, saucer::modules::print_settings>
{
};

struct saucer_pdf : bindings::handle<saucer_pdf, saucer::modules::pdf>
{
};

extern "C"
{
    saucer_print_settings *saucer_print_settings_new()
    {
        return saucer_print_settings::make();
    }

    void saucer_print_settings_free(saucer_print_settings *handle)
    {
        delete handle;
    }

    void saucer_print_settings_set_file(saucer_print_settings *handle, const char *file)
    {
        handle->value().file = file;
    }

    void saucer_print_settings_set_orientation(saucer_print_settings *handle, SAUCER_LAYOUT orientation)
    {
        handle->value().orientation = static_cast<saucer::modules::layout>(orientation);
    }

    void saucer_print_settings_set_width(saucer_print_settings *handle, double width)
    {
        handle->value().size.first = width;
    }

    void saucer_print_settings_set_height(saucer_print_settings *handle, double height)
    {
        handle->value().size.second = height;
    }

    saucer_pdf *saucer_pdf_new(saucer_handle *webview)
    {
        return saucer_pdf::make(webview);
    }

    void saucer_pdf_free(saucer_pdf *handle)
    {
        delete handle;
    }

    void saucer_pdf_save(saucer_pdf *handle, saucer_print_settings *settings)
    {
        handle->value().save(settings->value());
    }
}
