#include <vector>
#include <iostream>
#include <map>

#include "parse_file.h"

#define EMPTY 0
#define SPLIT 1
#define START 2

/**
 * Get number of times the beam splits when starting at coordinate (row, col).
 */
int get_splits(std::vector<std::vector<int>>  &input,
               std::vector<std::vector<bool>> &searched,
               int row,
               int col) {
 
    auto height = input.size();
    auto width  = input[0].size();

    // Base cases:
    //      - we reached the end of the manifold
    //      - we reached past boths sides of the manifold
    if ((row == (height - 1)) || (col == -1) || (col == width))
        return 0;

    if ((input[row][col] == SPLIT) && !searched[row][col]) {
        // Split once if we are at a splitter and haven't gone down
        // this path yet
        searched[row][col] = true;
        return get_splits(input, searched, row + 1, col + 1) + get_splits(input, searched, row + 1, col - 1) + 1;
    }
    else if (input[row][col] == EMPTY) {
        // Continue down if this spot is empty
        return get_splits(input, searched, row + 1, col);
    }
    else
        return 0; // We already checked this path
}

/**
 * Get total number of paths the beam can travel when starting at coordinate (row, col).
 *
 * DFS with memoization
 */
long get_total_paths(std::vector<std::vector<int>> &input,
                    std::vector<std::vector<long>> &memo,
                    int row,
                    int col) {
 
    auto height = input.size();
    auto width  = input[0].size();

    // Base cases:
    //      - we reached the end of the manifold so this is a valid path
    //      - we reached past boths sides of the manifold so this is not a valid path
    if (row == (height - 1))
        return 1;
    if ((col == -1) || (col == width))
        return 0;

    // Check if we have memoized a result at this spot already
    if (memo[row][col] != -1)
        return memo[row][col];

    // Otherwise, we still need to calculate the result from here
    if (input[row][col] == SPLIT) {
        long val = get_total_paths(input, memo, row + 1, col + 1) + get_total_paths(input, memo, row + 1, col - 1);
        memo[row][col] = val;
        return val;
    }
    else if (input[row][col] == EMPTY) {
        long val = get_total_paths(input, memo, row + 1, col);
        memo[row][col] = val;
        return val;
    }
    else
        return 0; // We shouldn't get here
}
 
int main(void) {
    std::vector<std::vector<int>> input;
    std::map<char, int> encoding{{'.', EMPTY}, {'^', SPLIT}, {'S', START}};

    // Parse the input file
    parse_file_grid("inputs/day7_input.txt", encoding, input);

    // Part 1
    std::vector<std::vector<bool>> searched(input.size(), std::vector<bool>(input[0].size(), false));

    int start_col = 0;
    for (int i = 0; i < input[0].size(); i++) {
        if (input[0][i] == START) {
            start_col = i;
            break;
        }
    }

    int num_split = get_splits(input, searched, 1, start_col);

    std::cout << "PART 1: " << num_split << std::endl;

    // Part 2
    std::vector<std::vector<long>> memo(input.size(), std::vector<long>(input[0].size(), -1));
    long num_paths = get_total_paths(input, memo, 1, start_col);

    std::cout << "PART 2: " << num_paths << std::endl;

    return 0;
}
