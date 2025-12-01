#include <fstream>
#include "parse_file.h"

void parse_file_lines(std::string path, std::vector<std::string> &input) {
  std::string s;
  std::ifstream f(path, std::ifstream::in);

  std::getline(f, s);
  while (f.good()) {
    input.push_back(s);

    std::getline(f, s);
  }
}

