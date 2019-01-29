cmake_minimum_required(VERSION 3.11)

add_executable(interpolation src/types.h
                             src/image.h
                             src/sampler.h
                             src/image.cpp
                             src/sampler.cpp
                             src/main.cpp)

target_link_libraries(interpolation PRIVATE stb
                                            glm)

set_target_properties(interpolation PROPERTIES CXX_STANDARD          17
                                               CXX_STANDARD_REQUIRED ON)