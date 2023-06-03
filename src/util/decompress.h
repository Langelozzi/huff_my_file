//
// Created by Lucas Angelozzi on 2023-04-21.
//

#ifndef HUFF_MY_FILE_DECOMPRESS_H
#define HUFF_MY_FILE_DECOMPRESS_H

#include <cstdio>
#include "../models/Node.h"

std::unordered_map<char, std::vector<int>*>* restoreCodewords(FILE* file, long numUniqueChars);

Node* restoreHuffmanTree(std::unordered_map<char, std::vector<int>*>* codewords);

std::ofstream createDecompressedFile(const char* zipFileName);

void decompress(FILE* originalFile, std::ofstream& outputFile, Node* huffmanTreeHead, long long charCount);

#endif //HUFF_MY_FILE_DECOMPRESS_H
