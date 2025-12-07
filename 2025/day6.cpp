#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "parse_file.h"

long do_math(std::vector<std::vector<long>> &operands, std::vector<char> &operations) {
    long sum = 0;
    for (int i = 0; i < operands.size(); i++) {
        long temp_val = -1;
        for (auto &val : operands[i]) {
            if (temp_val == -1)
                temp_val = val;
            else if (operations[i] == '*')
                temp_val *= val;
            else if (operations[i] == '+')
                temp_val += val;
        }

        sum += temp_val;
    }

    return sum;
}

int main(void) {
    std::vector<std::string> input;

    std::vector<std::vector<long>> operands_p1;
    std::vector<char> operations;

    // Parse the input file
    parse_file_lines("inputs/day6_input.txt", input);

    // Part 1 ***********************************************
    int col = 0;
    int row = 0;
    for (auto &s : input) {
        // Append a space at the end of each line to make processing easier
        s = s + " ";

        if (s.contains('+') || s.contains('*')) {
            for (auto c : s) {
                if (c != ' ')
                    operations.push_back(c);
            }
        }
        else {
            auto pos = s.find(" ");
            decltype(pos) old_pos = 0;

            row = 0;
            while (pos != std::string::npos) {
                if ((pos - old_pos) > 1) {
                    int val = std::stol(s.substr(old_pos, pos));
                    
                    if (col == 0)
                        operands_p1.push_back(std::vector<long>{val});
                    else
                        operands_p1[row].push_back(val);

                    row++;
                }
                old_pos = pos;
                pos = s.find(" ", pos + 1);
            }
        }

        col++;
    }

    long sum_p1 = do_math(operands_p1, operations);
    std::cout << "PART 1: " << sum_p1 << std::endl;

    // Part 2 ***********************************************
    std::vector<std::string> operands_p2_str;
    std::vector<std::vector<long>> operands_p2(operands_p1.size(), std::vector<long>{});

    row = 0;
    for (auto &s : input) {
        if (s.contains('+') || s.contains('*')) {
            // Skip the operations line, we already parsed it
            continue;
        }

        col = 0;
        for (auto c : s) {
            if (row == 0)
                operands_p2_str.push_back(std::string(&c, 1));
            else
                operands_p2_str[col] += std::string(&c, 1);

            col++;
        }

        row++;
    }

    row = 0;
    for (auto op : operands_p2_str) {
        auto no_space_end = std::remove(op.begin(), op.end(), ' ');
        op.erase(no_space_end, op.end());

        if (op == "") {
            row++;
        }
        else {
            operands_p2[row].push_back(std::stol(op));
        }
    }

    long sum_p2 = do_math(operands_p2, operations);
    std::cout << "PART 2: " << sum_p2 << std::endl;

    return 0;
}
