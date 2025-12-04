#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

#include "parse_file.h"

int main(void) {
  std::vector<std::string> input;

  // Parse the input file
  parse_file_lines("inputs/day1_input.txt", input);

  int32_t old_pos       = 50;
  int32_t curr_pos      = 50;
  const int32_t max_pos = 99;

  uint32_t password_p1 = 0;
  uint32_t password_p2 = 0;

  for (auto &ins : input) {
    // Turn the dial
    int32_t dial_turns = std::stoi(ins.substr(1));

    if (ins[0] == 'L') {
      auto new_pos = (curr_pos - dial_turns) % (max_pos + 1);

      if (new_pos < 0)
        curr_pos = max_pos + new_pos + 1;
      else
        curr_pos = new_pos;
    }
    else {
      curr_pos = (curr_pos + dial_turns) % (max_pos + 1);
    }

    // Increment password
    if (curr_pos == 0) password_p1++;

    if (ins[0] == 'L') {
      if ((curr_pos > old_pos) && (old_pos != 0)) password_p2++;
      if (curr_pos == 0)                          password_p2++;
    }
    else {
        if ((curr_pos < old_pos) && (old_pos != 0)) password_p2++;
    }
    password_p2 += dial_turns / (max_pos + 1);

    old_pos = curr_pos;
  }

  std::cout << "Part 1: " << password_p1 << std::endl;
  std::cout << "Part 2: " << password_p2 << std::endl;

  return 0;
}
