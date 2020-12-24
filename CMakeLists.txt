cmake_minimum_required(VERSION 3.0.0)
project(Morse_cpp VERSION 0.1.0)

FILE(GLOB mainSources *.cpp)
FILE(GLOB srcSources src/*.cpp)

add_executable(morse  
${mainSources}
${srcSources}
)

target_include_directories(morse PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
        )

set(CPACK_PROJECT_NAME ${Morse_cpp})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(morse)