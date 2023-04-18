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

/**
 * Open and return a pointer to the file with the given fileName, if it exists.
 * @param fileName the name of the file to open
 * @return a pointer to the file
 */
FILE* getFile(const char *fileName);

/**
 * Read the file and construct a character frequency table using an unordered_map.
 * @param file the file to read
 * @return an unordered_map with the character frequency of the file
 */
std::unordered_map<char, int> getCharFrequency(FILE* file);

/**
 * Build a Huffman Tree data structure using the Huffman algorithm.
 * @param queue the PriorityQueue to use as the basis for our Huffman algorithm
 * @return a pointer to the root Node of our Huffman Tree
 */
Node* buildHuffmanTree(PriorityQueue* queue);

/**
 * Traverse the Huffman Tree and generate an unordered_map with the keys as the character and the values as the
 * binary codewords represented as a vector of integers.
 * @param huffmanTreeRoot
 * @return
 */
std::unordered_map<char, std::vector<int>*>* getHuffmanCodes(Node *huffmanTreeRoot);

#endif //COMPRESS_H
