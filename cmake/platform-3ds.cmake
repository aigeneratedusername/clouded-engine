#NOTE: Requires the official devkitPro toolchain:
message(STATUS "Configuring N3DS target")

target_include_directories(engine PRIVATE "${CTR_ROOT}/include")

add_compile_definitions(PLATFORM_3DS)
add_executable(zmicropg src/main.cpp)
target_link_libraries(zmicropg PRIVATE engine ctru m)

ctr_generate_smdh(zmicropg.smdh
    NAME        "zmicropg"
    DESCRIPTION "zmicropg"
    AUTHOR      "jaeyappalot"
)

ctr_create_3dsx(zmicropg
    SMDH zmicropg.smdh
)
