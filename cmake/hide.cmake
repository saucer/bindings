function(saucer_bindings_hide_symbols NAME)
    set_target_properties(${NAME}
        PROPERTIES
        C_VISIBILITY_PRESET        hidden
        CXX_VISIBILITY_PRESET      hidden
        VISIBILITY_INLINES_HIDDEN  ON
        WINDOWS_EXPORT_ALL_SYMBOLS OFF
    )
endfunction()
