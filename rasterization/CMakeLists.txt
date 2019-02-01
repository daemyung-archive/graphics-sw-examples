cmake_minimum_required(VERSION 3.00)

add_executable(rasterization src/vertex.h
                             src/triangle.h
                             src/box.h
                             src/framebuffer.h
                             src/triangle.cpp
                             src/box.cpp
                             src/framebuffer.cpp
                             src/main.cpp)

target_link_libraries(rasterization PRIVATE stb
                                            glm)

set_target_properties(rasterization PROPERTIES CXX_STANDARD          17
                                               CXX_STANDARD_REQUIRED ON)