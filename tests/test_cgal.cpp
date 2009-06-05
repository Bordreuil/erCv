#include "erCvToCgal.hpp"
#include "erCgalPolygon2.hpp"
#include<iterator>
#include<iostream>

int main()
{
  std::vector<CvPoint2D32f> cvPts;
  std::vector<Point_2>      cgalPts;
  for(int i=0;i<20;i++){cvPts.push_back(cvPoint2D32f(rand(),rand()));}
  
  cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));

  std::cout << cgalPts[7] << std::endl;
};
