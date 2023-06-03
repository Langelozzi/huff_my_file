#include "../models/PriorityQueue.h"
#include "compress.h"
#include "helpers.h"
#include "huff.h"

/**
 * Compress a text file to a new file using huffman encoding algorithm.
 * @param argc argument count: the number of command line arguments provided
 * @param argv argument vector: the string (char*) arguments provided
 * @return exit status 0
 */
int huff(char* filename) {
    FILE *file = getFile(filename);
    auto frequencyMap = getCharFrequency(file);

    auto pq = new PriorityQueue(frequencyMap);

    Node *huffmanTree = buildHuffmanTree(pq);
    std::unordered_map<char, std::vector<int>*>* codewords = getHuffmanCodes(huffmanTree);
    printCodeWords(codewords);

    std::ofstream compressedFile = createCompressedFile(filename);

    // rewind will set the file pointer back to the beginning of the file
    rewind(file);
    unsigned long long charCount = getCharCount(file);
    unsigned long numUniqueChars = frequencyMap.size();

    writeMetadata(compressedFile, charCount, numUniqueChars, codewords);

    rewind(file);
    compress(file, compressedFile, codewords);

    compressedFile.close();
    fclose(file);
    return 0;
}
