#include <vector>
#include <string>
#include <iostream>
#include <map>

#include "parse_file.h"

/**
 * Traverse the graph and get the number of paths we can take from
 * curr_id to out_id.
 */
long count_paths(std::vector<std::vector<int>> &adj_list, 
                 std::vector<int> &memo,
                 int curr_id, int out_id) {
    // Base Case 1: we have made it to out_id
    if ((curr_id == out_id))
        return 1;

    // Base Case 2: invalid path to out_id
    if (adj_list[curr_id].size() == 0)
        return 0;

    // Is this result memoized already?
    if (memo[curr_id] != -1)
        return memo[curr_id];

    // If not, then we need to calculate it
    int num_paths = 0;
    for (auto &d : adj_list[curr_id]) {
        num_paths += count_paths(adj_list, memo, d, out_id);
    }
    memo[curr_id] = num_paths;

    return num_paths;
}

/**
 * Wrapper for count_paths that creates the memoization vector.
 */
long get_num_paths(std::vector<std::vector<int>> &adj_list, int curr_id, int out_id) {
    std::vector<int> memo(adj_list.size(), -1);
    return count_paths(adj_list, memo, curr_id, out_id);
}


int main(void) {
    std::vector<std::string> input;

    std::map<std::string, int> encoding;        // Mapping from device name to ID
    std::vector<std::vector<int>> adj_list;     // Graph

    // Parse the input file
    parse_file_lines("inputs/day11_input.txt", input);

    // Extract all the encodings and build the graph
    int num_encoding = 0;
    for (auto &s : input) {
        size_t prev_pos = 0;
        size_t curr_pos = s.find(" ");

        int root_id = -1;
        while (true) {
            std::string curr = s.substr(prev_pos, curr_pos - prev_pos);

            // Assign encoding for this device name
            if (curr.contains(':'))
                curr.erase(curr.length() - 1, 1);

            if (!encoding.contains(curr)) {
                encoding.insert({curr, num_encoding});
                adj_list.resize(adj_list.size() + 1);
                num_encoding++;
            }

            // Build the graph for this line
            if (root_id == -1)
                root_id = encoding[curr];
            else
                adj_list[root_id].push_back(encoding[curr]);

            if (curr_pos == std::string::npos) break;
            prev_pos = curr_pos + 1;
            curr_pos = s.find(" ", curr_pos + 1);
        }
    }

    // Part 1 -----------------------------------------------------------
    int part1 = get_num_paths(adj_list, encoding["you"], encoding["out"]);
    std::cout << "PART 1: " << part1 << std::endl;
 
    // Part 2 -----------------------------------------------------------
    // To get all paths from svr to out that contain dac and fft we can 
    // consider 2 cases:
    //      - Case 1: dac comes before fft in the path
    //      - Case 2: fft comes before dac in the path
    //
    // We can break up both cases to find all paths from svr to the first
    // node, then from the first node to the second node, and finally 
    // from the second node to out.

    // Case 1
    long case1_a = get_num_paths(adj_list, encoding["svr"], encoding["dac"]);
    long case1_b = get_num_paths(adj_list, encoding["dac"], encoding["fft"]);
    long case1_c = get_num_paths(adj_list, encoding["fft"], encoding["out"]);

    // Case 2
    long case2_a = get_num_paths(adj_list, encoding["svr"], encoding["fft"]);
    long case2_b = get_num_paths(adj_list, encoding["fft"], encoding["dac"]);
    long case2_c = get_num_paths(adj_list, encoding["dac"], encoding["out"]);

    long part2 = (case1_a * case1_b * case1_c) + (case2_a * case2_b * case2_c);
    std::cout << "PART 2: " << part2 << std::endl;
 
    return 0;
}
