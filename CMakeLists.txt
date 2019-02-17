cmake_minimum_required(VERSION 3.2)
project(starnet)

enable_testing()

set(CMAKE_CXX_STANDARD 11)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++11")
endif()

file(GLOB PROJECT_HEADERS *.h starnet/*.h) 
file(GLOB PROJECT_SOURCES *.cpp)

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

add_subdirectory(Samples/BaseUDPChat)
add_subdirectory(Samples/BaseTCPChat)