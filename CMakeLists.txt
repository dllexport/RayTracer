cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

project(RayTracer)

include_directories(3rd/stb)
include_directories(3rd/eigen)
include_directories(3rd/spdlog/include)

find_package(OPENMP REQUIRED)

add_executable(RayTracer main.cpp Ray.cpp Camera.cpp Sphere.cpp HittableList.cpp Lambertian.cpp Metal.cpp Renderer.cpp Dielectric.cpp MovingSphere.cpp)

target_link_libraries(RayTracer OpenMP::OpenMP_CXX)