#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<list>
#include<fstream>
#include<iterator>

int main(){
  erImage er    = erLoadImage("ed20090619_3_02176.bmp");
  erShowImage("base Image",&er);
  erImage bw    = erConvertToBlackAndWhite(&er);
  erImage ercan = erSmoothAndCanny(bw,200,1);
  erShowImage("after Canny",&ercan);
  IsEqualTo is_equal_255(255);
  std::list<CvPoint2D32f> cvPts;
  erExtractPoints(&ercan,cvPts,is_equal_255);
  std::list<Point_2> cgalPts;
  cvPointsToCgal(cvPts.begin(),cvPts.end(),std::back_inserter(cgalPts));
  Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(10.));
  std::list<Segment_2> segments;
  alpha_edges( as2, std::back_inserter(segments));
  std::ofstream ot("edges.dat");
  std::list<Segment_2>::iterator  is;
  for(is=segments.begin();is!=segments.end();is++)
    {
      ot << *is << std::endl;
    };

  return 0;
};
