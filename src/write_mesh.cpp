#include "write_mesh.hpp"

#include "geometry.hpp"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void WriteMesh(const string& fname, const Geometry geo, const size_t nx,
               const size_t ny,
               const vector<vector<unsigned int>>& material_map,
               const vector<vector<double>>& node,
               const vector<vector<unsigned int>>& element,
               const vector<vector<unsigned int>>& boundary)
{

  const string comment_char = "#";

  const string header{
    "MFEM mesh v1.0\n"
    "\n" +
    comment_char +
    "\n"
    "# MFEM Geometry Types (see mesh/geom.hpp)\n" +
    comment_char + "\n" + comment_char + " POINT       = 0\n" + comment_char +
    " SEGMENT     = 1\n" + comment_char + " TRIANGLE    = 2\n" + comment_char +
    " SQUARE      = 3\n" + comment_char + " TETRAHEDRON = 4\n" + comment_char +
    " CUBE        = 5\n" + comment_char + " PRISM       = 6\n" + comment_char +
    "\n"};

  const size_t nNode = (nx + 1) * (ny + 1);
  const size_t vdim  = node[0].size(); // 2 or 3
  const size_t nElement{CalcNElement(geo, nx, ny)};
  if (nElement == 0)
  {
    cout << "Invalid nElement. "
         << "Likely invalid shape selected. "
         << "Currently, only SQUARE and TRIANGLE supported. "
         << "Mesh not written." << endl;
    return;
  }
  const size_t nodePerElement = GeometryNode.at(geo);
  const size_t nBoundary      = 2 * nx + 2 * ny;

  ofstream f{fname}; // initializer opens the file

  f << header;
  f << '\n';

  f << "dimension\n";
  f << "2\n"; // only SQUARE and TRIANGLE and both are 2d
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
      case Geometry::SQUARE:
        idx = i % nx;
        jdx = i / nx; // integer division
        break;
      case Geometry::TRIANGLE:
        idx = (i / 2) % nx;
        jdx = (i / 2) / nx; // integer division
        break;
      default:
        cout << "Invalid geometry type in material map evalution. "
                "Mesh not calculated"
             << endl;
        return;
    }
    f << material_map[jdx][idx] << ' ' << geo;
    for (size_t j{0}; j < nodePerElement; j++)
    {
      f << ' ' << element[i][j];
    }
    f << '\n';
  }
  f << '\n';

  // write boundary
  f << "boundary\n";
  f << nBoundary << '\n';
  for (size_t i{0}; i < nBoundary; i++)
  {
    f << boundary[i][0] << ' ' << Geometry::SEGMENT;
    for (size_t j{1}; j < 3; j++)
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

size_t CalcNElement(const Geometry geo, const size_t nx, const size_t ny)
{
  switch (geo)
  {
    case Geometry::SQUARE: return nx * ny;
    case Geometry::TRIANGLE: return 2 * nx * ny;
    default: return 0;
  }
}
