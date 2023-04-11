//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef COMPRESS_H
#define COMPRESS_H

#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <string>
#include "../models/PriorityQueue.h"

FILE* getFile(const char *fileName);

std::unordered_map<char, int> getCharFrequency(FILE* file);

Node* buildHuffmanTree(PriorityQueue* queue);

std::unordered_map<char, std::vector<int>*>* getHuffmanCodes(Node *huffmanTreeRoot);

#endif //COMPRESS_H
