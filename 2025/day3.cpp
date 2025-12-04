#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

#include "parse_file.h"

int main(void) {
    std::vector<std::string> input;

    // Parse the input file
    parse_file_lines("inputs/day3_input.txt", input);

    // PART 1 ************************************************
    // Turn on two batteries
    long joltage_sum = 0;

    for (auto &bank : input) {
        auto first_battery = std::max_element(bank.begin(), bank.end() - 1);
        auto second_battery = std::max_element(first_battery + 1, bank.end());

        joltage_sum += (*first_battery - '0') * 10 + (*second_battery - '0');
    }

    std::cout << "PART 1: " << joltage_sum << std::endl;
     
    // PART 2 ************************************************
    // Turn on twelve batteries
    joltage_sum = 0;

    for (auto &bank : input) {
        auto search_start = bank.begin();
        auto search_end   = bank.end() - 11;

        for (int i = 0; i < 12; i++) {
            auto battery = std::max_element(search_start, search_end);

            search_start = battery + 1;
            search_end++;

            joltage_sum += (*battery - '0') * pow(10, 11 - i);
        }
    }

    std::cout << "PART 2: " << joltage_sum << std::endl;
     
    return 0;
}
