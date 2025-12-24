project(saucer-bindings-loop LANGUAGES CXX VERSION 8.0.0)

# --------------------------------------------------------------------------------------------------------
# Setup library
# --------------------------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} SHARED)
add_library(saucer::bindings::loop ALIAS ${PROJECT_NAME})

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
    "src/loop.cpp"
)

# --------------------------------------------------------------------------------------------------------
# Setup Dependencies
# --------------------------------------------------------------------------------------------------------

CPMFindPackage(
    NAME           saucer-loop
    VERSION        2.1.0
    GIT_REPOSITORY "https://github.com/saucer/loop"
)

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::loop)
saucer_bindings_add_module(${PROJECT_NAME} "SAUCER_LOOP_EXPORT")
