cmake_minimum_required(VERSION 3.2)
project(starnet)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

file(GLOB PROJECT_HEADERS *.h starnet/*.h) 
file(GLOB PROJECT_SOURCES *.cpp)

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

add_subdirectory(Samples/BaseUDPChat)
add_subdirectory(Samples/BaseTCPChat)
add_subdirectory(Samples/MemoryStreams)