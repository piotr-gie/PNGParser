#include "PNGParser.hpp"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>

void ImageData::printData()
{
    std::cout << "### Image data ###" << std::endl;
    std::cout << "Image width: " << width << std::endl;
    std::cout << "Image height: " << height << std::endl;
    std::cout << "Image bit depth: " << bitDepth << std::endl;
    std::cout << "Image color type: " << colorType << std::endl;
}

PNGParser::PNGParser(std::string fileName_) : fileName{fileName_}
{
    readImageBytes();

    parseImage();
}

void PNGParser::readImageBytes()
{
    std::ifstream image;

    // open file at the end (to get its length)
    image.open(fileName, std::ios::binary|std::ios::ate);

    if (not image) {
        std::cerr << "Error opening file" << std::endl;
    }

    // tellg() gives is the file position
    // (and therefore length)
    imageBytes.resize(image.tellg()); // make our vector big enough

    if (not imageBytes.empty()) {
        image.seekg(0); // move file position back to beginning

        if (not image.read((char*)&imageBytes[0], imageBytes.size())) {
            std::cerr << "Error reading file" << std::endl;
        }
    }

    image.close();
}

void PNGParser::parseImage()
{
    // readHeader();
    readIHDR();
}

void PNGParser::readIHDR()
{
    constexpr int ihdrFirstBytePosition{8};
    int index{ihdrFirstBytePosition};

    unsigned int ihdrLength = readNext4Bytes(index);

    constexpr int ihdrDataChunkFirstBytePosition{16};
    index = ihdrDataChunkFirstBytePosition;

    imageData.width = readNext4Bytes(index);
    imageData.height = readNext4Bytes(index);
    imageData.bitDepth = readNextByte(index);
    imageData.colorType = readNextByte(index);
}

int PNGParser::readNextByte(int& index)
{
    // assert(index < imageBytes.size());

    return imageBytes[index++];
}

unsigned int PNGParser::readNext4Bytes(int& index)
{
    // assert(index + 3 < imageBytes.size());

    index += 4;
    return concatenate4Bytes(
        imageBytes[index - 4],
        imageBytes[index - 3],
        imageBytes[index - 2],
        imageBytes[index - 1]
    );
}

void PNGParser::printImageData()
{
    imageData.printData();
}

unsigned int PNGParser::concatenate4Bytes(
    unsigned char b1,
    unsigned char b2,
    unsigned char b3,
    unsigned char b4
)
{
    return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

void PNGParser::printImageBytes()
{
    std::cout << "Bytes as decimal numbers:" << std::endl;
    printBytesAsDecNumbers();
    std::cout << std::endl;

    std::cout << "Bytes as hexdecimal numbers:" << std::endl;
    printBytesAsHexNumbers();
    std::cout << std::endl;

    std::cout << "Bytes as chars:" << std::endl;
    printBytesAsChars();
    std::cout << std::endl;
}

void PNGParser::printBytesAsDecNumbers()
{
    int i{};
    for (auto byte : imageBytes) {
        if (i % 16 == 0)
            std::cout << std::endl;
        else if (i % 8 == 0)
            std::cout << " ";
        i++;

        std::cout << std::setfill('0') << std::setw(3) << std::dec << static_cast<int>(byte) << " ";
    }

    std::cout << std::endl;
}

void PNGParser::printBytesAsHexNumbers()
{
    int i{};
    for (auto byte : imageBytes) {
        if (i % 16 == 0)
            std::cout << std::endl;
        else if (i % 8 == 0)
            std::cout << " ";
        i++;

        std::cout << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte) << " ";
    }

    std::cout << std::dec;
    std::cout << std::endl;
}

void PNGParser::printBytesAsChars()
{
    for (auto byte : imageBytes) {
        std::cout << byte << " ";
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
