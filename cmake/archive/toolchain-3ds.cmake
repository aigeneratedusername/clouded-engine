# cmake/toolchain-3ds.cmake
# CMake cross-compilation toolchain for Nintendo 3DS (devkitARM).
#
# Usage:
#   cmake -DPLATFORM=N3DS -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-3ds.cmake ..

if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DEVKITPRO environment variable is not set.")
endif()

set(DKP "$ENV{DEVKITPRO}")
set(DKA "${DKP}/devkitARM")

set(CMAKE_SYSTEM_NAME      Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER   "${DKA}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DKA}/bin/arm-none-eabi-g++")
set(CMAKE_AR           "${DKA}/bin/arm-none-eabi-ar" CACHE PATH "")
set(CMAKE_RANLIB       "${DKA}/bin/arm-none-eabi-ranlib" CACHE PATH "")

set(ARCH_FLAGS "-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft")

set(CMAKE_C_FLAGS_INIT   "${ARCH_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${ARCH_FLAGS}")

# Don't try to run test binaries on the host
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Sysroot / search paths
set(CMAKE_FIND_ROOT_PATH
    "${DKA}/arm-none-eabi"
    "${DKP}/libctru"
)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
