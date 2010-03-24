#include<erCv/erCvTools.hpp>


erImageIncrement::erImageIncrement():current(0),base(0),delta(0),every(0){};


erImageIncrement::erImageIncrement(int incbase,int incD,int every):current(0),base(incbase),
					                          delta(incD),every(every){};


int erImageIncrement::inc()
{
    current+=base;
    if(current > every)
      {
      current=0;
      return delta;
      };
    return base;
};
