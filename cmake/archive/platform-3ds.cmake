# cmake/platform-3ds.cmake
# Builds a .3dsx for the Nintendo 3DS using devkitARM + libctru.
#
# Prerequisites:
#   - devkitPro installed and $DEVKITPRO set in your environment
#   - Configure with the bundled toolchain:
#       cmake -DPLATFORM=N3DS \
#             -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-3ds.cmake \

message(STATUS "Configuring N3DS target")

if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR
        "DEVKITPRO environment variable is not set.\n"
        "Install devkitPro from https://devkitpro.org/wiki/Getting_Started "
        "and set DEVKITPRO in your environment.")
endif()

set(DKP  "$ENV{DEVKITPRO}")
set(DKA  "${DKP}/devkitARM")
set(CTRU "${DKP}/libctru")

target_include_directories(engine PRIVATE
    "${DKA}/arm-none-eabi/include"
    "${CTRU}/include"
)

set(ELF_NAME "zmicropg-3ds.elf")
set(DSX_NAME "zmicropg.3dsx")
set(ELF_OUT  "${CMAKE_BINARY_DIR}/${ELF_NAME}")
set(DSX_OUT  "${CMAKE_BINARY_DIR}/${DSX_NAME}")

set(LIBENGINE   "${CMAKE_BINARY_DIR}/libengine.a")

add_library(zmicropg_obj OBJECT src/main.cpp)
add_compile_definitions(__3DS__)

target_include_directories(zmicropg_obj PRIVATE
    "${DKA}/arm-none-eabi/include"
    "${CTRU}/include"
    src/platform
    vendor/stb
    vendor/tomlc17
)
target_link_libraries(zmicropg_obj PRIVATE engine platform)

add_custom_command(
    OUTPUT  ${ELF_OUT}
    COMMAND ${DKA}/bin/arm-none-eabi-gcc
            -specs=3dsx.specs
            -march=armv6k
            -mtune=mpcore
            -mfloat-abi=hard
            -mtp=soft
            -mword-relocations
            -g
            -o ${ELF_OUT}
            $<TARGET_OBJECTS:zmicropg_obj>
            ${LIBENGINE}
            -L${CTRU}/lib
            -L${DKA}/arm-none-eabi/lib/armv6k/fpu
            -lctru
            -lm
    DEPENDS zmicropg_obj engine
    COMMENT "Linking 3DS ELF: ${ELF_NAME}"
    VERBATIM
)

add_custom_command(
    OUTPUT  ${DSX_OUT}
    COMMAND ${DKP}/tools/bin/3dsxtool ${ELF_OUT} ${DSX_OUT}
    DEPENDS ${ELF_OUT}
    COMMENT "Packaging 3DS homebrew: ${DSX_NAME}"
    VERBATIM
)

add_custom_target(zmicropg ALL DEPENDS ${DSX_OUT})

install(FILES ${DSX_OUT} DESTINATION .)
