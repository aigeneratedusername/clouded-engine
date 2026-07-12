cmake_minimum_required(VERSION 3.21)
project(clouded C CXX)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(EXE_NAME "clouded-engine")

# ---------------------------------------------------------------------------
# Platform selection
# Pass -DPLATFORM=Linux|Windows|Mac|N3DS|PSVita on the cmake configure line.
# Defaults to Linux.
# ---------------------------------------------------------------------------
set(VALID_PLATFORMS Linux Windows Mac N3DS PSVita)
if(NOT PLATFORM IN_LIST VALID_PLATFORMS)
    message(FATAL_ERROR "Unknown platform '${PLATFORM}'. Choose one of: ${VALID_PLATFORMS}")
endif()

if(PLATFORM STREQUAL "Linux" OR PLATFORM STREQUAL "Windows" OR PLATFORM STREQUAL "Mac")
    set(PLATFORM_DESKTOP TRUE)
else()
    set(PLATFORM_DESKTOP FALSE)
endif()

set(PLATFORM "Linux" CACHE STRING "Target build platform")
set_property(CACHE PLATFORM PROPERTY STRINGS Linux Windows Mac N3DS PSVita)
message(STATUS "Building for platform: ${PLATFORM}")

# ---------------------------------------------------------------------------
# Configure compile options
# ---------------------------------------------------------------------------
add_compile_options(
    -fno-sanitize=undefined
    -ffunction-sections
)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>)
add_compile_options($<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>)

# ---------------------------------------------------------------------------
# Source lists
# ---------------------------------------------------------------------------

# Platform
set(PLATFORM_SOURCES_COMMON
    src/core/platform/platform.c
    src/core/platform/internal/internal.c
    src/core/platform/internal/memory.c
    src/core/platform/types.c
    src/core/platform/util.c
)

if(PLATFORM_DESKTOP STREQUAL "TRUE")
    set(PLATFORM_SOURCES
        src/core/platform/sdl/audio/audio.c
        src/core/platform/sdl/io/io.c
        src/core/platform/sdl/memory/memory.c
        src/core/platform/sdl/system/system.c
        src/core/platform/sdl/video/screen.c
    )
elseif(PLATFORM STREQUAL "N3DS")
    set(PLATFORM_SOURCES
        src/core/platform/3ds/audio/audio.c
        src/core/platform/3ds/io/io.c
        src/core/platform/3ds/memory/memory.c
        src/core/platform/3ds/system/system.c
        src/core/platform/3ds/video/screen.c
    )
elseif(PLATFORM STREQUAL "PSVita")
    set(PLATFORM_SOURCES
        src/core/platform/vita/audio/audio.c
        src/core/platform/vita/io/io.c
        src/core/platform/vita/memory/memory.c
        src/core/platform/vita/system/system.c
        src/core/platform/vita/video/screen.c
    )
endif()

# Vendor
set(VENDOR_SOURCES
    vendor/stb/stb.c
    vendor/tomlc17/tomlc17.c
)

set(VENDOR_SOURCES_PLATSPEC)
if(PLATFORM_DESKTOP STREQUAL "TRUE")
    set(VENDOR_SOURCES_PLATSPEC
        vendor/glad/src/glad.c
    )
endif()

#Engine Renderer Backend
if(PLATFORM_DESKTOP STREQUAL "TRUE")
    set(ENGINE_RENDERBACK_SOURCE
        src/core/renderer/backends/desktop-opengl.cpp
    )
elseif(PLATFORM STREQUAL "N3DS")
    set(ENGINE_RENDERBACK_SOURCE
        src/core/renderer/backends/3ds-citro3d.cpp
    )
endif()

# Engine
set(ENGINE_SOURCES
    src/engine.cpp
    src/core/util.cpp
)

set_source_files_properties(
    ${PLATFORM_SOURCES_COMMON}
    ${PLATFORM_SOURCES}
    ${VENDOR_SOURCES}
    ${VENDOR_SOURCES_PLATSPEC}
    PROPERTIES LANGUAGE C
)

set_source_files_properties(
    ${ENGINE_SOURCES}
    ${ENGINE_RENDERBACK_SOURCE}
    PROPERTIES LANGUAGE CXX
)

# ---------------------------------------------------------------------------
# libengine
# ---------------------------------------------------------------------------
add_library(engine STATIC
    ${PLATFORM_SOURCES_COMMON}
    ${PLATFORM_SOURCES}
    ${VENDOR_SOURCES}
    ${VENDOR_SOURCES_PLATSPEC}
    ${ENGINE_SOURCES}
)

target_include_directories(engine PUBLIC
    include
    vendor/stb
    vendor/tomlc17
)

# ---------------------------------------------------------------------------
# Platform-specific setup
# ---------------------------------------------------------------------------
if(PLATFORM_DESKTOP STREQUAL "TRUE")
    include(cmake/platform-desktop.cmake)
elseif(PLATFORM STREQUAL "N3DS")
    include(cmake/platform-3ds.cmake)
elseif(PLATFORM STREQUAL "PSVita")
    include(cmake/platform-vita.cmake)
endif()
