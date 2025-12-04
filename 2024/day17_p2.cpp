/*
The program has a single output function that needs to run for the number of digits in the program
string (16 times).

The value of register A determines if the program loops back to the beginning at the end of the program.
Register A is updated by the ADV, 3 instruction once every iteration. This means that on the 16th
iteration ADV, 3 should cause register A to be set to 0. So the starting value of A must be greater
than (2 ^ 3) ^ 15 and less than (2 ^ 3) ^ 16.

The value of register A also affects the value of register B which changes the output value.
Register B goes through the following operations each iteration:
   regB = (regA % 8) ^ 1
   regB = regB ^ (regA / 2**regB)
   regB = regB ^ 6

   output = regB % 8
          = ((((regA % 8) ^ 1) ^ (regA / (2**((regA % 8) ^ 1)))) ^ 6) % 8

Possible values of (regA % 8) ^ 1 ^ 6:
    0 ^ 1 ^ 6 = 1 ^ 6 = 7
    1 ^ 1 ^ 6 = 0 ^ 6 = 6
    2 ^ 1 ^ 6 = 3 ^ 6 = 5
    3 ^ 1 ^ 6 = 2 ^ 6 = 4
    4 ^ 1 ^ 6 = 5 ^ 6 = 3
    5 ^ 1 ^ 6 = 4 ^ 6 = 2
    6 ^ 1 ^ 6 = 7 ^ 6 = 1
    7 ^ 1 ^ 6 = 6 ^ 6 = 0

Using some simplification, this can be simplified to:
   output = ((7 - (regA % 8)) ^ (regA / (2**((regA % 8) ^ 1)))) % 8
          = ((7 - (regA % 8)) ^ (regA >> ((regA % 8) ^ 1))) % 8

There are 8 possible cases:
    output = (7 ^ (regA >> 1)) % 8       // regA multiple of 8
    output = (6 ^ (regA >> 0)) % 8       // regA multiple of 8 + 1
    output = (5 ^ (regA >> 3)) % 8       // regA multiple of 8 + 2
    output = (4 ^ (regA >> 2)) % 8       // regA multiple of 8 + 3
    output = (3 ^ (regA >> 5)) % 8       // regA multiple of 8 + 4
    output = (2 ^ (regA >> 4)) % 8       // regA multiple of 8 + 5
    output = (1 ^ (regA >> 7)) % 8       // regA multiple of 8 + 6
    output = (0 ^ (regA >> 6)) % 8       // regA multiple of 8 + 7

The output each iteration of the program seems to depend only on the last 8-bits of the register A.
We can work backwards from the most significant byte, locking in each digit every iteration. In cases
where more than one digit can be valid, we store them all and continue testing all possible options
until we reach the very end.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/**
 * Test if the current most significant digits, passed in as argument i,
 * produce the end of the output program so far.
 */
bool test_output(int digits, long i, std::string prog_str) {
    std::string output = "";

    for (int iter = 0; iter < digits; iter++) {
        long out;
        switch (i % 8) {
            case 0:
                out = (7 ^ (i >> 1)) % 8;
                break;

            case 1:
                out = (6 ^ (i >> 0)) % 8;
                break;

            case 2:
                out = (5 ^ (i >> 3)) % 8;
                break;

            case 3:
                out = (4 ^ (i >> 2)) % 8;
                break;

            case 4:
                out = (3 ^ (i >> 5)) % 8;
                break;

            case 5:
                out = (2 ^ (i >> 4)) % 8;
                break;

            case 6:
                out = (1 ^ (i >> 7)) % 8;
                break;

            case 7:
                out = (0 ^ (i >> 6)) % 8;
                break;

            default:
                break;
        }

        i = i >> 3;

        output += std::to_string(out) + ',';
    }
    
    // Check if the output matches so far
    if ((prog_str.substr(prog_str.length() - output.length() + 1) == output.substr(0, output.length() - 1)))
        return true;
    else
        return false;
}

int main(void) {
    std::string s;
    std::string prog_str;

    // Parse the input file
    std::ifstream f("inputs/day17_input.txt", std::ifstream::in);

    std::getline(f, s);
    while (f.good()) {
        if (s.find("Program") != std::string::npos) {
            s.erase(0, s.find(": ") + 2);
            prog_str = s;
        }
          
        std::getline(f, s);
    }

    std::vector<long> regA;
    for (int i = 1; i < 16; i++) {
        if (i == 1) {
            for (int digit = 0; digit < 63; digit++) {
                if (test_output(i + 1, digit, prog_str)) {
                    regA.push_back(digit * 8);
                }
            }
        }
        else {
            std::vector<long> tmp;

            while (!regA.empty()) {
                for (int digit = 0; digit < 8; digit++) {
                    long test = regA.back() | digit;
                    if (test_output(i + 1, test, prog_str)) {
                        tmp.push_back(test * 8);
                    }
                }

                regA.pop_back();
            }

            regA = tmp;
        }
    }

    std::cout << (*std::min_element(regA.begin(), regA.end()) / 8) << std::endl;
    return 0;
}
