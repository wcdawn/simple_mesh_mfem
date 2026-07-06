#ifndef CALC_MESH
#define CALC_MESH

#include <array>
#include <iostream>
#include <vector>

#include "geometry.hpp"

void CalcMesh(Geometry geo, size_t nx, size_t ny, const std::vector<double> & dx, const std::vector<double> & dy,
              std::vector<std::vector<double>> & node, std::vector<std::vector<int>> & element,
              std::vector<std::vector<int>> & boundary);

std::vector<std::vector<int>> BoundaryArray(size_t nx, size_t ny);
std::vector<std::vector<int>> SegmentBoundaryArray(size_t nx, size_t ny);

std::vector<std::vector<int>> SquareElementArray(size_t nx, size_t ny);
std::vector<std::vector<int>> TriangleElementArray(size_t nx, size_t ny);
std::vector<std::vector<int>> SegmentElementArray(size_t nx, size_t ny);

#endif
