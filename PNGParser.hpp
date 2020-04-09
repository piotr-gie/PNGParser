#pragma once

#include <string>
#include <vector>

class PNGParser
{
public:
    PNGParser(std::string fileName);
    void printBytesAsInt();
    void showImage();

private:
    void readImage();

    std::string fileName;
    std::vector<int> bytes;
};
