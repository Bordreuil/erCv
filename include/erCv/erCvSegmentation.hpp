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

#ifndef _ER_CV_SEGMENTATION_HPP_
#define _ER_CV_SEGMENTATION_HPP_
#include "erCvBase.hpp"
#include "erCvSegmentationParams.hpp"
#include "erCvFilters.hpp"
#include "cv.h"
#include <opencv2/legacy/legacy.hpp>
#include<string>

/** \defgroup segmentation erCvSegmentation */
/** \brief interface d'algorithmes de segmentation openCV dans erCv */



/** \addtogroup segmentation
    /*@{*/

/** \brief
    Permmet de substraire une image A sur autre B d equal type et dimension (A-B=C)
*/
void erCvDifferencing( IplImage*, IplImage*);


/** \brief
    Permet de segmenter une image a partir d un echantillon ou zone template dans l image (voir erCvTemplateUser)
*/
IplImage* erCvTemplate( IplImage*, erTemplP*);


/** \brief
    Permet d'incrementer le contraste dans l image, en effectuant une normalizacion de l histograme
*/
void erCvEqualizeHist( IplImage*, erEqualP*);


/** \brief
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
 */
void erCvPyramid( IplImage*, erPyramP*);


/** \brief
    Permet de couvrir les zones blanches (au desous du seuil) entoure par une zone noir (au dessus du seuil)
*/
void erWhiteBlobCorrection( IplImage*, erWhitBP*);
/** \brief
    Permet de couvrir les zones blanches (au desous du seuil) entoure par une zone noir (au dessu du seuil)
*/
void erWhiteBloborCorrection(std::string);
void erWhiteBloborCorrection(IplImage*);
//void erWhiteBlobDelete(std::string,erWhitBP);

#endif
