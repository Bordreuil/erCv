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
typedef Polygon_2::Vertex_iterator Polygon_vertex_iterator;


template< class Container>
void polygon_creation_user( Container cgalSegments, Container cgalPoints )
{
  std::list<CgalPoint> cgalPoints;
  erAlignementSegmentContour( cgalSegments);
  cgalPoints = erCgalConvertSegmentToPoint( cgalSegments); 
  Polygon_2 P( cgalPoints.begin(), cgalPoints.end());    
  for( Polygon_vertex_iterator it = P.vertices_begin(); it != P.vertices_end(); ++it)
    //  {
    //  cgalPoints.push_back( P.

};


template< typename Container>
void erAlignementSegmentContour( Container &seg)
{
  typename Container::iterator itseg, itseg_chain, itseg_chain2;
  Container seg_chain;
  itseg = seg.begin( );
  seg_chain.push_back( *itseg);
  do 
    { 
      itseg_chain2 = seg_chain.end();
      CgalPoint prt = (*itseg_chain2).target();
      itseg_chain = erFindCgalSegment( seg.begin( ), seg.end( ), prt); 
      seg_chain.push_back( *itseg_chain);
    }
  while( (*itseg_chain).target() == (*itseg).source());
  seg = seg_chain;
};


template< typename Container>
std::list<CgalPoint> erCgalConvertSegmentToPoint( Container bgraphSgm)
{
  typename Container::iterator itContainer, itContainer2;
  std::list< CgalPoint> cgalPts;
  std::list<CgalPoint>::iterator itcgalPts;

  cgalPts.push_back( (*bgraphSgm.begin()).source());
  //cgalPts.push_back( bgraphSgm.begin()->target); 
  itContainer2 = bgraphSgm.begin();
  itContainer2++;
  for( itContainer = itContainer2; itContainer != bgraphSgm.end(); itContainer++)
    {
      itcgalPts = erFindCgalPoint( cgalPts.begin(), cgalPts.end(), (*itContainer).source());
      if( itcgalPts == cgalPts.end())
	{
	  cgalPts.push_back( (*itContainer).source());
	}
      //itcgalPts = erFindCgalPoint( cgalPts.begin(), cgalPts.end(), itContainer->target);
      //if( itcgalPts == cgalPts.end())
      //{
      //  cgalPts.push_back( itContainer->target);
      //}
    }  
  return cgalPts;
};



template< typename Iterator>
Iterator erFindCgalSegment( Iterator p1, Iterator p2, CgalPoint punto)
{
  while( p1 != p2)
    {
      if( ( (*p1).source()).operator == (punto))
	{
	  return p1;
	  break;
	}
      if( ( (*p1).target()).operator == (punto))
	{
	  *p1 = (*p1).opposite();
	  return p1;
	  break;
	}
      p1++;
    }
  return p2;
};


template< typename Iterator>
Iterator erFindCgalPoint( Iterator p1, Iterator p2, CgalPoint punto)
{
  while( p1 != p2)
    {
      if( (*p1).operator == (punto))
	{
	  return p1;
	  break;
	}
      p1++;
    }
  return p2;
};

/*@}*/
#endif
