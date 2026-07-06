#include "calc_mesh.hpp"

#include <iostream>
#include <vector>

#include "geometry.hpp"

void CalcMesh(const Geometry geo, const size_t nx, const size_t ny, const std::vector<double> & dx,
              const std::vector<double> & dy, std::vector<std::vector<double>> & node,
              std::vector<std::vector<unsigned int>> & element, std::vector<std::vector<unsigned int>> & boundary)
{
  // convert dx to x
  std::vector<double> x(nx + 1, 0.0);
  for (size_t i{1}; i < nx + 1; i++)
  {
    x[i] = x[i - 1] + dx[i - 1];
  }

  // convert dy to y
  std::vector<double> y(ny + 1, 0.0);
  for (size_t i{1}; i < ny + 1; i++)
  {
    y[i] = y[i - 1] + dy[i - 1];
  }

  const size_t vdim{2}; // Number of coordinates per node. Two or Three.

  node.resize((nx + 1) * (ny + 1));
  // calculate node array
  for (size_t j{0}; j < ny + 1; j++)
  {
    for (size_t i{0}; i < nx + 1; i++)
    {
      const size_t idx{j * (nx + 1) + i};
      node[idx].resize(vdim);
      node[idx][0] = x[i];
      node[idx][1] = y[j];
    }
  }

  switch (geo)
  {
    case Geometry::SQUARE:
      element = SquareElementArray(nx, ny);
      break;
    case Geometry::TRIANGLE:
      element = TriangleElementArray(nx, ny);
      break;
    case Geometry::SEGMENT:
      element = SegmentElementArray(nx, ny);
    default:
      std::cout << "Cannot create element array for specified Geometry. Mesh not "
                   "Calculated."
                << std::endl;
      return;
  }

  boundary = BoundaryArray(nx, ny);
}

std::vector<std::vector<unsigned int>> BoundaryArray(const size_t nx, const size_t ny)
{
  std::vector<std::vector<unsigned int>> boundary(2 * nx + 2 * ny, std::vector<unsigned int>(3, 0));
  for (size_t i{0}; i < nx; i++)
  {
    const size_t idx = i;

    // south
    boundary[idx][0] = static_cast<unsigned int>(Direction::SOUTH);
    boundary[idx][1] = i;
    boundary[idx][2] = i + 1;

    // north
    boundary[idx + nx][0] = static_cast<unsigned int>(Direction::NORTH);
    boundary[idx + nx][1] = (nx + 1) * ny + i;
    boundary[idx + nx][2] = (nx + 1) * ny + i + 1;
  }

  // east and west
  for (size_t i{0}; i < ny; i++)
  {
    const size_t idx = i + 2 * nx;

    // east
    boundary[idx][0] = static_cast<unsigned int>(Direction::EAST);
    boundary[idx][1] = (nx + 1) * i + nx;
    boundary[idx][2] = (nx + 1) * (i + 1) + nx;

    // west
    boundary[idx + ny][0] = static_cast<unsigned int>(Direction::WEST);
    boundary[idx + ny][1] = (nx + 1) * i;
    boundary[idx + ny][2] = (nx + 1) * (i + 1);
  }
  return boundary;

} // BoundaryArray

std::vector<std::vector<unsigned int>> SquareElementArray(const size_t nx, const size_t ny)
{
  std::vector<std::vector<unsigned int>> element(CalcNElement(Geometry::SQUARE, nx, ny),
                                                 std::vector<unsigned int>(GeometryNode.at(Geometry::SQUARE), 0));
  for (size_t j{0}; j < ny; j++)
  {
    for (size_t i{0}; i < nx; i++)
    {
      const size_t idx{j * nx + i};
      element[idx][0] = j * (nx + 1) + i;
      element[idx][1] = j * (nx + 1) + i + 1;
      element[idx][2] = (j + 1) * (nx + 1) + i + 1;
      element[idx][3] = (j + 1) * (nx + 1) + i;
    }
  }
  return element;

} // SquareElementArray

std::vector<std::vector<unsigned int>> TriangleElementArray(const size_t nx, const size_t ny)
{
  std::vector<std::vector<unsigned int>> element(CalcNElement(Geometry::TRIANGLE, nx, ny),
                                                 std::vector<unsigned int>(GeometryNode.at(Geometry::TRIANGLE), 0));
  for (size_t j{0}; j < ny; j++)
  {
    for (size_t i{0}; i < nx; i++)
    {
      const size_t idx{2 * (j * nx + i)};
      element[idx][0] = j * (nx + 1) + i;
      element[idx][1] = (j + 1) * (nx + 1) + i + 1;
      element[idx][2] = (j + 1) * (nx + 1) + i;

      element[idx + 1][0] = j * (nx + 1) + i;
      element[idx + 1][1] = j * (nx + 1) + i + 1;
      element[idx + 1][2] = (j + 1) * (nx + 1) + i + 1;
    }
  }
  return element;
} // TriangleElementArray

std::vector<std::vector<unsigned int>> SegmentElementArray(const size_t nx, const size_t)
{
  std::vector<std::vector<unsigned int>> element(CalcNElement(Geometry::SEGMENT, nx, 1),
                                                 std::vector<unsigned int>(GeometryNode.at(Geometry::SEGMENT), 0));
  for (size_t i{0}; i < nx; i++)
  {
    // TODO
  }
  return element;
} // TriangleElementArray
