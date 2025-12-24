project(saucer-bindings-desktop LANGUAGES CXX VERSION 8.0.0)

# --------------------------------------------------------------------------------------------------------
# Setup library
# --------------------------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} SHARED)
add_library(saucer::bindings::desktop ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 23 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------------------------------------------------
# Include directories
# --------------------------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME} PUBLIC  "include")
target_include_directories(${PROJECT_NAME} PRIVATE "include/saucer")

# --------------------------------------------------------------------------------------------------------
# Add Sources
# --------------------------------------------------------------------------------------------------------

target_sources(${PROJECT_NAME} PRIVATE
    "src/desktop.cpp"
)

# --------------------------------------------------------------------------------------------------------
# Setup Dependencies
# --------------------------------------------------------------------------------------------------------

CPMFindPackage(
    NAME           saucer-desktop
    VERSION        4.2.0
    GIT_REPOSITORY "https://github.com/saucer/desktop"
)

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::desktop)
saucer_bindings_add_module(${PROJECT_NAME} "SAUCER_DESKTOP_EXPORT")
