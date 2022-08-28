cmake_minimum_required(VERSION 3.22)
project(PixelSim)

set(CMAKE_CXX_STANDARD 14)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(src ${dir}/src)

add_executable(PixelSim src/main.cpp
        src/noise/SimplexNoise.hpp
        src/noise/SimplexNoise.cpp src/App.cpp src/App.hpp src/Game.cpp src/Game.hpp src/Scene.cpp src/Scene.hpp)

include_directories(headers /usr/include c:/SFML/include)
#include_directories(box2d C:/Users/Martin/Downloads/box2d-master/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(PixelSim ${SFML_LIBRARIES})
endif ()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    # file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    # file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif ()