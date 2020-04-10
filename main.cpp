#include "PNGParser.hpp"

#include <iostream>

int main()
{
    std::string fileName{"example.png"};
    PNGParser parser{fileName};

    parser.printBytesAsInt();
    parser.printBytesAs4ByteInt();
    //    parser.showImage(); moze nie dzialac
}
