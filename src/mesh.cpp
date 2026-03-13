#include <cstddef>
#include <iostream>
#include <vector>

#ifdef DEBUG
#include <fenv.h>
#endif

#include "calc_mesh.hpp"
#include "geometry.hpp"
#include "input_proc.hpp"
#include "write_mesh.hpp"

using namespace std;

void usage(const string& exe_name)
{
  cout << "Usage:\n";
  cout << exe_name << " <file_name>" << endl;
}

int main(int argc, char** argv)
{
#ifdef DEBUG
  feenableexcept(FE_INVALID | FE_OVERFLOW | FE_DIVBYZERO);
  cout << "DEBUG" << endl;
#endif

  cout << "start MAIN" << endl;

  string fname;
  if (argc == 2)
  {
    fname = argv[1];
  }
  else
  {
    usage(argv[0]);
    return 1;
  }

  Input input; // Note: no initialization function.
  try
  {
    input.parse(fname);
  }
  catch (Input::input_exception)
  {
    cerr << "Input parsing error." << endl;
    return 1;
  }
  catch (...)
  {
    cerr << "Unknown input parsing error." << endl;
    return 2;
  }

  input.echo(cout);

  try
  {
    input.check();
  }
  catch (Input::input_exception)
  {
    cerr << "Invalid input value." << endl;
    return 1;
  }
  catch (...)
  {
    cerr << "Unknown input checking error." << endl;
    return 2;
  }

  const size_t nElement{CalcNElement(input.geo, input.nx, input.ny)};

  if (nElement == 0)
  {
    cout << "Invalid nElement." << endl;
    return 1;
  }

  vector<vector<double>> node;
  vector<vector<unsigned int>> element;
  vector<vector<unsigned int>> boundary;

  CalcMesh(input.geo, input.nx, input.ny, input.dx, input.dy, node, element,
           boundary);

  cout << "nNode = " << node.size() << endl;
  cout << "nElement = " << element.size() << endl;
  cout << "nBoundary = " << boundary.size() << endl;

  WriteMesh("generate.mesh", input.geo, input.nx, input.ny, input.material_map,
            node, element, boundary);

  cout << "end MAIN" << endl;

  return 0;
}
