// Copyright Universite Montpellier 2/CNRS 
// Contributor(s) : 
//         Edward Romero 
//         Cyril Bordreuil
// Contact: cyril.bordreuil@univ-montp2.fr
// 
// This software is a computer program whose purpose is to [describe
//  functionalities and technical features of your software].
//
// This software is governed by the CeCILL license under French law and
// abiding by the rules of distribution of free software.  You can  use, 
// modify and/ or redistribute the software under the terms of the CeCILL
// license as circulated by CEA, CNRS and INRIA at the following URL
// "http://www.cecill.info". 
//
// As a counterpart to the access to the source code and  rights to copy,
// modify and redistribute granted by the license, users are provided only
// with a limited warranty  and the software's author,  the holder of the
// economic rights,  and the successive licensors  have only  limited
// liability. 
//
// In this respect, the user's attention is drawn to the risks associated
// with loading,  using,  modifying and/or developing or reproducing the
// software by the user in light of its specific status of free software,
// that may mean  that it is complicated to manipulate,  and  that  also
// therefore means  that it is reserved for developers  and  experienced
// professionals having in-depth computer knowledge. Users are therefore
// encouraged to load and test the software's suitability as regards their
// requirements in conditions enabling the security of their systems and/or 
// data to be ensured and,  more generally, to use and operate it in the 
// same conditions as regards security. 
// 
// The fact that you are presently reading this means that you have had
// knowledge of the CeCILL license and that you accept its terms.
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


template< class Container, class Container2>
void polygon_creation_user( Container cgalSegments, Container2& cgalPoints)
{
  std::list<CgalPoint> cgalPoints2;
  erAlignementSegmentContour( cgalSegments);
  cgalPoints2 = erCgalConvertSegmentToPoint( cgalSegments); 
  Polygon_2 P( cgalPoints2.begin(), cgalPoints2.end());    
  for( Polygon_vertex_iterator it = P.vertices_begin(); it != P.vertices_end(); ++it)
    {
      cgalPoints.push_back( *it);
    }		    
};









/*@}*/
#endif
