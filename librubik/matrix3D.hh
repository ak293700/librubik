#pragma once

#include "vector3D.hh"

namespace rubik {
template <class T> class Matrix3D {
public:
  Matrix3D(std::array<std::array<T, 3>, 3> values) { values_ = values; };

  // Could be a reference, to check
  T &at(int i, int j) { return values_[j][i]; }

  static void swap(T &i, T &j) {
    T tmp = i;
    i = j;
    j = tmp;
  }

  // matrix-vector product
  Vector3D<T> operator*(const Vector3D<T> &v) const {
    return Vector3D<T>{
        values_[0][0] * v.x + values_[0][1] * v.y + values_[0][2] * v.z,
        values_[1][0] * v.x + values_[1][1] * v.y + values_[1][2] * v.z,
        values_[2][0] * v.x + values_[2][1] * v.y + values_[2][2] * v.z};
  }

  void transpose() {
    swap(this->at(0, 1), this->at(1, 0));
    swap(this->at(0, 2), this->at(2, 0));
    swap(this->at(1, 2), this->at(2, 1));
  }

private:
  std::array<std::array<T, 3>, 3> values_;
};

} // namespace rubik
