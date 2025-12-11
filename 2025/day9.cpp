#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdint>

#include "parse_file.h"

#define EMPTY 0
#define RED   1
#define GREEN 2

int main(void) {
    std::vector<std::string> input;

    std::vector<std::tuple<int, int>> coords;

    // Parse the input file
    parse_file_lines("inputs/day9_input.txt", input);

    for (auto &s : input) {
        auto delim = s.find(",");

        int x = std::stoi(s.substr(0, delim));
        int y = std::stoi(s.substr(delim + 1));

        coords.push_back({x, y});
    }

    // Part 1
    uint64_t max_area = 0;
    for (auto &c1 : coords) {
        for (auto &c2 : coords) {
            uint64_t area = (uint64_t)(abs(std::get<0>(c1) - std::get<0>(c2)) + 1) * (uint64_t)(abs(std::get<1>(c1) - std::get<1>(c2)) + 1);
            if (area > max_area)
                max_area = area;
        }
    }

    std::cout << "PART 1: " << max_area << std::endl;

    // Part 2
    auto prev_c = coords.back();
    for (auto &c : coords) {
        int x = std::get<0>(c);
        int y = std::get<1>(c);
        int prev_x = std::get<0>(prev_c);
        int prev_y = std::get<1>(prev_c);



        prev_c = c;
    }



    return 0;
}
