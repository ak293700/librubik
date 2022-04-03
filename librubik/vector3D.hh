#pragma once

#include "color.hh"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace rubik {
template <class T> class Vector3D {
public:
  T x;
  T y;
  T z;

  static Vector3D<int> toVector3DInt(std::string str) {
    Vector3D<int> res{};

    str = str.substr(1, str.size() - 1); // take parenthesis off
    std::stringstream str_stream(str);   // streamify str

    for (int i = 0; str_stream.good(); i++) {
      std::string substr;
      getline(str_stream, substr, ',');

      if (i == 0)
        res.x = std::stoi(substr);
      else if (i == 1)
        res.y = std::stoi(substr);
      else if (i == 2)
        res.z = std::stoi(substr);
      else
        throw std::ios_base::failure{"Wrong color format"};
    }

    return res;
  }

  static Vector3D<Color> toVector3DColor(std::string str) {
    Vector3D<Color> res{};

    str = str.substr(1, str.size() - 1); // take parenthesis off
    std::stringstream str_stream(str);   // streamify str

    for (int i = 0; str_stream.good(); i++) {
      std::string substr;
      getline(str_stream, substr, ',');

      if (i == 0)
        res.x = rubik::charToColor(substr[0]);
      else if (i == 1)
        res.y = rubik::charToColor(substr[0]);
      else if (i == 2)
        res.z = rubik::charToColor(substr[0]);
      else
        throw std::ios_base::failure{"Wrong color format"};
    }

    return res;
  }

  friend std::ostream &operator<<(std::ostream &out, const Vector3D<T> &t) {
    out << '(' << t.x << ',' << t.y << ',' << t.z << ')';
    return out;
  }

  inline bool operator==(const Vector3D<T> &vect) const {
    return x == vect.x && y == vect.y && z == vect.z;
  }

  inline bool operator!=(const Vector3D<T> &vect) const {
    return !(*this == vect);
  }
};

} // namespace rubik
