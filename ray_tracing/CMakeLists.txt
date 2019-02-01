cmake_minimum_required(VERSION 3.00)

add_executable(ray_tracing src/Vector.hpp
                           src/Pixmap.h
                           src/Pixmap.cpp
                           src/Ray.h
                           src/Ray.cpp
                           src/Hitable.h
                           src/Hitable.cpp
                           src/HitableList.h
                           src/HitableList.cpp
                           src/Sphere.h
                           src/Sphere.cpp
                           src/Camera.h
                           src/Camera.cpp
                           src/Material.h
                           src/Material.cpp
                           src/Lambertian.h
                           src/Lambertian.cpp
                           src/Metal.h
                           src/Metal.cpp
                           src/Dielectric.h
                           src/Dielectric.cpp
                           src/main.cpp)

find_package(Threads REQUIRED)

target_link_libraries(ray_tracing PRIVATE stb
                                          ${CMAKE_THREAD_LIBS_INIT}
                                          ${CMAKE_DL_LIBS})

target_compile_definitions(ray_tracing PUBLIC NOMINMAX
                                               _USE_MATH_DEFINES)

set_target_properties(ray_tracing PROPERTIES CXX_STANDARD          17
                                             CXX_STANDARD_REQUIRED ON)