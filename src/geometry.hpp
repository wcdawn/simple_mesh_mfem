#ifndef GEOMETRY
#define GEOMETRY

#include <array>
#include <string>
#include <unordered_map>

// NOTE: PRISM is a Wedge.
enum class Geometry
{
  INVALID = -1,
  POINT,
  SEGMENT,
  TRIANGLE,
  SQUARE,
  TETRAHEDRON,
  CUBE,
  PRISM,
};

Geometry str2enum_geometry(const std::string & s);
std::string enum2str(const Geometry geo);

// Number of nodes per element for given Geometry enum.
extern const std::unordered_map<Geometry, unsigned int> GeometryNode;

size_t CalcNElement(Geometry geo, size_t nx, size_t ny);

// Direction for boundary conditions
enum class Direction
{
  NORTH = 1,
  WEST = 2,
  SOUTH = 3,
  EAST = 4
};

#endif
