//
// Created by Lucas Angelozzi on 2023-04-21.
//

#ifndef HUFF_MY_FILE_DECOMPRESS_H
#define HUFF_MY_FILE_DECOMPRESS_H

#include <cstdio>

std::unordered_map<char, std::vector<int>*>* restoreCodewords(FILE* file, long numUniqueChars);

int decompress(FILE* file);

#endif //HUFF_MY_FILE_DECOMPRESS_H
