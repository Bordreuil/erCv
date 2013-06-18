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

#include "boost/python.hpp"
#include "pyublas/numpy.hpp"
#include<erCv/geometry/erCgalBase.hpp>
#include <erCv/geometry/erGeometricalCharacteristics.hpp>
#include<CGAL/linear_least_squares_fitting_2.h>

namespace bp = boost::python;

void erGetPrincipalAxis(boost::python::numeric::array arr,bp::list& point,bp::list& vector)
{
  
  const bp::tuple& shapePts   = bp::extract<bp::tuple>(arr.attr("shape"));
  
  int          nbLig      = bp::extract<int>(shapePts[0]);
 
  int          nbDim      = bp::extract<int>(shapePts[1]);
 
  //std::cout << "nb lig:" << nbLig << std::endl;
  
  assert(nbDim == 4);
 
  std::list<CgalSegmt> segs;
  for(int i=0;i<nbLig;i++)
  {

    double x1 = bp::extract<double>(arr[i][0]);
    double y1 =  bp::extract<double>(arr[i][1]);
    double x2 =  bp::extract<double>(arr[i][2]);
    double y2 =  bp::extract<double>(arr[i][3]);
    CgalPoint source(x1,y1);
    CgalPoint target(x2,y2);
    CgalSegmt seg(source,target);
    segs.push_back(seg);
   };
  //std::cout << "before :: triangs\n";
  std::list<CgalTrian> triangs=erGeometryExtractTriangles(segs.begin(),segs.end());
  //std::cout << "Taille trian:" << triangs.size() << std::endl;
  CgalLine  line;
  CgalPoint pt;
  CgalFTrai fit  = linear_least_squares_fitting_2(triangs.begin(),triangs.end(),line,pt,CGAL::Dimension_tag<2>());
  CgalVect vect  = line.to_vector();
  point.append(pt.x());point.append(pt.y());
  vector.append(vect.x());vector.append(vect.y());
};
void export_erGeometricalProperties()
{
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    def("erGetPrincipalAxis",&erGetPrincipalAxis,
	"Permet d obtenir l axe principale d un ensemble de segment");
 
};
