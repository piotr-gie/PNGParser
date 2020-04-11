#include "PNGParser.hpp"

#include <iostream>
#include <fstream>

void ImageData::printData()
{
    std::cout << "### Image data ###" << std::endl;
    std::cout << "Image width: " << width << std::endl;
    // TODO
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

    unsigned int ihdrLength =
        concatenate4Bytes(
            imageBytes[ihdrFirstBytePosition],
            imageBytes[ihdrFirstBytePosition + 1],
            imageBytes[ihdrFirstBytePosition + 2],
            imageBytes[ihdrFirstBytePosition + 3]
        );

    constexpr int ihdrDataFirstBytePosition{16};
    for (unsigned int i = ihdrDataFirstBytePosition; i < ihdrLength; i++) {
        // calculations
    }

    imageData.width =
        concatenate4Bytes(
            imageBytes[ihdrDataFirstBytePosition],
            imageBytes[ihdrDataFirstBytePosition + 1],
            imageBytes[ihdrDataFirstBytePosition + 2],
            imageBytes[ihdrDataFirstBytePosition + 3]
        );

    std::cout << "IHDR first byte (it should not be 'I'): " << imageBytes[ihdrFirstBytePosition] << std::endl;
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
    for (auto byte : imageBytes) {
        std::cout << std::dec << static_cast<int>(byte) << " ";
    }

    std::cout << std::endl;
}

void PNGParser::printBytesAsHexNumbers()
{
    for (auto byte : imageBytes) {
        std::cout << std::hex << static_cast<int>(byte) << " ";
    }

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
