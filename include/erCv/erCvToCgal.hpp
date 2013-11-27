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
   vers le point defini dans Cgal (la class CgalPoint est definie en erCgalBase.hpp)
 */
template<typename cvPoint>
CgalPoint CvToCgal( cvPoint cv_pt )
{ 
  CgalPoint pt( cv_pt.x, cv_pt.y);
  return pt;
};






/**
   Pour un iterateur d entree sur un conteneur de point d opencv
   on vient completer a partir de l output iterator le conteneur de sortie 
   des points de type cgal
*/
template< typename Container, typename Container2>
void convertCvToCgalpoints( Container cvPoint, Container2& cgalPoint)
{
  typedef typename Container::iterator Iterator;

  Iterator it;
  //std::list<CgPoint> cgPoint;
  for( it = cvPoint.begin(); it != cvPoint.end(); it++)
    {
      cgalPoint.push_back( CvToCgal(*it));
    }
  //return cgPoint;

};




#endif
