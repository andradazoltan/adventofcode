#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <numeric>

#include "parse_file.h"
#include "priority_queue.h"
#include "union_find.h"

typedef struct {
    int x;
    int y;
    int z;
} box_t;

// Get the distance between two boxes
inline double get_distance(box_t &a, box_t &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

int main(void) {
    std::vector<std::string> input;

    // Parse the input file
    parse_file_lines("inputs/day8_input.txt", input);

    // Make distance map
    std::vector<box_t> coords;
    PriorityQueue<std::tuple<int, int>> distances;

    for (auto &s : input) {
        auto comma1_pos = s.find(",");
        auto comma2_pos = s.find(",", comma1_pos + 1);

        int x = std::stoi(s.substr(0, comma1_pos));
        int y = std::stoi(s.substr(comma1_pos + 1, comma2_pos));
        int z = std::stoi(s.substr(comma2_pos + 1));

        coords.push_back({.x = x, .y = y, .z = z});
    }

    for (int i = 0; i < input.size(); i++) {
        for (int j = i + 1; j < input.size(); j++) {
            distances.insert(get_distance(coords[i], coords[j]), std::tuple<int, int>{i, j});
        }
    }

    // Make the connections for part 1 using a union-find structure
    UnionFind circuits(coords.size());
    int num_connections = 1000;
    for (int i = 0; i < num_connections; i++) {
        auto pair = distances.pop();

        int a = std::get<0>(pair);
        int b = std::get<1>(pair);

        circuits.unite(a, b);
    }

    // Get the max 3 sized circuits
    auto sizes = circuits.get_sorted_size_of_sets();
    int part_1 = sizes[0] * sizes[1] * sizes[2];
    std::cout << "PART 1: " << part_1 << std::endl;

    // Part 2, keep uniting until we have just one circuit
    int a;
    int b;
    while (sizes.size() != 1) {
        auto pair = distances.pop();

        a = std::get<0>(pair);
        b = std::get<1>(pair);

        circuits.unite(a, b); 
        sizes = circuits.get_sorted_size_of_sets();
    }

    long part_2 = (long)coords[a].x * coords[b].x;
    std::cout << "PART 2: " << part_2 << std::endl;

    return 0;
}
