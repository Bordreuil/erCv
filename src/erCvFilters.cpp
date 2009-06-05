#include "erCvFilters.hpp"
#include <iostream>

erImage erSmoothAndCanny(erImage pic1, int A=1, int B=2)
{
  /* Test picture is gray: only one channel */
  if(pic1.nChannels != 1)
    {
      std::cout << "Picture must be have only one channel" << std::endl;
      return erImage();
    }
  else
    { 
      cvSmooth( &pic1, &pic1, CV_BLUR, 5, 5, 0, 0);
      cvCanny( &pic1, &pic1, (float)A*10., (float)B*10., 5); 
      return &pic1;
    }
};
