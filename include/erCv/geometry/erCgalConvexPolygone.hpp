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
