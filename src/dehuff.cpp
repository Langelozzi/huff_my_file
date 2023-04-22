//
// Created by Lucas Angelozzi on 2023-04-21.
//


#include <iostream>
#include <fstream>
#include "util/helpers.h"
#include "util/decompress.h"

/**
 * Compress a text file to a new file using huffman encoding algorithm.
 * @param argc argument count: the number of command line arguments provided
 * @param argv argument vector: the string (char*) arguments provided
 * @return exit status 0
 */
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Please provide a zipped filename when using this command. e.g. dehuff file.zip" << std::endl;
        exit(1);
    }
    char* filename = argv[1];

    FILE *file = getFile(filename);

    int buffer;

    // get the total number of characters in the file
    std::string charCountString;
    buffer = fgetc(file);
    while (buffer != '|') {
        charCountString.append((char *) &buffer);
        buffer = fgetc(file);
    }
    long long charCount = strtoll((char *) &charCountString, nullptr, 10);

    // get the number of unique characters in the file
    auto *numUniqueCharString = new std::string();
    buffer = fgetc(file);
    while (buffer != '|') {
        numUniqueCharString->append((char *) &buffer);
        buffer = fgetc(file);
    }
    long numUniqueChar = strtol((char *) numUniqueCharString, nullptr, 10);

    std::cout << charCount << " " << numUniqueChar << std::endl;

    auto codewords = restoreCodewords(file, numUniqueChar);
    if (codewords == nullptr) {
        return 0;
    }
    printCodeWords(codewords);

    Node* huffmanTree = restoreHuffmanTree(codewords);

    auto decompressedFile = createDecompressedFile(filename);

    // when executing this function, the file cursor is at the end of the metadata and the start of the actual text
    // content
    decompress(file, decompressedFile, huffmanTree);

    return 0;
}