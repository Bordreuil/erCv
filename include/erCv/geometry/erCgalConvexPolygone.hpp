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
//#ifndef _ER_CGAL_POLYGON_2_HPP_
//#define _ER_CGAL_POLYGON_2_HPP_
#ifndef _ERCV_CGAL_CONVEX_HULL_HPP_
#define  _ERCV_CGAL_CONVEX_HULL_HPP_
#include "erCgalBase.hpp"
#include <CGAL/Polygon_2.h>
#include <erCv/geometry/erGeometricalCharacteristics.hpp>


typedef CGAL::Polygon_2<K> Polygon_2;
typedef Polygon_2::Vertex_iterator Polygon_vertex_iterator;

template< class Container, class Container2>
void convex_hull( Container bgraphSegments, Container2& cgalPoint)
{		    
  cgalPoint =  erGeometryExtractConvexPolygon( bgraphSegments.begin(), bgraphSegments.end());
}
  


#endif
