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
#ifndef _ER_CV_SEGMENTATION_USER_HPP_
#define _ER_CV_SEGMENTATION_USER_HPP_
#include "erCv/erCvSegmentationParams.hpp"
#include "erCv/erCvBase.hpp"
#include "cv.h"



/** \brief
    Permmet de segmenter une image a partir d un echantillon ou zone template dans l image, en utilisant une criter de comparaison avec le reste de l image
    La dite zone est choisit par l usager
*/
IplImage* erCvTemplateUser( IplImage*, erTemplP*, bool with_trackbar = false);


/** \brief
    Une fois determine un type d histograme base sur le format coulor de l image. La fonction permmet de segmenter l image a partir d un echantillon choisit par l usager
    Le type d histograme ainsi comment l echantillon est choisit par l usager
*/
IplImage* erCvCallBackPatchProjectUser( IplImage*, erCallBP*, bool with_trackbar = false );



/** \brief
    Permmet de normalizer l intensite et incremente le contraste en equalisant l histograme d une image des niveaux de gris
*/
void erCvEqualizeHistUser( IplImage*, erEqualP*);


/** \brief
    Permet d effectuer un filtrage de l image en reagroupant les pixels dans clusters 
    d interet et en effectuant des liaisons entre eux
*/
void erCvPyramidUser( IplImage*, erPyramP*, bool with_trackbar = false);

/** \brief
    Permmet d identifier les contours dans une image en binaire
 */
void erCvFindContours( IplImage*, erFindcP*, bool with_trackbar = false);

// void erCvWatershed( IplImage*, erWaterP*);

/** \brief
    Permet de couvrir taches blanches (au desous du seuil) dans l image qui se trouvent entoure par des zones noir (au dessu du seuil)
*/
void erWhiteBlobCorrectionUser( IplImage*, erWhitBP*);

/** \brief
    Growing ou croisance pour segmenter une region a partir d'un point marque pour l'usager
*/
void erRegionGrowingUser( IplImage*, erRegGrP*);


#endif
