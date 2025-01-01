include(GenerateExportHeader)

function(saucer_bindings_export NAME MACRO)
    generate_export_header(
      ${NAME}
      EXPORT_MACRO_NAME "${MACRO}"
      EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/saucer/export.h"
    )
endfunction()
