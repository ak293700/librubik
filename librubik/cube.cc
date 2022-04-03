#include "cube.hh"

namespace rubik {
Cube::Cube() : pieces_{std::vector<Piece>{}} {
  const Color colorXAxis[3] = {Color::BLUE, Color::NONE, Color::GREEN};
  const Color colorYAxis[3] = {Color::ORANGE, Color::NONE, Color::RED};
  const Color colorZAxis[3] = {Color::YELLOW, Color::NONE, Color::WHITE};

  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      for (int z = -1; z <= 1; z++) {

        pieces_.push_back(
            {{x, y, z},
             {colorXAxis[1 + x], colorYAxis[1 + y], colorZAxis[1 + z]}});
      }
    }
  }
}

Cube::Cube(std::vector<Piece> pieces) : pieces_{pieces} {}

std::vector<Piece> rubik::Cube::get_pieces() const { return pieces_; }

Piece Cube::find_piece(Vector3D<int> coords) const {
  for (auto piece : pieces_) {
    if (piece.coords == coords)
      return piece;
  }
  throw std::invalid_argument{"Piece with coord (" + std::to_string(coords.x) +
                              "," + std::to_string(coords.y) + "," +
                              std::to_string(coords.z) + ")" +
                              " does not exist "};
}

Piece Cube::find_piece(Vector3D<Color> colors) const {
  int coordsColor[COLOR_SIZE] = {
      0}; // Build a tab where store the color of colors
  coordsColor[static_cast<int>(colors.x)]++;
  coordsColor[static_cast<int>(colors.y)]++;
  coordsColor[static_cast<int>(colors.z)]++;

  for (Piece piece : pieces_) {
    const Vector3D<Color> piece_color = piece.colors;
    int x = static_cast<int>(piece_color.x);
    int y = static_cast<int>(piece_color.y);
    int z = static_cast<int>(piece_color.z);

    int pieceColor[COLOR_SIZE] = {
        0}; // Build a tab where store the color of colors
    pieceColor[x]++;
    pieceColor[y]++;
    pieceColor[z]++;

    // Just have to check if at the right coordinates it is set
    if (coordsColor[x] == pieceColor[x] && coordsColor[y] == pieceColor[y] &&
        coordsColor[z] == pieceColor[z])
      return piece;
  }
  throw std::invalid_argument{"Piece with colors 'colors' does not exist "};
}

std::ostream &operator<<(std::ostream &out, const Cube &cube) {
  auto pieces = cube.get_pieces();
  for (const Piece &piece : pieces)
    out << piece << '\n';
  return out;
}

Cube::iterator Cube::begin() { return pieces_.begin(); }

Cube::iterator Cube::end() { return pieces_.end(); }

Cube::const_iterator Cube::begin() const {
  return rubik::Cube::const_iterator();
}

Cube Cube::from_stream(std::istream &file) {
  std::vector<Piece> pieces{}; // = pieces_

  std::string line;
  while (std::getline(file, line)) {
    std::stringstream ss(line);

    Piece piece{};

    for (int i = 0; ss.good(); i++) {
      std::string substr;
      getline(ss, substr, ' ');

      if (i == 0)
        piece.coords = Vector3D<int>::toVector3DInt(substr);
      else if (i == 1)
        piece.colors = Vector3D<Color>::toVector3DColor(substr);
      else
        throw std::ios_base::failure{"Wrong formats"};
    }

    pieces.push_back(piece);
  }

  return Cube{pieces};
}

void Cube::do_move(Move move) {
  if (auto face(std::get_if<Face>(&move.mvt)); face) {
    for (Piece &piece : pieces_) {
      switch (*face) {
      case Face::FRONT:
        if (piece.coords.x == 1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      case Face::BACK:
        if (piece.coords.x == -1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      case Face::RIGHT:
        if (piece.coords.y == 1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      case Face::LEFT:
        if (piece.coords.y == -1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      case Face::UP:
        if (piece.coords.z == 1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      case Face::DOWN:
        if (piece.coords.z == -1) {
          piece.do_move(*face, move.dir);
          if (move.is_double)
            piece.do_move(*face, move.dir);
        }
        break;
      }
    }
  } else if (auto axis(std::get_if<Axis>(&move.mvt)); axis) {
    for (Piece &piece : pieces_) {
      piece.do_move(*axis, move.dir);
      if (move.is_double)
        piece.do_move(*axis, move.dir);
    }
  }
}

} // namespace rubik
