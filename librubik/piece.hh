#pragma once

#include "color.hh"
#include "matrix3D.hh"
#include "move.hh"
#include "vector3D.hh"
#include <array>

namespace rubik {

class Piece {
public:
  enum Type {
    CORNER,
    EDGE,
    CENTER

  };

  Vector3D<int> coords;
  Vector3D<Color> colors;

  Type get_type() {
    int cpt = static_cast<bool>(colors.x == Color::NONE) +
              static_cast<bool>(colors.y == Color::NONE) +
              static_cast<bool>(colors.z == Color::NONE);

    if (cpt == 0)
      return CORNER;
    if (cpt == 1)
      return EDGE;
    return CENTER;
  }

  void do_move(Face face, Direction dir);
  void do_move(Axis axis, Direction dir);

  // Display does not work
  friend std::ostream &operator<<(std::ostream &out, const Piece &piece);
  bool operator==(const Piece &piece) const;
  bool operator!=(const Piece &piece) const;
  bool operator<(const Piece &piece) const;
  bool operator>(const Piece &piece) const;
  bool operator<=(const Piece &piece) const;
  bool operator>=(const Piece &piece) const;
};

} // namespace rubik
