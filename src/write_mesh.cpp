#include "write_mesh.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "geometry.hpp"

// TODO actually handle the output format (e.g., scientific notation)

void WriteMesh(const std::string & fname, const Geometry geo, const int dimension, const size_t nx, const size_t ny,
               const std::vector<unsigned int> & material_map, const std::vector<std::vector<double>> & node,
               const std::vector<std::vector<unsigned int>> & element,
               const std::vector<std::vector<unsigned int>> & boundary)
{
  const std::string comment_char = "#";

  const std::string header{std::string{"MFEM mesh v1.0\n"} + "\n" + comment_char + "\n" + comment_char
                           + " MFEM Geometry Types (see mesh/geom.hpp)\n" + comment_char + "\n" + comment_char
                           + " POINT       = 0\n" + comment_char + " SEGMENT     = 1\n" + comment_char
                           + " TRIANGLE    = 2\n" + comment_char + " SQUARE      = 3\n" + comment_char
                           + " TETRAHEDRON = 4\n" + comment_char + " CUBE        = 5\n" + comment_char
                           + " PRISM       = 6\n" + comment_char + "\n"};

  const auto nNode = (nx + 1) * (ny + 1);
  const auto vdim = node[0].size(); // 2 or 3
  const auto nElement{CalcNElement(geo, nx, ny)};
  if (nElement == 0)
  {
    std::cout << "Invalid nElement. "
              << "Likely invalid shape selected. "
              << "Currently, only SQUARE and TRIANGLE supported. "
              << "Mesh not written." << std::endl;
    return;
  }
  const auto nodePerElement = GeometryNode.at(geo);
  const auto nBoundary = boundary.size();

  std::ofstream f{fname}; // initializer opens the file

  f << header;
  f << '\n';

  f << "dimension\n";
  f << dimension << "\n";
  f << '\n';

  // write element
  f << "elements\n";
  f << nElement << '\n';
  for (size_t i{0}; i < nElement; i++)
  {
    size_t idx{0};
    size_t jdx{0};
    switch (geo)
    {
      case (Geometry::SQUARE):
        idx = i % nx;
        jdx = i / nx; // integer division
        break;
      case (Geometry::TRIANGLE):
        idx = (i / 2) % nx;
        jdx = (i / 2) / nx; // integer division
        break;
      case (Geometry::SEGMENT):
        idx = i;
        jdx = 0;
        break;
      default:
        std::cout << "Invalid geometry type in material map evalution. "
                     "Mesh not written."
                  << std::endl;
        return;
    }
    f << material_map[idx + jdx * nx] << ' ' << static_cast<int>(geo);
    for (size_t j{0}; j < nodePerElement; j++)
    {
      f << ' ' << element[i][j];
    }
    f << '\n';
  }
  f << '\n';

  Geometry boundary_type;
  switch (geo)
  {
    case (Geometry::SQUARE):
      [[fallthrough]];
    case (Geometry::TRIANGLE):
      boundary_type = Geometry::SEGMENT;
      break;
    case (Geometry::SEGMENT):
      boundary_type = Geometry::POINT;
      break;
    default:
      std::cout << "Unable to identify the type of the boundary element!"
                << " Mesh not written." << std::endl;
      return;
  }

  // write boundary
  f << "boundary\n";
  f << nBoundary << '\n';
  for (size_t i{0}; i < nBoundary; i++)
  {
    f << boundary[i][0] << ' ' << static_cast<int>(boundary_type);
    for (size_t j{1}; j < boundary[i].size(); j++)
    {
      f << ' ' << boundary[i][j];
    }
    f << '\n';
  }
  f << '\n';

  // write node
  f << "vertices\n";
  f << nNode << '\n';
  f << vdim << '\n';
  for (size_t i{0}; i < nNode; i++)
  {
    f << node[i][0];
    for (size_t j{1}; j < vdim; j++)
    {
      f << ' ' << node[i][j];
    }
    f << '\n';
  }

  f.close();
}
