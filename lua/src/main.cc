#include <iostream>

#include "point.hh"

int main() {
  auto window = point::Window();

  point::draw::Initialize(window);
  point::draw::SetBackgroundColor(point::Color(0.2, 0.2, 0.2));

  while (!window.ShouldClose()) {
    window.Update();

    point::draw::Clear();
    point::draw::Present();
  }

  return 0;
}
