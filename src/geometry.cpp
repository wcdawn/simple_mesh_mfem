#include "geometry.hpp"

const std::unordered_map<Geometry, unsigned int> GeometryNode{
  {Geometry::POINT, 1},
  {Geometry::SEGMENT, 2},
  {Geometry::TRIANGLE, 3},
  {Geometry::SQUARE, 4},
  {Geometry::TETRAHEDRON, 4},
  {Geometry::CUBE, 8},
  {Geometry::PRISM, 6},
};
