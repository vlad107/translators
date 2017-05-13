#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include <algorithm>

#include "helper.h"

int main(int argc, char *argv[]) {

    std::string input_file = "example.txt";
    if (argc >= 2) {
        input_file = argv[1];
    }

    if (nullptr == freopen(input_file.c_str(), "r", stdin)) {
        std::cerr << "no input file" << std::endl;
        return 0;
    }

    // read input
    std::vector<std::string> tokens;
    read_tokens(&tokens);


    return 0;

}
