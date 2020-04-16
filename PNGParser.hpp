#pragma once

#include <array>
#include <string>
#include <vector>

struct tEXtChunk
{
    bool isContained;

    std::vector<std::string> keywords;
    std::vector<std::string> texts;

    void print();
};

struct IDATChunk
{
    int chunksNumber;
    std::vector<unsigned int> chunksSize;

    void print();
    void printChunksSize();
};

struct PLTEChunk
{
    std::vector<int> palette;

    bool isContained;

    void print();
    void printPalette();
};


struct ImageData
{
    int size; // int?
    unsigned int width;
    unsigned int height;
    int bitDepth;
    int colorType;
    int compressionMethod;
    int filterMethod;
    int interlaceMethod;

    bool isPLTE;

    void printData();

    PLTEChunk plte;
    IDATChunk idat;
    tEXtChunk tEXt;
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
    void printIDATChunks();
    void printPalette();
    void printtXTe();

private:
    ImageData imageData;

    void readHeader();
    void readIHDR();
    void readPLTE();
    void readIDAT();
    void readIEND();

    void readtEXt();

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
