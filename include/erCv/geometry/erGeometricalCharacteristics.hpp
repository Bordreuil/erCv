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
  fc++;
   int id_inf=fc->index(v_inf);
    CDT::Vertex_handle vp = fc->vertex(fc->cw(id_inf));
    result.push_back(vp->point());
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
