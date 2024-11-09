cmake_minimum_required(VERSION 3.30.0)

project(sandbox)

add_executable(${PROJECT_NAME} main.cpp)
find_package(OpenGL REQUIRED)
add_subdirectory(ext/GLFW)

target_include_directories(${PROJECT_NAME} PUBLIC ext/GLFW/include)
target_link_directories(${PROJECT_NAME} PRIVATE ext/GLFW/src)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL)

