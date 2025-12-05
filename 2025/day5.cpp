#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include "parse_file.h"

int main(void) {
    std::vector<std::string> input;

    std::vector<std::tuple<long, long>> fresh_ingredients;
    std::vector<long> available_ingredients;

    // Parse the input file
    parse_file_lines("inputs/day5_input.txt", input);

    for (auto &s : input) {
        auto delim = s.find("-");

        if (delim != std::string::npos) {
            long first = std::stol(s.substr(0, delim));
            long second = std::stol(s.substr(delim + 1));

            fresh_ingredients.push_back({first, second});
        }
        else if (s.length() != 0) {
            available_ingredients.push_back(std::stol(s));
        }
    }

    // Part 1
    int num_fresh = 0;
    for (auto &ing : available_ingredients) {
        for (auto &fresh : fresh_ingredients) {
            if ((ing >= std::get<0>(fresh)) && (ing <= std::get<1>(fresh))) {
                num_fresh++;
                break;
            }
        }
    }

    std::cout << "PART 1: " << num_fresh << std::endl;

    // Part 2
    // Sort first - O(n log(n))
    // Then combine ranges - O(n)
    std::sort(fresh_ingredients.begin(), fresh_ingredients.end());

    std::vector<std::tuple<long, long>> reduced_fresh_ingredients;
    for (auto &fresh : fresh_ingredients) {
        if (reduced_fresh_ingredients.empty())
            reduced_fresh_ingredients.push_back(fresh);
        else {
            std::tuple<long, long>& prev = reduced_fresh_ingredients.back();

            if ((std::get<0>(fresh) >= std::get<0>(prev)) && (std::get<0>(fresh) <= std::get<1>(prev))) {
                std::get<1>(prev) = std::max(std::get<1>(fresh), std::get<1>(prev));
            }
            else {
                reduced_fresh_ingredients.push_back(fresh);
            }
        }
    }

    // Count number of fresh ingredients
    long fresh_cnt = 0;
    for (auto &ing : reduced_fresh_ingredients) {
        fresh_cnt += (std::get<1>(ing) - std::get<0>(ing) + 1);
    }

    std::cout << "PART 2: " << fresh_cnt << std::endl;

    return 0;
}
