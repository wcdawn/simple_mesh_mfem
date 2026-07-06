#ifndef GEOMETRY
#define GEOMETRY

#include <array>

// NOTE: PRISM is a Wedge.
enum Geometry
{
  INVALID = -1,
  POINT,
  SEGMENT,
  TRIANGLE,
  SQUARE,
  TETRAHEDRON,
  CUBE,
  PRISM,
  NUM_GEOMETRIES
};

// Number of nodes per element for given Geometry enum.
constexpr std::array<unsigned int, Geometry::NUM_GEOMETRIES> GeometryNode{
  1, 2, 3, 4, 4, 8, 6};

// Direction for boundary conditions
enum Direction
{
  NORTH = 1,
  WEST  = 2,
  SOUTH = 3,
  EAST  = 4
};

#endif
