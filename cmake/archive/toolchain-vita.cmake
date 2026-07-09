# cmake/toolchain-vita.cmake
# CMake cross-compilation toolchain for PS Vita (VITASDK).
#
# Usage:
#   cmake -DPLATFORM=PSVita -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-vita.cmake ..
#
# Prerequisites — install VITASDK:
#   https://vitasdk.org/
#
#   Quick install (Linux / macOS / WSL):
#     git clone https://github.com/vitasdk/vdpm
#     cd vdpm && ./bootstrap-vitasdk.sh
#
#   Then add to your shell profile:
#     export VITASDK=/usr/local/vitasdk          # or wherever vdpm installed it
#     export PATH=$VITASDK/bin:$PATH
#
#   Windows: use the pre-built installer at https://vitasdk.org/#installation
#            and make sure VITASDK is set in your system environment variables.

if(NOT DEFINED ENV{VITASDK})
    message(FATAL_ERROR
        "VITASDK environment variable is not set.\n"
        "Install the Vita SDK from https://vitasdk.org/ "
        "and set VITASDK=/path/to/vitasdk in your environment.")
endif()

set(VITASDK "$ENV{VITASDK}")

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   "${VITASDK}/bin/arm-vita-eabi-gcc")
set(CMAKE_CXX_COMPILER "${VITASDK}/bin/arm-vita-eabi-g++")
set(CMAKE_AR           "${VITASDK}/bin/arm-vita-eabi-ar"     CACHE PATH "")
set(CMAKE_RANLIB       "${VITASDK}/bin/arm-vita-eabi-ranlib" CACHE PATH "")

# The Vita is ARMv7-A Cortex-A9 with NEON, hard-float ABI
set(VITA_ARCH_FLAGS "-march=armv7-a -mfpu=neon -mfloat-abi=hard")

set(CMAKE_C_FLAGS_INIT   "${VITA_ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${VITA_ARCH_FLAGS}")

# Don't try to run test binaries on the host
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_FIND_ROOT_PATH
    "${VITASDK}/arm-vita-eabi"
    "${VITASDK}"
)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
