#include "PNGParser.hpp"
#include "FFT.hpp"

#include <iostream>
#include <Magick++.h>

using namespace Magick;

void showMenu();

int main(int argc, char** argv)
{
    InitializeMagick(*argv);
    const std::string defaultFileName{"PNGImages/lena.png"};
    std::string fileName{defaultFileName};
    if (argc > 1) {
        fileName = argv[1];
    }

    PNGParser parser{fileName};
    FourierTransform fft(fileName);

    parser.createAnonymizeImage();

    showMenu();
    int userInput{1};
    while(userInput != 0) {

        std::cout << std::endl;
        std::cout << "Your choice (1 - show menu): ";
        std::cin >> userInput;
        std::cout << std::endl;

        switch(userInput){
            case 0:
                break;

            case 1:
                showMenu();
                break;

            case 2:
                parser.printImageData();
                break;

            case 3:
                parser.printImageBytes();
                break;

            case 4:
                fft.showMagnitude();
                break;

            case 5:
                fft.showPhase();
                break;

            case 6:
                parser.showImage();
                break;

            case 7:
                parser.showAnonymizedImage();
                break;

            case 8:
                parser.printIDATChunks();
                break;

            case 9:
                parser.printPalette();
                break;

            case 10:
                parser.printtXTe();
                break;

            default:
                std::cout << "There is no such option" << std::endl;
                break;
        }
    }
}

void showMenu()
{
    std::cout << " - - - MENU - - - " << std::endl;
    std::cout << "1 - show menu" << std::endl;
    std::cout << "2 - show image data" << std::endl;
    std::cout << "3 - show image bytes" << std::endl;
    std::cout << "4 - show magnitude" << std::endl;
    std::cout << "5 - show phase" << std::endl;
    std::cout << "6 - show image" << std::endl;
    std::cout << "7 - show anonymized image" << std::endl;
    std::cout << "8 - show IDAT chunks" << std::endl;
    std::cout << "9 - show Palette" << std::endl;
    std::cout << "10 - show tEXT chunk" << std::endl;
    std::cout << std::endl;
    std::cout << "0 - exit" << std::endl;
}
