cmake_minimum_required(VERSION 3.20)
project(arcanoid22)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)
add_executable(arcanoid22
        arcanoid22.cpp
        ball.cpp
        ball.h
        bonus.cpp
        bonus.h
        brick.cpp
        brick.h
        entity.cpp
        entity.h
        game.cpp
        game.h
        paddle.cpp
        paddle.h
        vector_extra_func.cpp
        vector_extra_func.h)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:\\Users\\ASUS\\Downloads\\SFML-2.6.0-windows-vc16-64-bit\\SFML-2.6.0\\lib\\cmake\\SFML")

target_link_libraries(arcanoid22 sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)