//
// Created by Lucas Angelozzi on 2023-04-21.
//

#include <cstdlib>
#include <iostream>
#include <fstream>
#include "decompress.h"
#include "helpers.h"
#include "../models/Node.h"

std::unordered_map<char, std::vector<int> *> *restoreCodewords(FILE *file, long numUniqueChars) {
    auto codes = new std::unordered_map<char, std::vector<int> *>();

    char buffer;
    // the number of unique characters is how many code mappings there will be
    for (int count = 0; count < numUniqueChars; count++) {
        // when compressing, the metadata for each codeword is as follows:
        // |character|number of bits in codeword|codeword in decimal|
        char character;
        int numBits;
        int codewordDecimal;

        // read those 3 pieces of data from the file
        character = fgetc(file);
        buffer = fgetc(file);
        numBits = atoi(&buffer);
        buffer = fgetc(file);
        codewordDecimal = atoi(&buffer);

        // convert the codeword back to binary
        std::vector<int> *binaryCodeword = integerToBinary(codewordDecimal);
        if (binaryCodeword->size() != numBits) {
            // some error checking to make sure the codeword is as long as it should be
            std::cout << "Decompression failed: could not restore codewords from metadata.";
            return nullptr;
        }

        // add the character and codeword into the map
        (*codes)[character] = binaryCodeword;
    }

    return codes;
};

Node *restoreHuffmanTree(std::unordered_map<char, std::vector<int> *> *codewords) {
    Node *root = new Node('\0');
    Node *treePtr = root;

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
                    Node *newNode = new Node('\0');
                    treePtr->setLeft(newNode);
                }
                // traverse to the left
                treePtr = treePtr->getLeft();
            } else if (bit == 1) {
                // if there is no node then create a dummy node to the right
                if (treePtr->getRight() == nullptr) {
                    Node *newNode = new Node('\0');
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
        Node *leafNode = new Node(character);
        if (bit == 0) {
            treePtr->setLeft(leafNode);
        } else if (bit == 1) {
            treePtr->setRight(leafNode);
        }

        // set the treePtr back to the root and start fresh for the next codeword
        treePtr = root;
        iterator++;
    }

    return root;
};

std::ofstream createDecompressedFile(const char *zipFileName) {
    std::string newFileName = zipFileName;
    newFileName.replace(
            newFileName.find("-compressed.zip"),
            sizeof("-compressed.zip") - 1,
            "-decompressed.txt"
    );

    std::ofstream newFile(newFileName);

    return newFile;
};

void decompress(FILE *originalFile, std::ofstream &outputFile, Node *huffmanTreeHead) {
    char buffer;
    buffer = fgetc(originalFile);

    Node *treePtr = huffmanTreeHead;

    while (buffer != EOF) {
        // convert the character in buffer (i.e. the compressed byte) back into binary
        std::vector<int> *byte = integerToBinary(buffer);

        // iterate through the bits, traversing the huffman tree as we go
        // if the node is a leaf node then we have successfully decoded a character and can write it to the file,
        // then reset the tree pointer back to the root
        auto iterator = byte->begin();
        while (iterator != byte->end()) {
            int bit = *iterator;
            if (bit == 1 && !treePtr->isLeaf()) {
                treePtr = treePtr->getRight();
            } else if (bit == 0 && !treePtr->isLeaf()) {
                treePtr = treePtr->getLeft();
            }

            if (treePtr->isLeaf()) {
                outputFile << treePtr->getData();
                treePtr = huffmanTreeHead;
            }

            iterator++;
        }

        buffer = fgetc(originalFile);
    }
};