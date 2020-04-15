FLAGS= -Wall -pedantic -std=c++17 -iquote inc 

parser.out: main.o PNGParser.o FFT.o
	g++ ${FLAGS}  main.o PNGParser.o FFT.o -o PNGParser `/usr/lib/x86_64-linux-gnu/ImageMagick-6.9.7/bin-q16hdri/Magick++-config --cppflags --cxxflags --ldflags --libs`

main.o: main.cpp PNGParser.hpp FFT.hpp
	g++ -c ${FLAGS}  main.cpp `/usr/lib/x86_64-linux-gnu/ImageMagick-6.9.7/bin-q16hdri/Magick++-config --cppflags --cxxflags --ldflags --libs`

PNGParser.o: PNGParser.hpp PNGParser.cpp
	g++ -c ${FLAGS}  PNGParser.cpp 

FFT.o: FFT.hpp FFT.cpp
	g++ -c ${FLAGS}  FFT.cpp `/usr/lib/x86_64-linux-gnu/ImageMagick-6.9.7/bin-q16hdri/Magick++-config --cppflags --cxxflags --ldflags --libs`
