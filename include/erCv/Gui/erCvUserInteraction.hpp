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
#ifndef _ERCV_USER_INTERACTION_HPP_
#define _ERCV_USER_INTERACTION_HPP_
#include <erCv/erCvBase.hpp>


/**
   \brief 
   Function qui permet a l usager de demarquer la zone d intreret a travers d un rectangle
   Si with_trackbar est true; la demarcation de la zone d interet s effectue a travers la souris en appuyant sur l image
   si non, il faut introduire les dimensions du rectangle 
 */
IplImage* erDef_ROIuser( erImage*, CvRect*, bool with_trackbar = false);



/**
   \brief
   Function qu utilise le rectagle definie en erDef_ROIuser pour demarquer la zone d interet
 */
IplImage* erDef_ROI( erImage*, CvRect*);



/**
   \brief
   Fonction qui permmet de destruir la zone d interet et revenier sur l image d origin
 */
void erRes_ROI_recons( IplImage*);



/**
   \brief
   Fonction qui permmet a l usager de marquer le debut d une corde ou ligne des pixels dans une image en binaire
*/
std::pair< CvPoint, int> erCvDebutCurve( IplImage*);

#endif
