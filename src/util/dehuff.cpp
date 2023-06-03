//
// Created by Lucas Angelozzi on 2023-04-21.
//

#include <iostream>
#include <fstream>
#include "helpers.h"
#include "decompress.h"
#include "dehuff.h"

/**
 * Compress a text file to a new file using huffman encoding algorithm.
 * @param argc argument count: the number of command line arguments provided
 * @param argv argument vector: the string (char*) arguments provided
 * @return exit status 0
 */
int dehuff(char* filename) {
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

    std::cout << "Character count " << charCount << "\n" << "Unique character count " << numUniqueChar << std::endl;

    auto codewords = restoreCodewords(file, numUniqueChar);
    if (codewords == nullptr) {
        return 0;
    }
    printCodeWords(codewords);

    // NOTE: huffman tree is working properly
    Node* huffmanTree = restoreHuffmanTree(codewords);

    auto decompressedFile = createDecompressedFile(filename);

    // when executing this function, the file cursor is at the end of the metadata and the start of the actual text
    // content
    long long numDecompressedCharacters = decompress(file, decompressedFile, huffmanTree);
    // ^^ this is not working

    if (numDecompressedCharacters != charCount) {
        std::cerr << "Error: number of decompressed characters does not match the number of characters in the file" <<
        std::endl;
    }

    return 0;
}