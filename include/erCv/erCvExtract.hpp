#ifndef _ER_CV_EXTRACT_HPP_
#define _ER_CV_EXTRACT_HPP_
/** \addtogroup cv_group */
/*@{*/
/**
   Permet d extraire des points d une image en niveau de gris et les placer dans 
   un container suivant un critere. Une liste de critere est disponible dans
   erPredicates.hpp
   \param IplImage * : une image 
   \param Container  : Un container STL (supportant le back_inserter ) de Point d OpenCv
   \param Criteria   :  un critere de selection des points
 */
template<typename Container,typename Criteria>
void erExtractPoints(IplImage * im,Container & pts,Criteria crit)
{  
  typedef typename Container::value_type CvPoint;
  int a;
   for( int y = 0; y < im->height; y++)
    {
      int* ptr = (int*)(im->imageData + y*im->widthStep );
      for( int x = 0; x < im->width; x++)
	{
	  a = ptr[x];
	  if(crit(a))
	    { CvPoint p;
	      p.x = x;p.y = y;
	      pts.push_back(p); 
	    }
	}
    }
};
/*@}*/
#endif
