#include "PNGParser.hpp"

#include <iostream>

int main()
{
    std::string fileName{"PNGImages/example1.png"};
    PNGParser parser{fileName};

    parser.printImageBytes();
    parser.printImageData();
    //    parser.showImage(); may not work
}
