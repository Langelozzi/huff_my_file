//
// Created by Lucas Angelozzi on 2023-04-21.
//

#include <cstdlib>
#include <iostream>
#include "decompress.h"
#include "helpers.h"
#include "../models/Node.h"

std::unordered_map<char, std::vector<int>*>* restoreCodewords(FILE* file, long numUniqueChars) {
    auto codes = new std::unordered_map<char, std::vector<int>*>();

    char buffer;
    for (int count = 0; count < numUniqueChars; count++) {
        char character;
        int numBits;
        int codewordDecimal;

        character = fgetc(file);
        buffer = fgetc(file);
        numBits = atoi(&buffer);
        buffer = fgetc(file);
        codewordDecimal = atoi(&buffer);

        std::vector<int>* binaryCodeword = integerToBinary(codewordDecimal);
        if (binaryCodeword->size() != numBits) {
            std::cout << "Decompression failed: could not restore codewords from metadata.";
            return nullptr;
        }

        (*codes)[character] = binaryCodeword;
    }

    return codes;
};

Node* restoreHuffmanTree(std::unordered_map<char, std::vector<int>*>* codewords) {
    Node* root = new Node('\0');
    Node* treePtr = root;

    // iterate through the codeword mappings
    auto iterator = codewords->begin();
    while (iterator != codewords->end()) {
        char character = iterator->first;
        std::vector<int> code = *(iterator->second);

        // iterate through the binary code until the second to last bit
        auto bitIterator = code.begin();
        int bit;
        while (bitIterator != std::prev(code.end())) {
            bit = *bitIterator;
            if (bit == 0) {
                // if there is no node then create a dummy node to the left
                if (treePtr->getLeft() == nullptr) {
                    Node* newNode = new Node('\0');
                    treePtr->setLeft(newNode);
                }
                // traverse to the left
                treePtr = treePtr->getLeft();
            } else {
                // if there is no node then create a dummy node to the right
                if (treePtr->getRight() == nullptr) {
                    Node* newNode = new Node('\0');
                    treePtr->setRight(newNode);
                }
                // traverse to the right
                treePtr = treePtr->getRight();
            }
            bitIterator++;
        }
        // loop will finish with bitIterator pointing at the last bit which will tell us which side to put the leaf
        // node with the actual character
        bit = *bitIterator;
        Node* leafNode = new Node(character);
        if (bit == 0) {
            treePtr->setLeft(leafNode);
        } else {
            treePtr->setRight(leafNode);
        }

        // set the treePtr back to the root and start fresh for the next codeword
        treePtr = root;
        iterator++;
    }

    return root;
};

int decompress(FILE* file) {
    char buffer;
    long long charCount;
    long numUniqueChar;

    buffer = fgetc(file);
    charCount = atoll(&buffer);
    buffer = fgetc(file);
    numUniqueChar = atoll(&buffer);

    std::cout << charCount << " " << numUniqueChar << std::endl;

    auto codewords = restoreCodewords(file, numUniqueChar);
    if (codewords == nullptr) {
        return 0;
    }
    printCodeWords(codewords);

    Node* huffmanTree = restoreHuffmanTree(codewords);

    return 1;
};