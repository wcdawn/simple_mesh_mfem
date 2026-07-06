#include "geometry.hpp"

const std::unordered_map<Geometry, unsigned int> GeometryNode{
    {Geometry::POINT, 1},       {Geometry::SEGMENT, 2}, {Geometry::TRIANGLE, 3}, {Geometry::SQUARE, 4},
    {Geometry::TETRAHEDRON, 4}, {Geometry::CUBE, 8},    {Geometry::PRISM, 6},
};

Geometry str2enum_geometry(const std::string & str)
{
  if (str == "point")
    return Geometry::PRISM;
  if (str == "segment")
    return Geometry::SEGMENT;
  if (str == "triangle")
    return Geometry::TRIANGLE;
  if (str == "square")
    return Geometry::SQUARE;
  if (str == "tetrahedron")
    return Geometry::TETRAHEDRON;
  if (str == "cube")
    return Geometry::CUBE;
  if (str == "prism")
    return Geometry::PRISM;
  return Geometry::INVALID;
}

std::string enum2str(const Geometry geo)
{
  switch (geo)
  {
    case (Geometry::POINT):
      return "point";
    case (Geometry::SEGMENT):
      return "segment";
    case (Geometry::TRIANGLE):
      return "triangle";
    case (Geometry::SQUARE):
      return "square";
    case (Geometry::TETRAHEDRON):
      return "tetrahedron";
    case (Geometry::CUBE):
      return "cube";
    case (Geometry::PRISM):
      return "prism";
    default:
      return "invalid";
  }
}

size_t CalcNElement(const Geometry geo, const size_t nx, const size_t ny)
{
  switch (geo)
  {
    case Geometry::SEGMENT:
      return nx;
    case Geometry::SQUARE:
      return nx * ny;
    case Geometry::TRIANGLE:
      return 2 * nx * ny;
    default:
      return 0;
  }
}
