#ifndef CALC_MESH
#define CALC_MESH

#include "geometry.hpp"

#include <array>
#include <iostream>
#include <vector>

using namespace std;

void CalcMesh(Geometry geo, size_t nx, size_t ny, const vector<double>& dx,
              const vector<double>& dy, vector<vector<double>>& node,
              vector<vector<unsigned int>>& element,
              vector<vector<unsigned int>>& boundary);

vector<vector<unsigned int>> BoundaryArray(size_t nx, size_t ny);

vector<vector<unsigned int>> SquareElementArray(size_t nx, size_t ny);

vector<vector<unsigned int>> TriangleElementArray(size_t nx, size_t ny);

#endif
