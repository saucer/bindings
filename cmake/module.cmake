function(saucer_bindings_add_module NAME MACRO)
    message(STATUS "[saucer-bindings] Adding module: ${NAME}")

    saucer_bindings_hide_symbols(${NAME})
    saucer_bindings_export(${NAME} ${MACRO})

    get_target_property(priv_includes saucer::bindings INCLUDE_DIRECTORIES)

    target_link_libraries(${NAME} PUBLIC saucer::bindings)
    target_include_directories(${NAME} PRIVATE ${priv_includes})
endfunction()
