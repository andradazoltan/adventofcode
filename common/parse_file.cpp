#include <fstream>
#include <iostream>
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

void parse_file_grid(std::string path, std::map<char, int> &encoding, std::vector<std::vector<int>> &input) {
    std::string s;
    std::ifstream f(path, std::ifstream::in);

    std::getline(f, s);
    while (f.good()) {
        std::vector<int> tmp;
        for (auto &c : s) {
            if (encoding.contains(c))
                tmp.push_back(encoding[c]);
            else {
                std::cout << "ERROR: no encoding provided for char " << c << std::endl;
                return;
            }
        }

        input.push_back(tmp);
        std::getline(f, s);
    }
}

