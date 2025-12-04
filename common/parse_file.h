#pragma once

#include <string>
#include <vector>
#include <map>

/**
 * Parse an input file by reading every line in the file and
 * populating a vector of strings with each line.
 */
void parse_file_lines(std::string path, std::vector<std::string> &input);

/**
 * Parse an input file that has a grid-like format. Populate a 2D vector
 * representing the grid with each character mapped to an integer.
 *
 * Prints an error if the input map encoding does not contain an entry
 * for each character found in the file.
 */
void parse_file_grid(std::string path, std::map<char, int> &encoding, std::vector<std::vector<int>> &input);
