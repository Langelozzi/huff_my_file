//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include "helpers.h"
#include <iostream>
#include <cmath>


FILE* getFile(const char *fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == nullptr) {
        std::cout << "File failed to open" << std::endl;
        exit(1);
    }

    return file;
};

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

std::vector<int>* integerToBinary(unsigned char intNum) {
    auto binaryNum = new std::vector<int>;

    if (intNum == 0) {
        binaryNum->push_back(0);
        return binaryNum;
    }

    while (intNum > 0) {
        binaryNum->push_back(intNum % 2);
        intNum /= 2;
    }

    std::reverse(binaryNum->begin(), binaryNum->end());
    return binaryNum;
};

int countDigits(int num) {
    // example: num = 1234, it is between 1000 and 10000, so 3 < log10(1234) < 4, but when turned int, will be 3 + 1 = 4
    return int(log10(num) + 1);
};