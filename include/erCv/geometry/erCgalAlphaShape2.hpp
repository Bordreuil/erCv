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
#ifndef _ER_CGAL_ALPHA_SHAPES_2_HPP_
#define _ER_CGAL_ALPHA_SHAPES_2_HPP_

#include "erCgalBase.hpp"
#include <CGAL/algorithm.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Alpha_shape_2.h>

#include<erCv/geometry/geometricalParams.hpp>

typedef CGAL::Alpha_shape_vertex_base_2<K> Vb;
typedef CGAL::Alpha_shape_face_base_2<K>  Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds> Triangulation_2;

typedef CGAL::Alpha_shape_2<Triangulation_2>  Alpha_shape_2;
typedef Alpha_shape_2::Alpha_shape_edges_iterator Alpha_shape_edges_iterator;






/* 
   "AlphaShape Regular" permet de créer des courbes fermes construites sur des segments non conectes, sur les contours detectés 
   par le traitement d'image. L'algorithme place les segments sur use une triangulation delaunnay pour Le dites pointes sont
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

  for(Alpha_shape_edges_iterator it =  A.alpha_shape_edges_begin(); it != A.alpha_shape_edges_end(); ++it)
    {
      cgalSegmts.push_back( A.segment(*it));
    }
  

}


#endif
