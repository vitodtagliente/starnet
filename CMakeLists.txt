cmake_minimum_required(VERSION 3.2)
project(starnet)

enable_testing()

set(CMAKE_CXX_STANDARD 17)

file(GLOB PROJECT_HEADERS *.h starnet/*.h) 
file(GLOB PROJECT_SOURCES *.cpp src/*.cpp)

add_library(
    ${PROJECT_NAME} 
	STATIC
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES} 
)

add_subdirectory(Samples/EchoServer)
add_subdirectory(Samples/BaseUDPChat)
add_subdirectory(Samples/BaseTCPChat)
add_subdirectory(Samples/MemoryStreams)