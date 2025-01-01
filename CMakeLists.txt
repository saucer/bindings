cmake_minimum_required(VERSION 3.21)
project(saucer-bindings LANGUAGES CXX VERSION 5.0.0)

# --------------------------------------------------------------------------------------------------------
# Library switches
# --------------------------------------------------------------------------------------------------------

option(saucer_desktop "Enable support for the desktop module" ON)

# --------------------------------------------------------------------------------------------------------
# CMake options
# --------------------------------------------------------------------------------------------------------

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --------------------------------------------------------------------------------------------------------
# Setup library
# --------------------------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} SHARED)
add_library(saucer::bindings ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

if (PROJECT_IS_TOP_LEVEL AND NOT MSVC AND NOT CMAKE_CXX_SIMULATE_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror -pedantic -pedantic-errors -Wfatal-errors)
endif()

if (NOT MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -Wno-unknown-warning-option -Wno-missing-field-initializers -Wno-cast-function-type)
endif()

# --------------------------------------------------------------------------------------------------------
# Export header
# --------------------------------------------------------------------------------------------------------

include("cmake/hide.cmake")
include("cmake/export.cmake")

saucer_bindings_hide_symbols(${PROJECT_NAME})
saucer_bindings_export(${PROJECT_NAME} "SAUCER_EXPORT")

# --------------------------------------------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC  "include")
target_include_directories(${PROJECT_NAME} PRIVATE "include/saucer" "private")

# --------------------------------------------------------------------------------------------------------
# Add Sources
# --------------------------------------------------------------------------------------------------------

target_sources(${PROJECT_NAME} PRIVATE 
    "src/app.cpp"
    "src/options.cpp"
    
    "src/memory.cpp"
    
    "src/icon.cpp"
    "src/stash.cpp"
    "src/script.cpp"
    "src/scheme.cpp"

    "src/navigation.cpp"
    "src/preferences.cpp"
    
    "src/window.cpp"
    "src/webview.cpp"
)

# --------------------------------------------------------------------------------------------------------
# Setup Dependencies
# --------------------------------------------------------------------------------------------------------

include("cmake/cpm.cmake")

CPMFindPackage(
  NAME           saucer
  VERSION        5.0.0
  GIT_REPOSITORY "https://github.com/saucer/saucer"
  OPTIONS        "saucer_static OFF" "CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON"
)

target_link_libraries(${PROJECT_NAME} PUBLIC saucer::saucer)

# --------------------------------------------------------------------------------------------------------
# Setup Modules
# --------------------------------------------------------------------------------------------------------

include("cmake/module.cmake")

if (saucer_desktop)
  add_subdirectory("modules/desktop")
endif()
