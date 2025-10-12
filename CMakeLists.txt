cmake_minimum_required(VERSION 3.26)

project(BobbysBurden LANGUAGES CXX)

# Require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Platform defines
if(WIN32)
    add_definitions(-DMOBYDICK_PLATFORM_WINDOWS)
elseif(ANDROID)
    add_definitions(-DMOBYDICK_PLATFORM_ANDROID)
elseif(IOS)
    add_definitions(-DMOBYDICK_PLATFORM_IOS)
endif()

# --- Make BB reuse MobyDick's vcpkg-installed dependencies (all packages) ---

# Handle both single-config (Ninja) and multi-config (Visual Studio) generators
#  - For multi-config, CMAKE_BUILD_TYPE is empty; VS supplies the config at build time.
#  - We'll try common build subdirs in order: debug, release, (and a flat build/ too).
set(_bb_candidate_prefixes
    "${CMAKE_SOURCE_DIR}/../MobyDick_NEW/build/debug/vcpkg_installed/x64-windows"
    "${CMAKE_SOURCE_DIR}/../MobyDick_NEW/build/release/vcpkg_installed/x64-windows"
    "${CMAKE_SOURCE_DIR}/../MobyDick_NEW/build/vcpkg_installed/x64-windows"     # just in case
    "C:/projects/vcpkg/installed/x64-windows"                                    # global fallback
)

foreach(_p IN LISTS _bb_candidate_prefixes)
    if (EXISTS "${_p}/share")
        list(APPEND CMAKE_PREFIX_PATH "${_p}")
    endif()
endforeach()

# Optional: tell CMake what we appended (helpful for debugging once)
message(STATUS "CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")

# Bring in the engine (MobyDick)   adjust relative path as needed
add_subdirectory(../MobyDick_NEW ${CMAKE_BINARY_DIR}/MobyDickBuild)

# Gather all BobbysBurden source files
file(GLOB_RECURSE BOBBYSBURDEN_SOURCES
    "src/*.cpp"
    "src/*.h"
)

# Create a static library for the game
add_library(BobbysBurden STATIC
    ${BOBBYSBURDEN_SOURCES}
)

# Include directories for this project
target_include_directories(BobbysBurden
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ../MobyDick_NEW/include
)

# Link the engine (so BobbysBurden.lib depends on MobyDick.lib)
target_link_libraries(BobbysBurden
    PUBLIC
        MobyDick
)

# Optional diagnostics
message(STATUS "Building Bobby s Burden as a static library.")
message(STATUS "Linked against MobyDick engine.")
