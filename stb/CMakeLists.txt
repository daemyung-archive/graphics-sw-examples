cmake_minimum_required(VERSION 3.00)

add_library(stb INTERFACE)

target_include_directories(stb INTERFACE include)

target_compile_definitions(stb INTERFACE STB_IMAGE_WRITE_IMPLEMENTATION
                                         _CRT_SECURE_NO_WARNINGS)