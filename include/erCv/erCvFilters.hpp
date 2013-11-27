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
#ifndef _ER_CV_FILTERS_HPP_
#define _ER_CV_FILTERS_HPP_

#include "erCvBase.hpp"
#include "erCvFiltersParams.hpp"

/** \defgroup filters erCvFilters */
/** \brief interface de filtres opencv dans erCv */




/** \brief 
    Permet de reperer les bordes ou zones de gradients qui repondent au filtre impusionelle de Canny. Le resultat affiche une image en binaire 
*/
void erCvCanny( IplImage*, erCannyP*);




/** 
    \brief 
    Permet d effectuer une lissage sur l image ou smooth
*/
void erCvSmooth( IplImage*, erSmootP*);





/** \brief
    Permet de filtrer l image par seuils d intensite
 */
void erCvThreshold( IplImage*, erThresP*);


/** \brief
    Permet d filtrer l image par seuils d intensites adaptes par zones 
 */
void erCvAdaptiveThreshold( IplImage*, erAdThrP*);



/** \brief
    Permet d effectuer un filtrage de l image en reduissant le nombre de pixels avec noir
 */
void erCvDilate( IplImage*, erDilatP*);



/** \brief
    Permet d effectuer un filtrage de l image en augmentant le nombre de pixels avec noir
 */
void erCvErode( IplImage*, erErodeP*);
/*@}*/

#endif
