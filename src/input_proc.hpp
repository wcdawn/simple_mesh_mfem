#ifndef INPUT_PROC
#define INPUT_PROC

#include <string>
#include <vector>

#include "geometry.hpp"

class Input
{
  private: // Cannot be inherited. Otherwise, use protected.

    bool init{false};
    static bool skip_line(std::string & line);

  public:

    bool parse(const std::string & fname);
    void echo(std::ostream & out) const;
    bool check() const;

    // TODO add getters
    // variables should be private to a class and use getters/setters
    size_t nx{0};
    size_t ny{0};
    std::vector<double> dx;
    std::vector<double> dy;
    Geometry geo{Geometry::SQUARE}; // default to squares
    std::vector<std::vector<unsigned int>> material_map;

    // exceptions
    class input_exception
    {
    };

}; // Input

#endif
