FLAGS= -Wall -pedantic -std=c++17 -iquote inc
Magick++Path= /usr/lib/x86_64-linux-gnu/ImageMagick-6.9.7/bin-q16hdri/Magick++-config
Magick++Flags= ${Magick++Path} --cppflags --cxxflags --ldflags --libs

parser.out: main.o PNGParser.o FFT.o
	g++ ${FLAGS}  main.o PNGParser.o FFT.o -o PNGParser `${Magick++Flags}`

main.o: main.cpp PNGParser.hpp FFT.hpp
	g++ -c ${FLAGS}  main.cpp `${Magick++Flags}`

PNGParser.o: PNGParser.hpp PNGParser.cpp
	g++ -c ${FLAGS}  PNGParser.cpp

FFT.o: FFT.hpp FFT.cpp
	g++ -c ${FLAGS}  FFT.cpp `${Magick++Flags}`
