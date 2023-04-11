#include <iostream>
#include "models/PriorityQueue.h"
#include "util/compress.h"

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

// argc = argument count: number of arguments provided
// argv = a vector of arguments
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Please provide a filename when using this command. e.g. huff file.txt" << std::endl;
        exit(1);
    }
    char* filename = argv[1];

    FILE *file = getFile(filename);
    auto frequencyMap = getCharFrequency(file);

    auto pq = new PriorityQueue(frequencyMap);

    Node *huffmanTree = buildHuffmanTree(pq);
    std::unordered_map<char, std::vector<int>*>* codewords = getHuffmanCodes(huffmanTree);

    printCodeWords(codewords);

    return 0;
}
