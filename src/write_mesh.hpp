#ifndef WRITE_MESH
#define WRITE_MESH

#include "geometry.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void WriteMesh(const string& fname, Geometry geo, size_t nx, size_t ny,
               const vector<vector<unsigned int>>& material_map,
               const vector<vector<double>>& node,
               const vector<vector<unsigned int>>& element,
               const vector<vector<unsigned int>>& boundary);

size_t CalcNElement(Geometry geo, size_t nx, size_t ny);

#endif
