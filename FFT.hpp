#include <Magick++.h>
#include <iostream>
#include <vector>

class FourierTransform
{
  private:
  std::string fileName;

  public:
  FourierTransform(std::string fileName_);
  void showMagnitude();
  void showPhase();
};
