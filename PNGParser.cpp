#include "PNGParser.hpp"

#include <iostream>
#include <fstream>


PNGParser::PNGParser(std::string fileName_) : fileName{fileName_}
{
    readImage();
}

void PNGParser::readImage()
{
    std::ifstream image{fileName};

    if (not image) {
        std::cerr << "Cannot open file" << std::endl;
        // TODO throw Exception
    }

    unsigned char byte;
    while (image >> byte) {
        bytes.push_back(static_cast<int>(byte));
    }
}

void PNGParser::printBytesAsInt()
{
    std::cout << "Bytes:" << std::endl;

    for (auto byte : bytes) {
        std::cout << byte << "|";
    }

    std::cout << std::endl;
}

void PNGParser::showImage()
{
    std::string showImageCommand;
    showImageCommand += "xdg-open ";
    showImageCommand += fileName;

    system(showImageCommand.c_str());
}
