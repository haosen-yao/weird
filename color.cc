#include "color.hpp"
#include <stdexcept>
Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  const int kOne = 255;
  if (r < 0 || r > kOne || g < 0 || g > kOne || b < 0 || b > kOne) {
    throw std::runtime_error("not work");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}