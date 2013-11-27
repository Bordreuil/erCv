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

//namespace bp = boost::python;

extern void export_erCvFiltersParams();
extern void export_erCvSegmentationParams();
extern void export_erCvTools();
extern void export_erCvBase();
extern void export_erCvAnalysis();
extern void export_erMacroDropAnalysis();
extern void export_erMetalTransfertAnalysis();
extern void export_erMultiMetalTransfertAnalysis();
extern void export_erCreatisAnalysis();
extern void export_erSolidificationAnalysis();
extern void export_erWireAnalysis();
extern void export_erWeldPoolAnalysis();
extern void export_erGeometricalParams();
extern void export_erCvSegmentation();
extern void export_erCalibration();
extern void export_erGeometricalProperties();
extern void export_erSkeleton();
extern void export_erChainPoints();
extern void export_erWeldPoolSolidificationAnalysis();
extern void export_erLaserPrototypageAnalysis();

BOOST_PYTHON_MODULE(PyerCv)
{ 
  boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
  export_erGeometricalParams();
  export_erCvFiltersParams();
  export_erCvSegmentationParams();
  export_erCvSegmentation();
  export_erCvAnalysis();
  export_erCvTools();
  export_erCvBase();
  export_erCalibration();
  export_erGeometricalProperties();
  export_erSkeleton();
  export_erChainPoints();
  export_erMacroDropAnalysis();
  export_erMetalTransfertAnalysis();
  export_erMultiMetalTransfertAnalysis();
  export_erCreatisAnalysis();
  export_erSolidificationAnalysis();
  export_erWireAnalysis();
  export_erWeldPoolAnalysis();
  export_erWeldPoolSolidificationAnalysis();
  export_erLaserPrototypageAnalysis();
};
