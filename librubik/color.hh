#pragma once

#include <iostream>

#define COLOR_SIZE 7

namespace rubik {
const char colorFace[] = {'W', 'Y', 'G', 'B', 'R', 'O', 'X'};
enum class Color { WHITE = 0, YELLOW, GREEN, BLUE, RED, ORANGE, NONE };

inline Color charToColor(char c) {
  int i = 0;
  for (; i < COLOR_SIZE && colorFace[i] != c; i++)
    ;
  if (i == COLOR_SIZE)
    throw std::ios_base::failure{"Wrong Color mentioned"};
  return static_cast<Color>(i);
}

inline std::ostream &operator<<(std::ostream &out, const Color &color) {
  out << colorFace[static_cast<int>(color)];
  return out;
}
} // namespace rubik
