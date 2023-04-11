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