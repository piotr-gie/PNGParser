#include "FFT.hpp"
#include <Magick++.h>
#include <iostream> 
#include <vector>

using namespace std; 
using namespace Magick; 


FourierTransform::FourierTransform(string fileName_) : fileName{fileName_}
{
  
}

void FourierTransform::showMagnitude()
{
  Image image;
  vector<Image> FFTresult(2);
try { 
    // Read a file into image object
    image.read(fileName);

    // Perform FFT and save results to FFTresult vector of two images (Magnitude and Phase)
    forwardFourierTransformImage(&FFTresult,image);
    //Make magnitude visible by using logarythmic scale
    Pixels view(FFTresult[0]);
    cout<<FFTresult[0].columns();
    PixelPacket *pixels = view.get(0,0,FFTresult[0].columns(),FFTresult[0].rows()); 
    for(size_t i=0; i<FFTresult[0].columns()*FFTresult[0].rows();i++)
  {
    
        pixels->red=5000*log(pixels->red);//log(pixels->red*20+1.0)/log(20+1.0);
        pixels->green=5000*log(pixels->green);//log(pixels->green*20+1.0)/log(20+1.0);
        pixels->blue=5000*log(pixels->blue);//log(pixels->blue*20+1.0)/log(20+1.0);
        pixels++;
  }  

    view.sync();

    cout<<"Magnitude:"<<endl;
    FFTresult[0].display();
    // Write FFT result images to file
    FFTresult[0].write( "Magnitude.png" );
  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl; 
    } 
}

void FourierTransform::showPhase()
{
  Image image;
  vector<Image> FFTresult(2);
try { 
    // Read a file into image object
    image.read(fileName);

    // Perform FFT and save results to FFTresult vector of two images (Magnitude and Phase)
    forwardFourierTransformImage(&FFTresult,image);

    // Write FFT rusult images to file
    FFTresult[1].write( "Phase.png" );
    cout<<"Phase:"<<endl;
    FFTresult[1].display();
  } 
  catch( Exception &error_ ) 
    { 
      cout << "Caught exception: " << error_.what() << endl;
    } 
}


