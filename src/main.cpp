#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "calc_mesh.hpp"
#include "geometry.hpp"
#include "input_proc.hpp"
#include "write_mesh.hpp"

void usage(const std::string & exe_name)
{
  std::cout << "Usage:\n";
  std::cout << exe_name << " <file_name>" << std::endl;
}

std::string get_stub(const std::string & fname)
{
  const auto last{fname.find_last_of('.')};
  return fname.substr(0, last); // does not include period
}

int main(int argc, char ** argv)
{
  std::cout << "start MAIN" << std::endl;

  std::string fname;
  if (argc == 2)
  {
    fname = argv[1];
  }
  else
  {
    usage(argv[0]);
    return 1;
  }

  const std::string fname_stub{get_stub(fname)};
  const std::string fname_mesh{fname_stub + ".mesh"};

  Input input; // Note: no initialization function.
  try
  {
    input.parse(fname);
  }
  catch (Input::input_exception)
  {
    std::cerr << "Input parsing error." << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown input parsing error." << std::endl;
    return 2;
  }

  input.echo(std::cout);

  try
  {
    input.check();
  }
  catch (Input::input_exception)
  {
    std::cerr << "Invalid input value." << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown input checking error." << std::endl;
    return 2;
  }

  const size_t nElement{CalcNElement(input.geo, input.nx, input.ny)};

  if (nElement == 0)
  {
    std::cout << "Invalid nElement." << std::endl;
    return 1;
  }

  std::vector<std::vector<double>> node;
  std::vector<std::vector<int>> element;
  std::vector<std::vector<int>> boundary;

  CalcMesh(input.geo, input.nx, input.ny, input.dx, input.dy, node, element, boundary);

  std::cout << "nNode = " << node.size() << std::endl;
  std::cout << "nElement = " << element.size() << std::endl;
  std::cout << "nBoundary = " << boundary.size() << std::endl;

  WriteMesh(fname_mesh, input.geo, input.dimension, input.nx, input.ny, input.material, node, element, boundary);

  std::cout << "end MAIN" << std::endl;

  return 0;
}
