//
// Created by Lucas Angelozzi on 2023-04-21.
//


#include <iostream>
#include "util/helpers.h"
#include "util/decompress.h"

/**
 * Compress a text file to a new file using huffman encoding algorithm.
 * @param argc argument count: the number of command line arguments provided
 * @param argv argument vector: the string (char*) arguments provided
 * @return exit status 0
 */
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Please provide a zipped filename when using this command. e.g. dehuff file.zip" << std::endl;
        exit(1);
    }
    char* filename = argv[1];

    FILE *file = getFile(filename);

    decompress(file);

    return 0;
}