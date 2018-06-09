//
// Created by Artem Ustinov on 6/2/2018.
//

#include <iostream>
#include <ctime>
#include "compressor.h"

using namespace std;

void help_message() {
    cout << "usage: <command> <SOURCE_FILE> <DESTINATION_FILE>\n\n";
    cout << "commands:\n";
    cout << "compress       Compress a file using Huffman algorithm.\n";
    cout << "decompress     Decompress file, compressed earlier.\n";
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        help_message();
        return 0;
    }
    string command = argv[1], SOURCE = argv[2], DESTINATION = argv[3];
    clock_t beg, end;
    if (SOURCE == DESTINATION) {
        cerr << "Source file and destination file must be different\n";
        return 0;
    }
    if (command == "compress") {
        cout << "Compressing...\n";
        beg = clock();
        try {
            compress(SOURCE, DESTINATION);
        } catch (std::runtime_error &e) {
            cerr << "Failed to compress " << argv[2] << ":\n";
            cerr << e.what();
            return 0;
        }
        end = clock();
        cout << argv[2] << " compressed successfully ";
        cout << '(' << double(end - beg) / CLOCKS_PER_SEC * 1000 << " ms)\n";

    } else if (command == "decompress") {
        cout << "Decompressing...\n";
        beg = clock();
        try {
            decompress(SOURCE, DESTINATION);
        } catch (std::runtime_error &e) {
            cout << "Failed to decompress " << argv[2] << ":\n";
            cout << e.what();
            return 0;
        }
        end = clock();
        cout << argv[2] << " decompressed successfully ";
        cout << '(' << double(end - beg) / CLOCKS_PER_SEC * 1000 << " ms)\n";
    } else {
        cerr << "Unknown command : " << command << "\n";
        help_message();
    }
    return 0;
}