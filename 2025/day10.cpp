#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdint>

#include "parse_file.h"

/**
 * Get the fewest button presses to toggle all the lights
 * into their final desired position.
 */
int get_fewest_button_presses(int final_light, std::vector<int> &buttons) {
    int min_buttons = buttons.size();

    // This is not very efficient because we're checking every single
    // possible combination instead of start from the minimum number of
    // buttons and working up.
    //
    // However, it's an easy way to generate all possible combinations
    // and the input is small enough to allow for this.
    for (int i = 1; i < pow(2, buttons.size()); i++) {
        int val = 0;
        int num_buttons = 0;

        for (int iidx = 0; iidx < buttons.size(); iidx++) {
            if (i & (1 << iidx)) {
                num_buttons++;
                val ^= buttons[iidx];
            }
        }

        if ((final_light == val) && (num_buttons < min_buttons))
            min_buttons = num_buttons;
    }

    return min_buttons;
}

int main(void) {
    std::vector<std::string> input;

    std::vector<int>              final_lights;
    std::vector<std::vector<int>> buttons;

    // Parse the input file
    parse_file_lines("inputs/day10_input.txt", input);

    for (auto &s : input) {
        size_t prev_pos = 0;
        size_t curr_pos = s.find(" ");

        int light_len = 0; // Number of lights
        std::vector<int> button;
        while (curr_pos != std::string::npos) {
            std::string curr = s.substr(prev_pos, curr_pos - prev_pos);
            
            // Indicator light diagram
            if (curr.contains('[')) {
                light_len = curr.length() - 2;

                int val = 0;
                int i = light_len - 1;
                for (auto c : curr) {
                    if (c == '.')
                        i--;
                    if (c == '#') {
                        val |= (1 << i);
                        i--;
                    }
                }

                final_lights.push_back(val);
            }

            // Buttons
            if (curr.contains('(')) {
                int val = 0;
                for (auto c : curr) {
                    if (c != '(' && c != ')' && c != ',') {
                        val |= (1 << (light_len - (c - '0') - 1));
                    }
                }
                button.push_back(val);
            }

            // Joltage
            if (curr.contains('{')) {
                
            }

            prev_pos = curr_pos + 1;
            curr_pos = s.find(" ", curr_pos + 1);
        }

        buttons.push_back(button);
    }

    // Part 1
    long total_presses = 0;
    for (int i = 0; i < final_lights.size(); i++) {
        total_presses += get_fewest_button_presses(final_lights[i], buttons[i]);
    }

    std::cout << "PART 1: " << total_presses << std::endl;

    return 0;
}
