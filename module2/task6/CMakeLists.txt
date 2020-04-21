cmake_minimum_required(VERSION 3.15)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra")

project(contest2_task6)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
find_package(Catch2 REQUIRED)

add_executable(tests tests.cpp)
target_link_libraries(tests Catch2::Catch2)

install(
        TARGETS tests
        RUNTIME DESTINATION bin
)