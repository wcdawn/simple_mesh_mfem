#ifndef INPUT_PROC
#define INPUT_PROC

#include "geometry.hpp"

#include <string>
#include <vector>

using namespace std;

class Input
{

private: // Cannot be inherited. Otherwise, use protected.
  bool init{false};
  static bool skip_line(string& line);

public:
  bool parse(const string& fname);
  void echo(ostream& out) const;
  bool check() const;

  // TODO add getters
  // variables should be private to a class and use getters/setters
  size_t nx{0};
  size_t ny{0};
  vector<double> dx;
  vector<double> dy;
  Geometry geo{Geometry::SQUARE}; // default to squares
  vector<vector<unsigned int>> material_map;

  // exceptions
  class input_exception {};

}; // Input

#endif
