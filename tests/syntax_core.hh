#include "../src/librubik/vector3D.hh"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <librubik/color.hh>
#include <librubik/cube.hh>
#include <librubik/piece.hh>
#include <librubik/vector3D.hh>

#include "gtest/gtest.h"

namespace rubik {
// FIXME: Uncomment each test once the corresponding step is implemented

TEST(syntax_core, color_enum) {
  auto all_colors = {Color::WHITE, Color::YELLOW, Color::GREEN, Color::BLUE,
                     Color::RED,   Color::ORANGE, Color::NONE};
  testing::internal::CaptureStdout();
  for (const auto &c : all_colors)
    std::cout << c;
  std::cout << '\n';
  std::string got = testing::internal::GetCapturedStdout();
  std::string expected = "WYGBROX\n";

  ASSERT_EQ(got, expected);
}

TEST(syntax_core, vector3D_class) {
  auto my_coords = Vector3D<int>{0, 1, -1};
  auto my_colors = Vector3D<Color>{Color::NONE, Color::RED, Color::YELLOW};

  testing::internal::CaptureStdout();
  std::cout << my_coords << ' ' << my_colors << '\n';
  std::string got = testing::internal::GetCapturedStdout();
  std::string expected = "(0,1,-1) (X,R,Y)\n";

  ASSERT_EQ(got, expected);
}

TEST(vector_test, v3D_1) {
  auto v1 = rubik::Vector3D<int>{1, 0, -1};
  auto v2 = rubik::Vector3D<int>{1, 1, -1};

  ASSERT_EQ(v1, v1);
  ASSERT_NE(v1, v2);
}

TEST(vector_test, v3D_2) {
  auto v3 = Vector3D<Color>{Color::NONE, Color::RED, Color::WHITE};
  auto v4 = Vector3D<Color>{Color::NONE, Color::ORANGE, Color::WHITE};

  ASSERT_EQ(v4, v4);
  ASSERT_NE(v3, v4);
}

/*
TEST(syntax_core, piece_class)
{
    rubik::Piece p1{ { 1, -1, 0 }, { Color::GREEN, Color::ORANGE, Color::NONE }
}; rubik::Piece p2{ { 0, 0, 1 }, { Color::NONE, Color::ORANGE, Color::NONE } };

    ASSERT_EQ(p1.get_type(), rubik::Piece::Type::EDGE);
    ASSERT_EQ(p2.get_type(), rubik::Piece::Type::CENTER);

    ASSERT_NE(p1, p2);

    //(piece != piece);
    // (piece > piece);
    // (piece <= piece);
    // (piece >= piece);
}
*/
/*
TEST(syntax_core, cube_class)
{
    Cube cube;
    std::cout << cube << '\n';

    std::ifstream file("tests/cube_state_example.txt");
    auto example_cube = Cube::from_stream(file);

    for (auto piece : cube)
        piece.get_type();
    std::sort(cube.begin(), cube.end());

    cube.find_piece({ 0, 1, 0 });
    cube.find_piece({ Color::GREEN, Color::RED, Color::WHITE });
}

*/

} // namespace rubik
