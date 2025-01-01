cmake_minimum_required(VERSION 3.21)
project(saucer-bindings LANGUAGES CXX VERSION 5.0.0)

# --------------------------------------------------------------------------------------------------------
# CMake options
# --------------------------------------------------------------------------------------------------------

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

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

include(GenerateExportHeader)

generate_export_header(
    ${PROJECT_NAME} 
    EXPORT_MACRO_NAME "SAUCER_EXPORT"
    EXPORT_FILE_NAME "${CMAKE_CURRENT_SOURCE_DIR}/include/saucer/export.h"
)

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

    "src/string.cpp"
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
  OPTIONS        "saucer_static OFF"
)

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::saucer)
