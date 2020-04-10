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
void PNGParser::printBytesAs4ByteInt()
{
    std::cout << "Bytes:" << std::endl;
    unsigned long longint;
    for (int i=0; i<bytes.size();i+=4) {
      longint = bytes[i+3]|(bytes[i+2]<<8)|(bytes[i+1]<<16)|(bytes[i]<<24);
        std::cout << longint << "|";
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
