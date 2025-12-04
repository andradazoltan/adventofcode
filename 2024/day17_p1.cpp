#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include <vector>
#include <cmath>

typedef enum {
    ADV = 0,
    BXL = 1,
    BST = 2,
    JNZ = 3,
    BXC = 4,
    OUT = 5,
    BDV = 6,
    CDV = 7
} opcode_t;

typedef struct {
    opcode_t op;
    long operand;
} instruction_t;

/**
 * Get the value of a combo operand.
 */
long get_combo_operand(int operand, long reg_a, long reg_b, long reg_c) {
    if (operand <= 3)
        return operand;
    else if (operand == 4)
        return reg_a;
    else if (operand == 5)
        return reg_b;
    else if (operand == 6)
        return reg_c;
    else
        return 0; // Should not occur
}

/**
 * Function for ADV, BDV, CDV commands.
 */
void div(long a, long b, long *out) {
    *out = floor(a / pow(2, b));
}

/**
 * Function for BXL and BXC command.
 */
void bx(long *a, long b) {
    *a = *a ^ b;
}

int main(void) {
    std::string s;

    long reg_a;
    long reg_b;
    long reg_c;

    std::vector<instruction_t> ins;

    // Parse the input file
    std::ifstream f("inputs/day17_input.txt", std::ifstream::in);

    std::getline(f, s);
    while (f.good()) {
        if (s.find("A") != std::string::npos)
            reg_a = std::stol(s.substr(s.find(": ") + 2, s.length() - 1));
        else if (s.find("B") != std::string::npos)
            reg_b = std::stol(s.substr(s.find(": ") + 2, s.length() - 1));
        else if (s.find("C") != std::string::npos)
            reg_c = std::stol(s.substr(s.find(": ") + 2, s.length() - 1));
        else if (s.find("Program") != std::string::npos) {
            s.erase(0, s.find(": ") + 2);

            while (s.find(',') != std::string::npos) {
                opcode_t op = (opcode_t)std::stoi(s.substr(0, s.find(',')));
                s.erase(0, s.find(',') + 1);
                int operand = std::stoi(s.substr(0, s.find(',')));
                s.erase(0, s.find(',') + 1);

                ins.push_back({.op = op, .operand = operand});
            }  
        }
          
        std::getline(f, s);
    }

    // Run through the program
    std::string output = "";

    int ins_ptr = 0;
    while (ins_ptr < ins.size()) {
        auto i = ins[ins_ptr];
        int operand;
        int out;

        switch (i.op) {
            case ADV:
                operand = get_combo_operand(i.operand, reg_a, reg_b, reg_c);

                div(reg_a, operand, &reg_a);
                break;

            case BXL:
                bx(&reg_b, i.operand);
                break;

            case BST:
                reg_b = get_combo_operand(i.operand, reg_a, reg_b, reg_c) % 8;
                break;

            case JNZ:
                std::cout << "JNZ " << i.operand << "\n";
                if (reg_a != 0) {
                    ins_ptr = i.operand / 2;
                    continue;
                }
                break;

            case BXC:
                bx(&reg_b, reg_c);
                break;

            case OUT:
                out = get_combo_operand(i.operand, reg_a, reg_b, reg_c) % 8; 
                output += std::to_string(out) + ',';
                break;

            case BDV:
                operand = get_combo_operand(i.operand, reg_a, reg_b, reg_c);

                div(reg_a, operand, &reg_b);
                break;

            case CDV:
                operand = get_combo_operand(i.operand, reg_a, reg_b, reg_c);

                div(reg_a, operand, &reg_c);
                break;

            default:
                // Should never end up here
                break;
        }

        ins_ptr++;
        std::cout << "OP " << i.op << std::endl;
        std::cout << "REG A " << reg_a << std::endl;
        std::cout << "REG B " << reg_b << std::endl;
        std::cout << "REG C " << reg_c << std::endl << std::endl;
    }

    std::cout << output.substr(0, output.length() - 1) << std::endl;

    return 0;
}
