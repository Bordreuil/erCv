#include<erCv/erCvFiltersParams.hpp>

erSmootP::erSmootP():size(7),type(BLUR){};

erSmootP::erSmootP(SmoothType st,int si):size(si),type(st){};

erCannyP::erCannyP():trh1(150),trh2(150){};

erCannyP::erCannyP(int t1,int t2):trh1(t1),trh2(t2){};


erAdThrP::erAdThrP():type(THRESH_BINARY),adpt(AM_MEAN),trhP(10),neig(7),trh0(51){};
erAdThrP::erAdThrP(AdaptiveThresholdType tt,AdaptiveMethodType mt ,int thrp,int neig,int thr0):
  type(tt),adpt(mt),trhP(thrp),neig(neig),trh0(thr0){};



std::ostream& operator << (std::ostream& o,const erSmootP es)
{
  o << "** Begin Smooth Parameter : \n";
  o << "\tSize\t:\t" << es.size << std::endl;
  o << "\tType\t:\t" << es.type << std::endl;
  o << "** End Smooth Parameter------\n";
  return o;
};

std::ostream& operator << (std::ostream& o,const erCannyP ec)
{
  o << "** Begin Canny Parameter : \n";
  o << "\tThreshold 1\t:\t" << ec.trh1 << std::endl;
  o << "\tThreshold 2\t:\t" << ec.trh2 << std::endl;
  o << "** End Canny Parameter------\n";

  return o;
};
std::ostream& operator << (std::ostream& o,const erAdThrP ea)
{
  o << "** Begin Adaptive Threshold Parameter : \n";
  o << "\tAdaptive Threshold Type\t:\t" << ea.type << std::endl;
  o << "\tAdaptive Method Type\t:\t"    << ea.adpt<< std::endl;
  o << "\tThreshold Parameter\t:\t" << ea.trhP << std::endl;
  o << "\tNeighbour\t\t:\t"    << ea.neig<< std::endl;
  o << "\tThreshold\t\t:\t"    << ea.trh0<< std::endl;
  o << "** End Adaptive Threshold Parameter------\n";
  
  return o;
};
