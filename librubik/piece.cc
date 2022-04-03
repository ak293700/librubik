#include "piece.hh"
#include <functional>

namespace rubik {
std::ostream &operator<<(std::ostream &out, const Piece &piece) {
  out << piece.coords << ' ' << piece.colors;
  return out;
}

bool Piece::operator==(const Piece &piece) const {
  return coords == piece.coords && colors == piece.colors;
}

bool Piece::operator!=(const Piece &piece) const { return !(*this == piece); }

bool Piece::operator<(const Piece &piece) const {
  auto c1 = coords;
  auto c2 = piece.coords;

  if (c1.x < c2.x)
    return true;

  if (c1.x == c2.x) {
    if (c1.y < c2.y)
      return true;
    if (c1.y == c2.y) {
      if (c1.z < c2.z)
        return true;
    }
  }
  return false;
}

bool Piece::operator>(const Piece &piece) const {
  return !(*this < piece) && *this != piece;
}

bool Piece::operator<=(const Piece &piece) const { return !(*this > piece); }

bool Piece::operator>=(const Piece &piece) const { return !(*this < piece); }

void Piece::do_move(Face face, Direction dir) {
  int limit = dir == Direction::CLOCKWISE ? 1 : 3;

  if (face == Face::FRONT || face == Face::BACK) {
    // Move coord
    Matrix3D<int> m = Matrix3D<int>{
        std::array<std::array<int, 3>, 3>{{{1, 0, 0}, {0, 0, -1}, {0, 1, 0}}}};

    if (face == Face::FRONT)
      m.transpose();

    for (int i = 0; i < limit; i++) {
      coords = m * coords;
      rubik::Matrix3D<Color>::swap(colors.y, colors.z);
    }
  } else if (face == Face::RIGHT || face == Face::LEFT) {
    // Move coord
    Matrix3D<int> m = Matrix3D<int>{
        std::array<std::array<int, 3>, 3>{{{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}}}};

    if (face == Face::RIGHT)
      m.transpose();

    for (int i = 0; i < limit; i++) {
      coords = m * coords;
      rubik::Matrix3D<Color>::swap(colors.x, colors.z);
    }
  } else if (face == Face::UP || face == Face::DOWN) {
    // Move coord
    Matrix3D<int> m = Matrix3D<int>{
        std::array<std::array<int, 3>, 3>{{{0, 0, 1}, {0, 1, 0}, {-1, 0, 0}}}};

    if (face == Face::UP)
      m.transpose();

    for (int i = 0; i < limit; i++) {
      coords = m * coords;
      rubik::Matrix3D<Color>::swap(colors.x, colors.y);
    }
  }
}

void Piece::do_move(Axis axis, Direction dir) {
  switch (axis) {
  case Axis::X:
    do_move(Face::RIGHT, dir);
    break;
  case Axis::Y:
    do_move(Face::UP, dir);
    break;
  case Axis::Z:
    do_move(Face::FRONT, dir);
    break;
  }
}

} // namespace rubik
