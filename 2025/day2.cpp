#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>

int main(void) {
    std::vector<std::string> ranges;

    // Parse input
    std::ifstream f("inputs/day2_input.txt", std::ifstream::in);

    std::string s;
    std::getline(f, s);

    std::string token;
    std::istringstream ts(s);
    while (std::getline(ts, token, ',')) {
        ranges.push_back(token);
    }

    // Find all the invalid IDs
    long sum_p1 = 0;
    long sum_p2 = 0;
    for (auto &range : ranges) {
        auto delim_idx = range.find('-');
        long first_id = std::stol(range.substr(0, delim_idx));
        long last_id  = std::stol(range.substr(delim_idx + 1));

        // Loop through all IDs and sum all invalid ones
        for (long i = first_id; i <= last_id; i++) {
            std::string i_str = std::to_string(i);

            auto length = i_str.length();
            if (length % 2 == 0) {
                if (i_str.substr(0, length / 2) == i_str.substr(length / 2)) {
                    sum_p1 += i;
                }
            }

            for (int m = 1; m < length; m++) {
                std::regex match("(" + i_str.substr(0, m) + ")+");
                if (std::regex_match(i_str, match)) {
                    sum_p2 += i;
                    break;
                }
            }
        }
    }

    std::cout << "PART 1: " << sum_p1 << std::endl;
    std::cout << "PART 2: " << sum_p2 << std::endl;
}
