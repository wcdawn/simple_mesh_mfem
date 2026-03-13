#include "input_proc.hpp"

#include "geometry.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

bool Input::parse(const string& fname)
{

  bool good{false};

  string card;
  string line_string;
  ifstream inp{fname};

  while (getline(inp, line_string))
  {
    if (skip_line(line_string))
    {
      continue;
    } // skip blank lines and comments
    stringstream line{line_string};
    line >> card;

    if (card == "[MESH]")
    {
      good = true;
    }
    else if (card == "dx")
    {
      for (double this_dx{0.0}; line >> this_dx; )
        dx.push_back(this_dx);
      nx = dx.size();
    }
    else if (card == "dy")
    {
      for (double this_dy{0.0}; line >> this_dy; )
        dy.push_back(this_dy);
      ny = dy.size();
    }
    else if (card == "element")
    {
      line >> card;
      if (card == "square")
      {
        geo = Geometry::SQUARE;
      }
      else if (card == "triangle")
      {
        geo = Geometry::TRIANGLE;
      }
      else
      {
        cout << "Invalid value specified on element card.\n"
                "element "
             << card << endl;
        return false;
      }
    }
    else if (card == "map")
    {
      material_map.resize(ny, vector<unsigned int>(nx));
      for (size_t jloop{0}; jloop < ny; ++jloop)
      {

        const size_t j{ny - 1 - jloop};

        // get a new line from input (make sure to allow for blank lines and
        // comments)
        getline(inp, line_string);
        if (skip_line(line_string))
        {
          continue;
        } // skip blank lines and comments
        stringstream line{line_string};

        for (size_t i{0}; i < nx; ++i)
        {
          line >> material_map[j][i];
        }
      }
    }
    else
    {
      cerr << "Unknown card specified.\n"
              "First unknown card: *"
           << card << "*" << endl;
      throw input_exception{};
    }
  }
  inp.close();
  init = true;
  return good;
} // Input::parse

void Input::echo(ostream& out) const
{
  out << "nx = " << nx << '\n';
  out << "dx =";
  for (size_t i{0}; i < nx; i++)
  {
    out << ' ' << dx[i];
  }
  out << '\n';
  out << "ny = " << ny << '\n';
  out << "dy =";
  for (size_t i{0}; i < ny; i++)
  {
    out << ' ' << dy[i];
  }
  out << '\n';
  out << "element = " << geo << '\n';
  out << "map\n";
  for (size_t jloop{0}; jloop < ny; jloop++)
  {
    const size_t j{ny - 1 - jloop};
    out << material_map[j][0];
    for (size_t i{1}; i < ny; i++)
    {
      out << ' ' << material_map[j][i];
    }
    out << '\n';
  }
} // Input::echo

bool Input::check() const
{
  if (!((geo == Geometry::SQUARE) || (geo == Geometry::TRIANGLE)))
  {
    cerr << "Invalid element type. "
            "Currently, only SQUARE and TRIANGLE are supported."
         << endl;
    throw input_exception{};
  }

  for (size_t i{0}; i < nx; i++)
  {
    if (dx[i] < 0.0)
    {
      cerr << "Negative dx value." << endl;
      throw input_exception{};
    }
  }

  for (size_t i{0}; i < ny; i++)
  {
    if (dy[i] < 0.0)
    {
      cerr << "Negative dy value." << endl;
      throw input_exception{};
    }
  }

  return true;
} // Input::check_input

bool Input::skip_line(string& line)
{
  const char comment_char = '#';

  if (line.empty())
  {
    return true;
  } // skip blank lines

  line.erase(0, line.find_first_not_of(' ')); // left adjust line
  return (line[0] == comment_char);
} // Input::skip_line
