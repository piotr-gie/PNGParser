#include "PNGParser.hpp"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void ImageData::printData()
{
    std::cout << "### Image data ###" << std::endl;
    std::cout << "size: " << size << " bytes" << std::endl;
    std::cout << "width: " << width << std::endl;
    std::cout << "height: " << height << std::endl;
    std::cout << "bit depth: " << bitDepth << std::endl;
    std::cout << "color type: " << colorType << std::endl;
    std::cout << "compression method: " << compressionMethod << std::endl;
    std::cout << "filter method: " << filterMethod << std::endl;
    std::cout << "interlace method: " << interlaceMethod << std::endl;

    std::cout << "contains PLTE chunk: " << std::boolalpha << isPLTE << std::endl;
    std::cout << "Number of IDAT chunks: " << idatChunks << std::endl;
}

PNGParser::PNGParser(std::string fileName_) : fileName{fileName_}
{
    readImageBytes();

    parseImage();
}

void PNGParser::readImageBytes()
{
    std::ifstream image{fileName};

    if (not image) {
        std::cerr << "Cannot open file" << std::endl;
        exit(1);
    }

    // imageBytes.clear();
    unsigned char byte;
    while (image >> std::noskipws >> byte) {
        imageBytes.push_back(byte);
    }
}

void PNGParser::parseImage()
{
    imageData.size = imageBytes.size();

    readHeader();
    readIHDR();
    readPLTE();
    readIDAT();
    readIEND();
}

void PNGParser::readHeader()
{
    constexpr int headerLength{8};
    std::string header;
    for (std::size_t i = 0; i < headerLength; i++) {
        header += imageBytes[i];
    }

    if (header != "\x89PNG\r\n\x1a\n") {
        std::cerr << "Wrong image header";
        exit(1);
    }

    for (std::size_t  i = 0; i < headerLength; i++) {
        anonedImageBytes.push_back(imageBytes[i]);
    }
}

void PNGParser::readIHDR()
{
    unsigned int ihdrIndex{0};
    for (std::size_t i = 0; i < imageBytes.size() - 3; i++) {
        if (imageBytes[i] == 'I' and imageBytes[i + 1] == 'H'
        and imageBytes[i + 2] == 'D' and imageBytes[i + 3] == 'R') {
            ihdrIndex = i;
            break;
        }
    }

    unsigned int index{ihdrIndex - 4};
    unsigned int ihdrLength = readNext4Bytes(index);
    if (ihdrLength != 13) {
        std::cerr << "Wrong IHDR chunk size";
        exit(1);
    }

    index += 4;
    imageData.width = readNext4Bytes(index);
    imageData.height = readNext4Bytes(index);
    imageData.bitDepth = readNextByte(index);
    imageData.colorType = readNextByte(index);
    imageData.compressionMethod = readNextByte(index);
    imageData.filterMethod = readNextByte(index);
    imageData.interlaceMethod = readNextByte(index);

    for (std::size_t i = ihdrIndex - 4; i < ihdrIndex - 4 + ihdrLength + 12; i++) {
        anonedImageBytes.push_back(imageBytes[i]);
    }
}

void PNGParser::readPLTE()
{
    unsigned int plteIndex{0};
    for (std::size_t i = 0; i < imageBytes.size() - 3; i++) {
        if (imageBytes[i] == 'P' and imageBytes[i + 1] == 'L'
        and imageBytes[i + 2] == 'T' and imageBytes[i + 3] == 'E') {
            plteIndex = i;
            break;
        }
    }

    if (plteIndex == 0) {
        imageData.isPLTE = false;
        return;
    }

    imageData.isPLTE = true;
    unsigned int index{plteIndex - 4};
    unsigned int plteLength = readNext4Bytes(index);
    if (plteLength % 3 != 0) {
        std::cerr << "Wrong PLTE chunk length";
        exit(1);
    }

    index += 4;
    std::cout << "PLTE Palette" << std::endl;
    for (unsigned int i = 0; i < plteLength / 3; i++) {
        std::cout << "*Pallete no. " << i << "*"
                  << " Red: " << readNextByte(index)
                  << " Green: " << readNextByte(index)
                  << " Blue: " << readNextByte(index)
                  << std::endl;
    }

    for (std::size_t i = plteIndex - 4; i < plteIndex - 4 + plteLength + 12; i++) {
        anonedImageBytes.push_back(imageBytes[i]);
    }
}

void PNGParser::readIDAT()
{
    std::vector<unsigned int> idatIndice;
    for (std::size_t i = 0; i < imageBytes.size() - 3; i++) {
        if (imageBytes[i] == 'I' and imageBytes[i + 1] == 'D'
        and imageBytes[i + 2] == 'A' and imageBytes[i + 3] == 'T') {
            idatIndice.push_back(i);
        }
    }

    std::vector<unsigned int> idatLengths;
    for (std::size_t i = 0; i < idatIndice.size(); i++) {
        unsigned int index{idatIndice[i] - 4};
        unsigned int idatLength = readNext4Bytes(index);
        idatLengths.push_back(idatLength);
    }

    imageData.idatChunks = idatIndice.size();
    for (std::size_t j = 0; j < idatIndice.size(); j++) {
        for (std::size_t i = idatIndice[j] - 4; i < idatIndice[j] - 4 + idatLengths[j] + 12; i++) {
            anonedImageBytes.push_back(imageBytes[i]);
        }
    }
}

void PNGParser::readIEND()
{
    unsigned int iendIndex{0};
    for (std::size_t i = 0; i < imageBytes.size() - 3; i++) {
        if (imageBytes[i] == 'I' and imageBytes[i + 1] == 'E'
        and imageBytes[i + 2] == 'N' and imageBytes[i + 3] == 'D') {
            iendIndex = i;
            break;
        }
    }

    if (iendIndex == 0) {
        std::cerr << "Wrong IEND chunk" << std::endl;
        return;
    }

    unsigned int index{iendIndex - 4};
    unsigned int iendLength = readNext4Bytes(index);

    if (iendLength != 0) {
        std::cerr << "Wrong IEND chunk length";
        exit(1);
    }

    for (std::size_t i = iendIndex - 4; i < iendIndex - 4 + iendLength + 12; i++) {
        anonedImageBytes.push_back(imageBytes[i]);
    }
}

int PNGParser::readNextByte(unsigned int& index)
{
    assert(index < imageBytes.size());

    return imageBytes[index++];
}

unsigned int PNGParser::readNext4Bytes(unsigned int& index)
{
    assert(index + 3 < imageBytes.size());

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

void PNGParser::createAnonymizeImage()
{
    std::ofstream anonedImg{"anonedImage.png"};

    for (std::size_t i = 0; i < anonedImageBytes.size(); i++) {
        anonedImg << anonedImageBytes[i];
    }
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
    int ithByte{};
    for (auto byte : imageBytes) {
        if (ithByte % 16 == 0)
            std::cout << std::endl;
        else if (ithByte % 8 == 0)
            std::cout << " ";
        ithByte++;

        std::cout << std::setfill('0') << std::setw(3) << std::dec << static_cast<int>(byte) << " ";
    }

    std::cout << std::endl;
}

void PNGParser::printBytesAsHexNumbers()
{
    int ithByte{};
    for (auto byte : imageBytes) {
        if (ithByte % 16 == 0)
            std::cout << std::endl;
        else if (ithByte % 8 == 0)
            std::cout << " ";
        ithByte++;

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

void PNGParser::showAnonymizedImage()
{
    std::string showImageCommand;
    showImageCommand += "xdg-open ";
    showImageCommand += "anonedImage.png";

    system(showImageCommand.c_str());
}
