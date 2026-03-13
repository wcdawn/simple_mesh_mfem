# Simple Mesh Generator for MFEM

This program will generate a simple two-dimensional rectilinear mesh in the MFEM v1.0 [format](https://mfem.org/mesh-format-v1.0/#mfem-mesh-v10).
Originally, this was a practice for me to learn C++. 

See the `examples` directory for example input files for this program. The basic usage would be
```
$ ./mesh bwr.inp
```
Note that for now, the output file is always called `generate.mesh` so you'll need to be careful about overwriting existing files.

Although the mesh is rectilinear, the mesh can be generated using quadrilateral elements or two right-triangular elements per rectilinear spacial discretization.

## Boundary Conditions

For now, the boundary attributes are hard-wired. You can see `include/geometry.hpp` to change them yourself.
```cpp
enum Direction
{
  NORTH = 1,
  WEST  = 2,
  SOUTH = 3,
  EAST  = 4
};
```
