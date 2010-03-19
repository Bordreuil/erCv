
/** @file erCvCgal.hpp 
  \brief Fichier contenant les transfert des structures ou objet d OpenCv
  vers CGAL
  @package erCv
*/
#ifndef _MY_ERCVCGAL_HPP_
#define _MY_ERCVCGAL_HPP_


#include <erCv/geometry/erCgalBase.hpp>
//#include <erCv/erCvBase.hpp>
#include <vector>




/**
   Permet de transferer un point d opencv de n importe quel type
   vers le point defini dans Cgal (erCgalBase.hpp
 */
template<typename cvPoint>
CgPoint CvToCg( cvPoint& cv_pt)
{
  CgPoint pt( cv_pt.x, cv_pt.y);
  return pt;
};






/**
   Pour un iterateur d entree sur un conteneur de point d opencv
   on vient completer a partir de l output iterator le conteneur de sortie 
   des points de type cgal
*/
template< typename Container>
std::list<CgPoint> convertCvToCgalpoints( Container cvPoint)
{
  typedef typename Container::iterator Iterator;

  Iterator it;
  std::list<CgPoint> cgPoint;
  for( it = cvPoint.begin(); it != cvPoint.end(); it++)
    {
      cgPoint.push_back( CvToCg(*it));
    }
  return cgPoint;

};




#endif
