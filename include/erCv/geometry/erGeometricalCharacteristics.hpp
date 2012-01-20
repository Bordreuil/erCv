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
#ifndef _ERCV_GEOMETRICAL_CHARACTERISTICS_HPP_
#define  _ERCV_GEOMETRICAL_CHARACTERISTICS_HPP_

#include <erCv/geometry/erConstrainedTriangulation2.hpp>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Delaunay_mesher_2.h>
#include <CGAL/Delaunay_mesh_face_base_2.h>
#include <CGAL/Delaunay_mesh_size_criteria_2.h>

typedef CGAL::Triangulation_vertex_base_2<K> VVb;
typedef CGAL::Delaunay_mesh_face_base_2<K> VFb;
typedef CGAL::Triangulation_data_structure_2<VVb, VFb> CTds;
typedef CGAL::Constrained_Delaunay_triangulation_2<K, CTds> CgalDT;
typedef CGAL::Delaunay_mesh_size_criteria_2<CgalDT> Criteria;

template<typename InputSegmentIterator>
std::list< CgalTrian> erGeometryExtractTriangles( InputSegmentIterator debut, InputSegmentIterator fin)
{
  CDT cdt ;
  for( InputSegmentIterator icg=debut;icg!=fin;icg++)
    {
      cdt.insert_constraint(icg->source(),icg->target());
    };
 
  initializeID(cdt);
  discoverComponents(cdt);
  std::list<CgalTrian> triangs;
  CDT::All_faces_iterator deb=cdt.all_faces_begin();

  for(;deb!=cdt.all_faces_end();deb++)
    {
      if(deb->is_in_domain())
	{ CgalTrian tri=cdt.triangle(deb);
	  triangs.push_back(tri);
	}
    };
    return triangs;
};

template<typename InputSegmentIterator>
 std::list< CgalTrian> erGeometryExtractTrianglesWithMesh( InputSegmentIterator debut, InputSegmentIterator fin)
 {
   CgalDT cgadt ;
   for( InputSegmentIterator icg=debut;icg!=fin;icg++)
     {
       cgadt.insert_constraint(icg->source(),icg->target());
     };
   CGAL::refine_Delaunay_mesh_2(cgadt, Criteria(0.125, 2.));
   
   CgalDT::Finite_edges_iterator bed,nif;
   // std::cout << "Nbre de noeuds:" << cgadt.number_of_vertices() << std::endl;
   // int i;
   // std::cin >> i;
   bed=cgadt.finite_edges_begin();
   nif=cgadt.finite_edges_end();
   CDT cdt;
   for(;bed!=nif;bed++)
     {
       CDT::Vertex_handle  va = cdt.insert(bed->first->vertex(cgadt.cw(bed->second))->point());
       CDT::Vertex_handle  vb = cdt.insert(bed->first->vertex(cgadt.ccw(bed->second))->point());
       if(cgadt.is_constrained(*bed))
	 {
	   cdt.insert_constraint(va,vb);
	 }
     }

   initializeID(cdt);
   discoverComponents(cdt);
   std::list<CgalTrian> triangs;
   CDT::All_faces_iterator deb=cdt.all_faces_begin();

   for(;deb!=cdt.all_faces_end();deb++)
     {
       if(deb->is_in_domain())
   	{ CgalTrian tri=cdt.triangle(deb);
   	  triangs.push_back(tri);
   	}
    };
     return triangs;
 };

template<typename InputSegmentIterator>
std::list<CgalPoint> erGeometryExtractConvexPolygon(InputSegmentIterator debut,InputSegmentIterator fin)
{
  CDT cdt ;
  std::list<CgalPoint> result;
  int inc(0);
  for( InputSegmentIterator icg = debut; icg != fin; icg++)
    { //std::cout << inc++ << std::endl;
      cdt.insert_constraint(icg->source(),icg->target());
    };
 
  CDT::Vertex_handle v_inf = cdt.infinite_vertex();
  
  CDT::Face_circulator fc  = cdt.incident_faces(v_inf);
  CDT::Face_circulator fi=fc;
  
  
  CGAL_For_all(fc,fi)
    {
      //std::cout << inc++ << " tour dans cv hull" << std::endl; 
      int id_inf=fc->index(v_inf);
      CDT::Vertex_handle vp = fc->vertex(fc->cw(id_inf));
      result.push_back(vp->point());
    };
  // fc++;
  // int id_inf=fc->index(v_inf);
  //  CDT::Vertex_handle vp = fc->vertex(fc->cw(id_inf));
  //  result.push_back(vp->point());
  return result;

};


template<typename InputGeoObjectIterator>
double erGetArea(InputGeoObjectIterator debut,InputGeoObjectIterator fin)
{
  double area(0.);
  for(;debut!=fin;debut++)
    {
      area+=debut->area();
    };
  return area;
};
template<typename InputGeoObjectIterator>
double erGetAreaAxi(InputGeoObjectIterator debut,InputGeoObjectIterator fin,CgalPoint pt,CgalVect vect)
{
  double area(0.);
  for(;debut!=fin;debut++)
    { double local_area = debut->area();
      CgalPoint centre_triangle = CGAL::centroid(*debut);
      // std::cout << centre_triangle.x() - pt.x() << " " << centre_triangle.y()-pt.y() << std::endl;
      area+=local_area*3.14116*std::abs(centre_triangle.x() - pt.x());
    };
  return area;
};

#endif
