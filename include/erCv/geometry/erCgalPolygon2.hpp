#ifndef _ER_CGAL_POLYGON_2_HPP_
#define _ER_CGAL_POLYGON_2_HPP_

#include "erCgalBase.hpp"
#include <CGAL/Polygon_2.h>

/** \addtogroup cgal */
/** \brief definition du polygone de cgal */
/*@{*/
#include "erCgalBase.hpp"
#include<CGAL/Polygon_2.h>

typedef CGAL::Polygon_2<K> Polygon_2;


template< class Container>
void polygon_creation_user( Container unkown)
{
  std::list<CgalPoint> cgalPoints;
  cgalPoints = erCgalConvertSegmentToPoint( unkown); 
  Polygon_2 P( cgalPoints.begin(), cgalPoints.end());    
}


template< typename Container>
std::list<CgalPoint> erCgalConvertSegmentToPoint( Container bgraphSgm)
{
  typename Container::iterator itContainer;
  std::list< CgalPoint> cgalPts;
  std::list<CgalPoint>::iterator itcgalPts;

  cgalPts.push_back( bgraphSgm.begin()->source);
  cgalPts.push_back( bgraphSgm.begin()->target); 

  for( itContainer = bgraphSgm.begin()+1, itContainer =! bgraphSgm.end(), itContrainer++)
    {
      itcgalPts = erFindCgalPoint( cgalPts.begin(), cgalPts.end(), itContainer->source);
      if( itcgalPts == cgalPts.end())
	{
	  cgalPts.push_back( itContainer->source);
	}
      itcgalPts = erFindCgalPoint( cgalPts.begin(), cgalPts.end(), itContainer->target);
      if( itcgalPts == cgalPts.end())
	{
	  cgalPts.push_back( itContainer->target);
	}
    }  
  return cgalPts;
}



template< typename Iterator>
Iterator erFindCgalPoint( Iterator p1, Iterator p2, CgalPoint punto)
{
  while( p1 != p2)
    {
      if( p1.operator == (punto))
	{
	  return p1;
	  break;
	}
      p1++;
    }
  return p2;
}

/*@}*/
#endif
