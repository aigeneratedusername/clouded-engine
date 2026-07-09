message(STATUS "Configuring desktop target (${PLATFORM})")

target_include_directories(engine PRIVATE 
    vendor/SDL3/include
    vendor/glad/include
)

if(PLATFORM STREQUAL "Linux")
    set(SDL3_LIB_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL3/lib/linux")
elseif(PLATFORM STREQUAL "Windows")
    set(SDL3_LIB_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL3/lib/windows")
elseif(PLATFORM STREQUAL "Mac")
    set(SDL3_LIB_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL3/lib/mac")
endif()

add_compile_definitions(PLATFORM_DESKTOP)
add_executable(${EXE_NAME}
    src/main.cpp
    ${GAME_SOURCES}
)

target_link_directories(${EXE_NAME} PRIVATE ${SDL3_LIB_DIR})
target_link_libraries(${EXE_NAME} PRIVATE engine SDL3)

install(TARGETS ${EXE_NAME} DESTINATION bin)
