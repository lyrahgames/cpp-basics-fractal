#include <iostream>
#include <string>

#include <application.hpp>

using namespace std;

int main(int argc, char** argv) {
  if (2 < argc) {
    cout << "usage: " << argv[0] << " [<draw string>]\n";
    return -1;
  }

  // Get optional draw string for application.
  string draw_str{};
  if (argc == 2) draw_str = argv[1];

  // Use RAII principle for application.
  // Construct, initialize, execute and automatically destroy.
  application app{800, 450, draw_str};
  app.execute();
}