// FIXME: You can include various files from the librubik library
#include "librubik/matrix3D.hh"
#include <array>
#include <librubik/cube.hh>
// #include "librubik/cube.hh"

int main() {
  // FIXME: This is where you should play around with librubik.
  // Do not forget to use the 'rubik' namespace prefix (rubik::Cube,
  // rubik::Move, ...)

  rubik::Cube cube{};
  cube.do_move({std::variant<rubik::Face, rubik::Axis>({rubik::Face::FRONT})});
  cube.do_move({std::variant<rubik::Face, rubik::Axis>({rubik::Face::RIGHT})});

  std::sort(cube.begin(), cube.end());
  std::cout << cube;

  return 0;
}
