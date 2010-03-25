#include<erCv/erCvFiltersParams.hpp>

erSmootP::erSmootP():size(7),type(BLUR){};

erSmootP::erSmootP(SmoothType st,int si):size(si),type(st){};

erCannyP::erCannyP():trh1(150),trh2(150){};

erCannyP::erCannyP(int t1,int t2):trh1(t1),trh2(t2){};


erAdThrP::erAdThrP():type(THRESH_BINARY),adpt(AM_MEAN),trhP(10),neig(7),trh0(51){};
erAdThrP::erAdThrP(AdaptiveThresholdType tt,AdaptiveMethodType mt ,int thrp,int neig,int thr0):
  type(tt),adpt(mt),trhP(thrp),neig(neig),trh0(thr0){};


