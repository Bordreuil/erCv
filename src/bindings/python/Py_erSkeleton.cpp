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
#include<boost/shared_ptr.hpp>
#include "boost/python.hpp"
#include<erCv/geometry/erCgalBase.hpp>
#include<CGAL/Polygon_with_holes_2.h>
#include<CGAL/create_straight_skeleton_from_polygon_with_holes_2.h>

typedef CGAL::Polygon_2<K>            Polygon ;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes ;
typedef CGAL::Straight_skeleton_2<K>  Straight_skeleton ;
typedef Straight_skeleton::Halfedge_const_iterator Halfedge_const_iterator ;
typedef Straight_skeleton::Halfedge_const_handle   Halfedge_const_handle ;
typedef boost::shared_ptr<Straight_skeleton> Straight_skeleton_ptr ;



namespace bp = boost::python;

void erGetSkeleton(boost::python::numeric::array arr,bp::list& skeleton)
{
  
  const bp::tuple& shapePts   = bp::extract<bp::tuple>(arr.attr("shape"));
  
  int          nbLig      = bp::extract<int>(shapePts[0]);
  int          nbDim      = bp::extract<int>(shapePts[1]);
 
  
  assert(nbDim == 2);
 
  std::vector<CgalPoint> points;
  for(int i=0;i<nbLig;i++)
  {

    double x1 =  bp::extract<double>(arr[i][0]);
    double y1 =  bp::extract<double>(arr[i][1]);
   
    points.push_back(CgalPoint(x1,y1));
   };

  Polygon input(points.begin(),points.end());
  Straight_skeleton_ptr ss = CGAL::create_interior_straight_skeleton_2(input);


  
  for(Halfedge_const_iterator hit = ss->halfedges_begin(); hit != ss->halfedges_end(); ++hit)
  {
    Halfedge_const_handle h = hit ;
    boost::python::list seg;
    if( h->is_bisector() && ((h->id()%2)==0) && !h->has_infinite_time() && !h->opposite()->has_infinite_time() )
    { 
      seg.append(h->vertex()->point().x()) ;
      seg.append(h->vertex()->point().y());
      seg.append(h->opposite()->vertex()->point().x());
      seg.append(h->opposite()->vertex()->point().y() );
      skeleton.append(seg);
    }
  }

};
void export_erSkeleton()
{
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    def("erGetSkeleton",&erGetSkeleton,
	"Permet d obtenir le squelette d un polygone");
 
};
