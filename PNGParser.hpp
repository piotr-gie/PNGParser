#pragma once

#include <string>
#include <vector>

class PNGParser
{
public:
    PNGParser(std::string fileName);
    void printBytesAsInt();
    void showImage();
  void printBytesAs4ByteInt();  

private:
    void readImage();

    std::string fileName;
    std::vector<int> bytes;
};
