//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include "compress.h"
#include "helpers.h"

std::unordered_map<char, int> getCharFrequency(FILE* file) {
    std::unordered_map<char, int> freqMap;

    char buffer;
    buffer = fgetc(file);
    while (buffer != EOF) {
        if (freqMap.find(buffer) == freqMap.end()) {
            freqMap[buffer] = 1;
        } else {
            freqMap[buffer]++;
        }
        buffer = fgetc(file);
    }

    return freqMap;
};

unsigned long long getCharCount(FILE* file) {
    long count = 0;
    char buffer;

    buffer = fgetc(file);
    while (buffer != EOF) {
        count++;
        buffer = fgetc(file);
    }

    return count;
};

Node* buildHuffmanTree(PriorityQueue* queue) {
    Node *left, *right, *root;

    while (queue->getSize() != 1) {
        left = queue->dequeue();
        right = queue->dequeue();
        root = new Node('\0', left->getPriority() + right->getPriority());

        root->setLeft(left);
        root->setRight(right);

        queue->insert(root);
    }

    return queue->dequeue();
};

void getCodesHelper(Node *root, int arr[], int top, std::unordered_map<char, std::vector<int>*>* codes) {
    if (root->getLeft()) {
        arr[top] = 0;
        getCodesHelper(root->getLeft(), arr, top + 1, codes);
    }
    if (root->getRight()) {
        arr[top] = 1;
        getCodesHelper(root->getRight(), arr, top + 1, codes);
    }
    if (root->isLeaf()) {
        (*codes)[root->getData()] = new std::vector<int>;

        for (int i = 0; i < top; i++) {
            codes->find(root->getData())->second->push_back(arr[i]);
        }
    }
}

std::unordered_map<char, std::vector<int>*>* getHuffmanCodes(Node *huffmanTreeRoot) {
    auto codes = new std::unordered_map<char, std::vector<int>*>();

    int arr[50], top = 0;
    getCodesHelper(huffmanTreeRoot, arr, top, codes);

    return codes;
}

std::ofstream createCompressedFile(const char* originalFileName) {
    std::string newFileName = originalFileName;
    newFileName.replace(newFileName.find(".txt"), sizeof(".txt") - 1, "-compressed.zip");

    std::ofstream newFile(newFileName, std::ios::binary);

    return newFile;
};

// the format being written is |character|length of codeword|codeword as integer|
void writeCodewords(std::ofstream& compressedFile, std::unordered_map<char, std::vector<int>*>* codewordMapping) {
    for (auto& iterator : *codewordMapping) {
        char character = iterator.first;
        unsigned long codewordLength = iterator.second->size();
        int codewordAsInt = binaryToInteger(iterator.second);

        compressedFile << character << codewordLength << "|" << codewordAsInt << "|";
    }
};

void writeMetadata(
        std::ofstream& compressedFile,
        unsigned long long charCount,
        unsigned long numUniqueChars,
        std::unordered_map<char, std::vector<int>*>* codewordMapping
) {
    compressedFile << charCount << "|" << numUniqueChars << "|";
    writeCodewords(compressedFile, codewordMapping);
};

void compress(
        FILE* originalFile, std::ofstream& outputFile, std::unordered_map<char, std::vector<int>*>* codewordMapping
) {
    unsigned char currentByte = 0; // start at 0000 0000
    int currentByteCount = 0;

    char currentChar;
    currentChar = fgetc(originalFile);
    while (currentChar != EOF) {
        auto code = (*codewordMapping)[currentChar];

        auto iterator = code->begin();
        while (iterator != code->end()) {
            int bit = *iterator;
            // if current byte is not yet "full"
            if (currentByteCount < 7) {
                if (bit == 1) {
                    // add 1 to current byte (0000 0001)
                    currentByte++;
                    // shift the 1 over a spot (0000 0010)
                    currentByte <<= 1;
                    currentByteCount++;
                } else if (bit == 0) {
                    // don't add 1 but shift the 0 over a spot
                    currentByte <<= 1;
                    currentByteCount++;
                }
                iterator++;
            }
            // once there are 7 bits filled
            else if (currentByteCount == 7) {
                if (bit == 1) {
                    // add the final bit to the current byte
                    currentByte++;
                }
                // reset byte count
                currentByteCount = 0;
                // write the byte to the new file
                outputFile.write((char *) &currentByte, sizeof(currentByte));
                // reset the byte back to 0000 0000
                currentByte = 0;
            }
        }
        currentChar = fgetc(originalFile);
    }
    // shift 0's onto the end of the last byte then write it
    for (int i = 0; i < 7 - currentByteCount; i++) {
        currentByte <<= 1;
    }
    outputFile.write((char *) &currentByte, sizeof(currentByte));
};
