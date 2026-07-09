# NOTE: Requires the official VITASDK toolchain:

message(STATUS "Configuring PSVita target")

# App metadata
set(VITA_APP_NAME "zmicropg")
set(VITA_TITLEID  "ZMCR00001")
set(VITA_VERSION  "01.00")

target_include_directories(engine PRIVATE
    "${VITASDK}/arm-vita-eabi/include"
)

add_compile_definitions(PLATFORM_VITA)

add_executable(zmicropg src/main.cpp)
target_link_libraries(zmicropg PRIVATE engine
    SceLibc_stub
    SceKernel_stub
    SceDisplay_stub
    SceGxm_stub
    SceCtrl_stub
    SceAudio_stub
    SceRtc_stub
    SceSysmodule_stub
    m
)

vita_create_self(zmicropg.self zmicropg)

vita_create_vpk(zmicropg.vpk ${VITA_TITLEID} zmicropg.self
    VERSION ${VITA_VERSION}
    NAME    ${VITA_APP_NAME}
)
