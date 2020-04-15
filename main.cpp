#include "PNGParser.hpp"
#include "FFT.hpp"

#include <iostream>
#include <Magick++.h>

int main(int argc, char** argv)
{
    InitializeMagick(*argv);
    std::string fileName{"PNGImages/lena.png"};
    if (argc > 1) {
        fileName = argv[1];
    }

    PNGParser parser{fileName};

    // parser.printImageBytes();
    parser.printImageData();
    parser.createAnonymizeImage();
    
    // parser.showImage(); // xdg-open required
    // parser.showAnonymizedImage(); // xdg-open required
    FourierTransform fft(fileName);
    fft.showMagnitude();
    fft.showPhase();
}
