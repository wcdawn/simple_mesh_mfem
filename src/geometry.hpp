#ifndef GEOMETRY
#define GEOMETRY

#include <array>
#include <unordered_map>

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
extern const std::unordered_map<Geometry, unsigned int> GeometryNode;

// Direction for boundary conditions
enum class Direction
{
  NORTH = 1,
  WEST = 2,
  SOUTH = 3,
  EAST = 4
};

#endif
