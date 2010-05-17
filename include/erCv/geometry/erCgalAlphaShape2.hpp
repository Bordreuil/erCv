#ifndef _ER_CGAL_ALPHA_SHAPES_2_HPP_
#define _ER_CGAL_ALPHA_SHAPES_2_HPP_

#include "erCgalBase.hpp"
#include <CGAL/algorithm.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h>


typedef CGAL::Alpha_shape_vertex_base_2<K> Vb;
typedef CGAL::Alpha_shape_face_base_2<K>  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation_2;

typedef CGAL::Alpha_shape_2<Triangulation_2>  Alpha_shape_2;
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator;



struct erAlphaP
{
  double alpha;       /** < Value of parameter alpha to AlphaShape */
};


/* 
   "AlphaShape Regular" permet de créer des courbes fermes construites sur des segments non conectes, sur les contours detectés 
   par le traitement d'image. L'algorithme place les segments sur use une triangulation de L'Aunneay pour Le dites pointes sont
   definies sur erCgalBase.hpp.
*/
template < class Container, class Container2 >
void alpha_edges_user( Container cgalPoints, Container2& cgalSegmts, erAlphaP* param)
{
  double alfa;
  //std::list<CgSegmt> cgSegment;
  typedef typename Container::iterator it;
  int ok =1;
  while(ok)
    {
      std::cout << std::endl;
      std::cout << "Value of alpha parameter to Alpha Shape (double v | v>0) ";
      std::cin >> alfa;
      std::cout << std::endl;
      Alpha_shape_2 A( cgalPoints.begin(), cgalPoints.end(), CgalFTrai(alfa));
      for(Alpha_shape_edges_iterator it =  A.alpha_shape_edges_begin(); it != A.alpha_shape_edges_end(); ++it)
	{
	  cgalSegmts.push_back( A.segment(*it));
	}
      ok = 0;
    }
  param->alpha = alfa;
  //return cgSegment;
}




template < class Container, class Container2 >
void alpha_edges( Container cgalPoints, Container2& cgalSegmts, erAlphaP* param)
{
  double alfa = param->alpha;
  typedef typename Container::iterator it;
  
  Alpha_shape_2 A( cgalPoints.begin(), cgalPoints.end(), CgalFTrai(alfa));
  //std::list<CgSegmt> cgSegment;
  for(Alpha_shape_edges_iterator it =  A.alpha_shape_edges_begin(); it != A.alpha_shape_edges_end(); ++it)
    {
      cgalSegmts.push_back( A.segment(*it));
    }
  
  //return cgSegment;
}


#endif
