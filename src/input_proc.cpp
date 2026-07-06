#include "input_proc.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "geometry.hpp"

std::string get_card(std::ifstream & ifs)
{
  std::string card;
  ifs >> card;
  return card;
}

bool Input::parse(const std::string & fname)
{
  constexpr char comment_char = '#';
  bool good{false};

  std::ifstream inp{fname};

  while (inp.good())
  {
    const std::string card{get_card(inp)};
    if (card[0] == comment_char)
    {
      // eat until newline
      for (char x{'a'}; x != '\n'; inp.get(x))
      {
      }
      continue;
    }

    // skip newline
    if (card == "")
      break;

    if (card == "[MESH]")
    {
      good = true;
    }
    else if (card == "nx")
    {
      inp >> nx;
      dx.reserve(nx);
    }
    else if (card == "dx")
    {
      for (std::size_t i = 0; i < nx; ++i)
      {
        double x;
        inp >> x;
        dx.push_back(x);
      }
    }
    else if (card == "ny")
    {
      inp >> ny;
      dy.reserve(ny);
    }
    else if (card == "dy")
    {
      for (std::size_t i = 0; i < ny; ++i)
      {
        double x;
        inp >> x;
        dy.push_back(x);
      }
    }
    else if (card == "element")
    {
      const std::string element_type{get_card(inp)};
      geo = str2enum_geometry(element_type);
    }
    else if (card == "map")
    {
      // NOTE: comments are not allowed amid/among maps!
      const size_t loopmax{std::max(ny, size_t{1})};
      material.resize(nx * loopmax);
      for (size_t jloop{0}; jloop < loopmax; ++jloop)
      {
        const size_t j{ny - 1 - jloop};
        for (size_t i{0}; i < nx; ++i)
        {
          inp >> material[i + j * nx];
        }
      }
    }
    else
    {
      std::cerr << "Unknown card specified.\n"
                   "First unknown card: *"
                << card << "*" << std::endl;
      throw input_exception{};
    }
  }
  inp.close();

  switch (geo)
  {
    case (Geometry::SQUARE):
      [[fallthrough]];
    case (Geometry::TRIANGLE):
      dimension = 2;
      break;
    case (Geometry::SEGMENT):
      dimension = 1;
      break;
    default:
      std::cerr << "I don't know how to specify the dimension for your mesh." << std::endl;
      throw input_exception{};
  }

  init = true;
  return good;
} // Input::parse

void Input::echo(std::ostream & out) const
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
  out << "element = " << enum2str(geo) << " " << static_cast<int>(geo) << '\n';
  out << "map\n";
  const size_t loopmax{std::max(ny, size_t{1})};
  for (size_t jloop{0}; jloop < loopmax; jloop++)
  {
    const size_t j{ny - 1 - jloop};
    out << material[0 + j * nx];
    for (size_t i{1}; i < nx; i++)
    {
      out << ' ' << material[i + j * nx];
    }
    out << '\n';
  }
} // Input::echo

bool Input::check() const
{
  if (geo == Geometry::INVALID)
  {
    std::cerr << "Invalid element type. Unable to parse." << std::endl;
    throw input_exception{};
  }

  if ((dimension == 2) && ((geo != Geometry::SQUARE) && (geo != Geometry::TRIANGLE)))
  {
    std::cerr << "Invalid element type. "
                 "Currently, only SQUARE and TRIANGLE are supported in 2D."
              << std::endl;
    throw input_exception{};
  }
  if ((dimension == 1) && (geo != Geometry::SEGMENT))
  {
    std::cerr << "Invalid element type. "
                 "Currently, only SEGMENT is supported in 1D."
              << std::endl;
    throw input_exception{};
  }
  if ((geo == Geometry::SEGMENT) && (ny != 0))
  {
    std::cerr << "SEGMENT elements must be specified with an ny of exactly zero!\n" << std::endl;
    throw input_exception{};
  }

  for (size_t i{0}; i < nx; i++)
  {
    if (dx[i] < 0.0)
    {
      std::cerr << "Negative dx value." << std::endl;
      throw input_exception{};
    }
  }

  for (size_t i{0}; i < ny; i++)
  {
    if (dy[i] < 0.0)
    {
      std::cerr << "Negative dy value." << std::endl;
      throw input_exception{};
    }
  }

  return true;
} // Input::check_input
