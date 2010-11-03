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
