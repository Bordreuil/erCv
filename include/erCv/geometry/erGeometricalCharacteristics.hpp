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
