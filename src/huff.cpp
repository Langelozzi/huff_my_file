#include <iostream>
#include "models/PriorityQueue.h"
#include "util/compress.h"
#include "util/helpers.h"

/**
 * Compress a text file to a new file using huffman encoding algorithm.
 * @param argc argument count: the number of command line arguments provided
 * @param argv argument vector: the string (char*) arguments provided
 * @return exit status 0
 */
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
