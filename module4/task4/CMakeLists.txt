cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

project(contest4_task4)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(contest4_task4 src/task4.cpp include/task4.h main.cpp)

find_package(Catch2 REQUIRED)

add_executable(tests tests.cpp src/task4.cpp)
target_link_libraries(tests Catch2::Catch2)

install(
        TARGETS tests contest4_task4
        RUNTIME DESTINATION bin
)