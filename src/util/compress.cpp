//
// Created by Lucas Angelozzi on 4/10/2023.
//

#include "compress.h"
#include "helpers.h"

FILE* getFile(const char *fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == nullptr) {
        std::cout << "File failed to open" << std::endl;
        exit(1);
    }

    return file;
};

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
        root = new Node('$', left->getPriority() + right->getPriority());

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
    newFileName.replace(newFileName.find(".txt"), sizeof(".txt") - 1, "-compressed.txt");

    std::ofstream newFile(newFileName);

    return newFile;
};

// the format being written is |character|length of codeword|codeword as integer|
void writeCodewords(std::ofstream& compressedFile, std::unordered_map<char, std::vector<int>*>* codewordMapping) {
    for (auto& iterator : *codewordMapping) {
        char character = iterator.first;
        unsigned long codewordLength = iterator.second->size();
        int codewordAsInt = binaryToInteger(iterator.second);

        compressedFile << character << codewordLength << codewordAsInt;
    }
};

void writeMetadata(
        std::ofstream& compressedFile,
        unsigned long long charCount,
        unsigned long numUniqueChars,
        std::unordered_map<char, std::vector<int>*>* codewordMapping
) {
    compressedFile << charCount << numUniqueChars;
    writeCodewords(compressedFile, codewordMapping);
};