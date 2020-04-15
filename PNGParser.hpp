#pragma once

#include <string>
#include <vector>

struct ImageData {
    int size; // int?
    unsigned int width;
    unsigned int height;
    int bitDepth;
    int colorType;
    int compressionMethod;
    int filterMethod;
    int interlaceMethod;

    bool isPLTE;
    int idatChunks;

    void printData();
};

class PNGParser
{
public:
    PNGParser(std::string fileName);

    void parseImage();

    void createAnonymizeImage();
    void showImage();
    void showAnonymizedImage();
    void printImageBytes();
    void printImageData();

private:
    ImageData imageData;

    void readHeader();
    void readIHDR();
    void readPLTE();
    void readIDAT();
    void readIEND();

    int readNextByte(unsigned int& index);
    unsigned int readNext4Bytes(unsigned int& index);

    void readImageBytes();
    void printBytesAsDecNumbers();
    void printBytesAsHexNumbers();
    void printBytesAsChars();

    unsigned int concatenate4Bytes(
        unsigned char b1,
        unsigned char b2,
        unsigned char b3,
        unsigned char b4
    );

    std::string fileName;
    std::vector<unsigned char> imageBytes;
    std::vector<unsigned char> anonedImageBytes;
};
