//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include "helpers.h"
#include <iostream>

void printCodeWords(std::unordered_map<char, std::vector<int>*>* codewords) {
    std::cout << "Huffman Codeword:" << std::endl;

    auto iterator = codewords->begin();
    while (iterator != codewords->end()) {
        std::cout << iterator->first << " | ";
        for (auto bit : *(iterator->second)) {
            std::cout << bit;
        }
        std::cout << std::endl;

        std::advance(iterator, 1);
    }
}

int binaryToInteger(std::vector<int>* binaryNum) {
    int result = 0;
    int currentMultiplier = 1;

    // rbegin() = reverse begin (i.e. the last index) and rend() is first index
    for (auto iterator = binaryNum->rbegin(); iterator != binaryNum->rend(); iterator++) {
        int bit = *iterator;
        if (bit == 1) {
            result += currentMultiplier;
        }
        currentMultiplier *= 2;
    }

    return result;
};