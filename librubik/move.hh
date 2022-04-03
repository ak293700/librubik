#pragma once

#include <variant>
#include <vector>

namespace rubik {
enum class Axis { X = 0, Y, Z };

enum class Direction { CLOCKWISE = 0, ANTI_CLOCKWISE };

enum class Face { UP = 0, DOWN, LEFT, RIGHT, FRONT, BACK };

class Move {
public:
  std::variant<Face, Axis> mvt{};
  Direction dir = Direction::CLOCKWISE;
  bool is_double = false;
};
} // namespace rubik
