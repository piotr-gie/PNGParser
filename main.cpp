#include "PNGParser.hpp"

#include <iostream>

int main(int argc, char** argv)
{
    std::string fileName{"PNGImages/example1.png"};
    if (argc > 1) {
        fileName = argv[1];
    }

    PNGParser parser{fileName};

    // parser.printImageBytes();
    parser.printImageData();
    parser.createAnonymizeImage();
    // parser.showImage(); // xdg-open required
    // parser.showAnonymizedImage(); // xdg-open required
}
