//
// Created by Lucas Angelozzi on 4/10/2023.
//

#ifndef COMPRESS_H
#define COMPRESS_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include "../models/PriorityQueue.h"

/**
 * Read the file and construct a character frequency table using an unordered_map.
 * @param file the file to read
 * @return an unordered_map with the character frequency of the file
 */
std::unordered_map<char, int> getCharFrequency(FILE* file);

/**
 * Count the number of characters in the file.
 * @param file the file pointer
 * @return a long representing how many total characters are in the file
 */
unsigned long long getCharCount(FILE* file);

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

/**
 * Create a new file with the same name as the original, but with the word "compressed" appended
 * @param originalFileName the name of the original file
 * @return positive number if successful, 0 if unsuccessful
 */
std::ofstream createCompressedFile(const char* originalFileName);

/**
 * Write in the metadata of the compressed file with contains the total number of characters in the file, the number
 * of unique characters in the file, and the mapping of characters to codewords.
 * @param charCount
 * @param numUniqueChars
 * @param codewordMapping
 */
void writeMetadata(
        std::ofstream& compressedFile,
        unsigned long long charCount,
        unsigned long numUniqueChars,
        std::unordered_map<char, std::vector<int>*>* codewordMapping
);

void compress(
        FILE* originalFile,
        std::ofstream& outputFile,
        std::unordered_map<char, std::vector<int>*>* codewordMapping
);

#endif //COMPRESS_H
