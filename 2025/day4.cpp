#include <vector>
#include <iostream>
#include <map>

#include "parse_file.h"

/**
 * Get the number of neighbouring rolls at a particular index (i, j).
 */
int get_num_neighbours(int i, int j, std::vector<std::vector<int>> &input) {
    auto height = input.size();
    auto width  = input[0].size();

    int num_neighbours = 0;
    if (i >= 1) {
                             num_neighbours += input[i - 1][j]; 
        if (j >= 1)          num_neighbours += input[i - 1][j - 1]; 
        if (j < (width - 1)) num_neighbours += input[i - 1][j + 1]; 
    }
    if (i < (height - 1)) {
                             num_neighbours += input[i + 1][j]; 
        if (j >= 1)          num_neighbours += input[i + 1][j - 1]; 
        if (j < (width - 1)) num_neighbours += input[i + 1][j + 1]; 
    }
    if (j >= 1)              num_neighbours += input[i][j - 1]; 
    if (j < (width - 1))     num_neighbours += input[i][j + 1]; 

    return num_neighbours;
}

int main(void) {
    std::vector<std::vector<int>> input;
    std::map<char, int> encoding{{'.', 0}, {'@', 1}};

    // Parse the input file
    parse_file_grid("inputs/day4_input.txt", encoding, input);

    auto height = input.size();
    auto width  = input[0].size();
 
    // Part 1
    long num_rolls = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // No roll in this spot
            if (input[i][j] == 0) continue;

            // We can only access rolls that have less than 4 neighbours
            if (get_num_neighbours(i, j, input) < 4)
                num_rolls++;
        }
    }            

    std::cout << "PART 1: " << num_rolls << std::endl;

    // Part 2
    long total_rolls_removed = 0;
    long curr_rolls_removed  = num_rolls;
    while (curr_rolls_removed > 0) {
        curr_rolls_removed = 0;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                // No roll in this spot
                if (input[i][j] == 0) continue;

                // Remove the current roll if we can access it
                if (get_num_neighbours(i, j, input) < 4) {
                    curr_rolls_removed++;
                    input[i][j] = 0;
                }
            }
        }

        total_rolls_removed += curr_rolls_removed;
    }
 
    std::cout << "PART 2: " << total_rolls_removed << std::endl;

    return 0;
}
