#include "erCvFilters.hpp"
#include "erPredicates.hpp"
#include "erCvExtract.hpp"
#include "erCvToCgal.hpp"
#include "erCgalAlphaShape2.hpp"
#include<list>
#include<iterator>
int main(){
  erImage er    = erLoadImage("pos1_cuadro.bmp");
  erShowImage("base Image",&er);
  erImage bw    = erConvertToBlackAndWhite(&er);
  erImage ercan = erSmoothAndCanny(bw,1,5);
  erShowImage("after Canny",&ercan);
  IsEqualTo is_equal_255(255);
  std::list<CvPoint2D32f> cvPts;
  erExtractPoints(&ercan,cvPts,is_equal_255);
  std::list<Point_2> cgalPts;
  cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));
  Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(10.));
  return 0;
};
