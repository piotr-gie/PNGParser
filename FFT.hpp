#include <Magick++.h>
#include <iostream> 
#include <vector>

using namespace std; 
using namespace Magick; 

class FourierTransform
{
  private:
  string fileName;
  
  public:
  FourierTransform(string fileName_);
  void showMagnitude();
  void showPhase();

};
