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
std::list<CgalPoint> erGeometryExtractConvexPolygon(InputSegmentIterator debut,InputSegmentIterator fin)
{
  CDT cdt ;
  std::list<CgalPoint> result;
  for( InputSegmentIterator icg=debut;icg!=fin;icg++)
    {
      cdt.insert_constraint(icg->source(),icg->target());
    };

  CDT::Vertex_handle v_inf = cdt.infinite_vertex();
  
  CDT::Face_circulator fc  = cdt.incident_faces(v_inf);
  CDT::Face_circulator fi=fc;
  CGAL_For_all(fc,fi)
    {
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
double getArea(InputGeoObjectIterator debut,InputGeoObjectIterator fin)
{
  double area(0.);
  for(;debut!=fin;debut++)
    {
      area+=debut->area();
    };
  return area;
};
#endif
