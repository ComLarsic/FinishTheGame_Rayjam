cmake_minimum_required(VERSION 3.22)
project(RayJam CXX)

file(GLOB SRC src/**/*.cpp src/**/*.hpp)
include_directories(./src/)
include_directories(./vendor)
add_executable(RayJam ${SRC})
target_link_libraries(RayJam PUBLIC raylib)

find_package(raylib 4.0.0 QUIET)
if (NOT raylib_FOUND) 
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) 
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

if (EMSCRIPTEN)
  message("-- Building using emscripten")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 --preload-file ../assets/")
  set(CMAKE_EXECUTABLE_SUFFIX ".html")
else ()
  message("-- Failed to detect emscripten")
endif ()