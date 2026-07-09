# cmake/platform-vita.cmake
# Builds a .vpk for the PS Vita using VITASDK.
# This file is included by CMakeLists.txt when PLATFORM=PSVita.
#
# Prerequisites:
#   - VITASDK installed and $VITASDK set in your environment (see toolchain-vita.cmake)
#   - Configure with the bundled toolchain:
#       cmake -DPLATFORM=PSVita \
#             -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vita.cmake \
#             -DCMAKE_BUILD_TYPE=Release \
#             ..
#
# Output artefacts:
#   zmicropg.velf   — relocated ELF (intermediate)
#   zmicropg.self   — signed ELF (eboot.bin before rename)
#   zmicropg.vpk    — installable homebrew package
#
# App metadata — edit these to match your project:
set(VITA_APP_NAME  "zmicropg")
set(VITA_TITLEID   "ZMCR00001")   # Must be exactly 9 chars: XXXX#####
set(VITA_VERSION   "01.00")

message(STATUS "Configuring PS Vita target")

if(NOT DEFINED ENV{VITASDK})
    message(FATAL_ERROR
        "VITASDK environment variable is not set.\n"
        "Install the Vita SDK from https://vitasdk.org/ "
        "and set VITASDK=/path/to/vitasdk in your environment.")
endif()

set(VITASDK "$ENV{VITASDK}")

# ---------------------------------------------------------------------------
# SDK include / library paths
# ---------------------------------------------------------------------------
foreach(tgt platform engine)
    target_include_directories(${tgt} PRIVATE
        "${VITASDK}/arm-vita-eabi/include"
    )
endforeach()

# ---------------------------------------------------------------------------
# Main object target
# ---------------------------------------------------------------------------
add_library(zmicropg_obj OBJECT src/main.cpp)   # rename to .c if pure C
target_include_directories(zmicropg_obj PRIVATE
    "${VITASDK}/arm-vita-eabi/include"
    src/platform
    vendor/stb
    vendor/tomlc17
)
target_link_libraries(zmicropg_obj PRIVATE engine platform)

# ---------------------------------------------------------------------------
# Paths for the multi-step packaging pipeline
# ---------------------------------------------------------------------------
set(ELF_OUT   "${CMAKE_BINARY_DIR}/zmicropg.elf")
set(VELF_OUT  "${CMAKE_BINARY_DIR}/zmicropg.velf")
set(SELF_OUT  "${CMAKE_BINARY_DIR}/eboot.bin")
set(VPK_OUT   "${CMAKE_BINARY_DIR}/zmicropg.vpk")

set(LIBPLATFORM "${CMAKE_BINARY_DIR}/libplatform.a")
set(LIBENGINE   "${CMAKE_BINARY_DIR}/libengine.a")

# ---------------------------------------------------------------------------
# Step 1 — link ELF
# Standard VITASDK libs: SceLibc_stub, SceDisplay_stub, etc.
# Add / remove stubs to match what your vita platform layer actually calls.
# ---------------------------------------------------------------------------
add_custom_command(
    OUTPUT  ${ELF_OUT}
    COMMAND ${VITASDK}/bin/arm-vita-eabi-gcc
            -Wl,-q           # keep relocations for vita-elf-create
            -o ${ELF_OUT}
            $<TARGET_OBJECTS:zmicropg_obj>
            ${LIBENGINE}
            ${LIBPLATFORM}
            -L${VITASDK}/arm-vita-eabi/lib
            -lSceLibc_stub
            -lSceKernel_stub
            -lSceDisplay_stub
            -lSceGxm_stub
            -lSceCtrl_stub
            -lSceAudio_stub
            -lSceRtc_stub
            -lSceSysmodule_stub
            -lm
    DEPENDS zmicropg_obj engine platform
    COMMENT "Linking Vita ELF"
    VERBATIM
)

# ---------------------------------------------------------------------------
# Step 2 — vita-elf-create: strips / relocates the ELF for the Vita loader
# ---------------------------------------------------------------------------
add_custom_command(
    OUTPUT  ${VELF_OUT}
    COMMAND ${VITASDK}/bin/vita-elf-create ${ELF_OUT} ${VELF_OUT}
    DEPENDS ${ELF_OUT}
    COMMENT "Creating Vita ELF (velf)"
    VERBATIM
)

# ---------------------------------------------------------------------------
# Step 3 — vita-make-fself: produces a signed ELF (eboot.bin)
# ---------------------------------------------------------------------------
add_custom_command(
    OUTPUT  ${SELF_OUT}
    COMMAND ${VITASDK}/bin/vita-make-fself -s ${VELF_OUT} ${SELF_OUT}
    DEPENDS ${VELF_OUT}
    COMMENT "Creating eboot.bin (fself)"
    VERBATIM
)

# ---------------------------------------------------------------------------
# Step 4 — vita-pack-vpk: bundles eboot.bin + assets into a .vpk
#
# The sce_sys directory layout expected by vita-pack-vpk:
#   sce_sys/icon0.png        — 128×128 app icon
#   sce_sys/livearea/...     — LiveArea assets (optional for homebrew)
#
# Create a minimal sce_sys/ folder in your source tree; vita-pack-vpk will
# warn (but still succeed) if it's missing entirely.
# ---------------------------------------------------------------------------
add_custom_command(
    OUTPUT  ${VPK_OUT}
    COMMAND ${VITASDK}/bin/vita-pack-vpk
            -s ${CMAKE_SOURCE_DIR}/sce_sys/param.sfo   # built below
            -b ${SELF_OUT}
            ${VPK_OUT}
    DEPENDS ${SELF_OUT} ${CMAKE_BINARY_DIR}/sce_sys/param.sfo
    COMMENT "Packing .vpk"
    VERBATIM
)

# ---------------------------------------------------------------------------
# param.sfo — minimal app metadata file required by every .vpk
# vita-mksfoex is part of VITASDK.
# ---------------------------------------------------------------------------
add_custom_command(
    OUTPUT  ${CMAKE_BINARY_DIR}/sce_sys/param.sfo
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/sce_sys
    COMMAND ${VITASDK}/bin/vita-mksfoex
            -s TITLE_ID=${VITA_TITLEID}
            -s APP_VER=${VITA_VERSION}
            "${VITA_APP_NAME}"
            ${CMAKE_BINARY_DIR}/sce_sys/param.sfo
    COMMENT "Generating param.sfo"
    VERBATIM
)

add_custom_target(zmicropg ALL DEPENDS ${VPK_OUT})

install(FILES ${VPK_OUT} DESTINATION .)
