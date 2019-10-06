#include <application.hpp>

#include <omp.h>
#include <cmath>
#include <stdexcept>

application::application(int w, int h, const std::string& draw_str)
    : screen_width{w}, screen_height{h} {
  if (draw_str == "") {
  } else if (draw_str == "mandelbrot")
    draw_function = &application::draw_mandelbrot;
  else if (draw_str == "circle")
    draw_function = &application::draw_circle;
  else if (draw_str == "julia")
    draw_function = &application::draw_julia;
  else {
    throw std::runtime_error("Given draw string could not be read!");
  }

  resize();
}

void application::resize() {
  pixels.resize(4 * screen_width * screen_height);
  window.setView(sf::View{sf::FloatRect{0, 0, static_cast<float>(screen_width),
                                        static_cast<float>(screen_height)}});
  texture.create(screen_width, screen_height);
  sprite.setTexture(texture, true);
}

void application::resize(int w, int h) {
  screen_width = w;
  screen_height = h;
  resize();
}

void application::compute_viewport() {
  view_dim.x = view_dim.y * screen_width / screen_height;
  view_min = origin - 0.5f * view_dim;
  view_max = origin + 0.5f * view_dim;
}

void application::draw_mandelbrot() {
  using namespace std;
  const int max_it = 200;
  int it_max = 0;
  int it_min = max_it;
#pragma omp parallel for schedule(dynamic)
  for (int j = 0; j < screen_height; ++j) {
    for (int i = 0; i < screen_width; ++i) {
      const int index = 4 * (screen_width * j + i);
      const int red = index + 0;
      const int green = index + 1;
      const int blue = index + 2;
      const int alpha = index + 3;

      using me::complex;
      const complex c{view_dim.x * i / screen_width + view_min.x,
                      view_dim.y * j / screen_height + view_min.y};
      complex z{};
      int it = 0;
      for (; (squared_norm(z) < 4) && (it < max_it); ++it) {
        z = a * z * z + c;
      }

      it_max = max(it_max, it);
      it_min = min(it_min, it);

      pixels[red] = pixels[green] = pixels[blue] = it;
      pixels[alpha] = 255;
    }
  }

#pragma omp parallel for
  for (int j = 0; j < screen_height; ++j) {
    for (int i = 0; i < screen_width; ++i) {
      const int index = 4 * (screen_width * j + i);
      const int red = index + 0;
      const int green = index + 1;
      const int blue = index + 2;
      const float scale =
          pow(static_cast<float>(pixels[red] - it_min) / (it_max - it_min),
              100.7f / max_it);
      pixels[red] = pixels[green] = pixels[blue] = 255.0f * scale;
    }
  }
}

void application::draw_circle() {
  using namespace std;

  for (int j = 0; j < screen_height; ++j) {
    for (int i = 0; i < screen_width; ++i) {
      const int index = 4 * (screen_width * j + i);
      const int red = index + 0;
      const int green = index + 1;
      const int blue = index + 2;
      const int alpha = index + 3;

      using me::complex;
      const complex c{view_dim.x * i / screen_width + view_min.x,
                      view_dim.y * j / screen_height + view_min.y};
      if (squared_norm(c) <= 1) {
        pixels[red] = pixels[green] = pixels[blue] = 255;
      } else {
        pixels[red] = pixels[green] = pixels[blue] = 0;
      }
      pixels[alpha] = 255;
    }
  }
}

void application::draw_julia() {
  using namespace std;
  const int max_it = 200;
  int it_max = 0;
  int it_min = max_it;
#pragma omp parallel for schedule(dynamic)
  for (int j = 0; j < screen_height; ++j) {
    for (int i = 0; i < screen_width; ++i) {
      const int index = 4 * (screen_width * j + i);
      const int red = index + 0;
      const int green = index + 1;
      const int blue = index + 2;
      const int alpha = index + 3;

      using me::complex;
      const complex c = a;
      complex z{view_dim.x * i / screen_width + view_min.x,
                view_dim.y * j / screen_height + view_min.y};
      int it = 0;
      for (; (squared_norm(z) < 4) && (it < max_it); ++it) {
        z = z * z + c;
      }

      it_max = max(it_max, it);
      it_min = min(it_min, it);

      pixels[red] = pixels[green] = pixels[blue] = it;
      pixels[alpha] = 255;
    }
  }

#pragma omp parallel for
  for (int j = 0; j < screen_height; ++j) {
    for (int i = 0; i < screen_width; ++i) {
      const int index = 4 * (screen_width * j + i);
      const int red = index + 0;
      const int green = index + 1;
      const int blue = index + 2;
      const float scale =
          pow(static_cast<float>(pixels[red] - it_min) / (it_max - it_min),
              100.7f / max_it);
      pixels[red] = pixels[green] = pixels[blue] = 255.0f * scale;
    }
  }
}