#ifndef WRITE_MESH
#define WRITE_MESH

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "geometry.hpp"

void WriteMesh(const std::string & fname, const Geometry geo, const int dimension, const size_t nx, const size_t ny,
               const std::vector<std::vector<unsigned int>> & material_map,
               const std::vector<std::vector<double>> & node, const std::vector<std::vector<unsigned int>> & element,
               const std::vector<std::vector<unsigned int>> & boundary);

#endif
