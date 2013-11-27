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
//#include "boost/python.hpp"
//#include "pyublas/numpy.hpp"
#include<erCv/bindings/python/erNumpyTools.hpp>


erImage erConvertNumpyArray16ToImage(pyublas::numpy_array<unsigned short>& arr)
{
    const npy_intp* dims = arr.dims();
    int ncol = dims[0];
    int nlig = dims[1];
    
    unsigned short* storage = arr.data();

    
    IplImage* im = cvCreateImage(cvSize(nlig,ncol),IPL_DEPTH_8U,3);
    for(int i=0;i<ncol;i++)
       {
	  for(int j=0;j < nlig;j++)
	  { 

	    unsigned short va = storage[j+i*nlig]*256/65536;
	    CvScalar val      = cvScalarAll(va);
	    cvSet2D(im,i,j,val);
	  };

      }; 

    erImage eim(im);
    return eim;
};
