#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "color.hh"
#include "piece.hh"

#define NUMBER_OF_SIDE 6
#define PIECE_PER_FACE 9
#define CUBE_SIZE NUMBER_OF_SIDE *PIECE_PER_FACE

namespace rubik {
class Cube {
public:
  using iterator = std::vector<Piece>::iterator;
  using const_iterator = std::vector<Piece>::const_iterator;

public:
  Cube();
  Cube(std::vector<Piece> pieces);

  static Cube from_stream(std::istream &file);

  friend std::ostream &operator<<(std::ostream &out, const Cube &cube);

  std::vector<Piece> get_pieces() const;

  Piece find_piece(Vector3D<int> coords) const;
  Piece find_piece(Vector3D<Color> colors) const;

  void do_move(Move move);

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

private:
  std::vector<Piece> pieces_;
};
} // namespace rubik
