cmake_minimum_required(VERSION 3.14)
project(simple_mesh_mfem VERSION 0.1.0 DESCRIPTION "A simple mesh utility to create MFEM meshes." LANGUAGES CXX)

add_executable(mesh.x)

target_sources(mesh.x
  PRIVATE
    src/calc_mesh.cpp
    src/geometry.cpp
    src/input_proc.cpp
    src/main.cpp
    src/write_mesh.cpp
)

set_property(TARGET mesh.x PROPERTY CXX_STANDARD 23)

target_compile_options(mesh.x PRIVATE -Wall -Wextra -O3)
