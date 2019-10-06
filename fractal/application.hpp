#pragma once
#include <cstdint>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include <complex.hpp>
#include <vector2.hpp>

class application {
 public:
  application() { resize(); }
  application(int w, int h, const std::string& draw_str = {});
  ~application() = default;

  void execute();

 private:
  void resize();
  void resize(int w, int h);
  void compute_viewport();
  void draw_mandelbrot();
  void draw_circle();
  void draw_julia();

 private:
  int screen_width = 500;
  int screen_height = 500;
  using draw_function_type = void (application::*)();
  draw_function_type draw_function = &application::draw_mandelbrot;

  // viewport
  me::vector2f origin{};
  me::vector2f view_dim =
      2.0f * me::vector2f{1, static_cast<float>(screen_width) / screen_height};
  me::vector2f view_min;
  me::vector2f view_max;

  // rendering
  std::vector<uint8_t> pixels;
  sf::RenderWindow window{sf::VideoMode(screen_width, screen_height),
                          "Fractal Render"};
  sf::Texture texture{};
  sf::Sprite sprite{};
  bool update = true;

  // parameters
  me::complex a{1, 0};
};