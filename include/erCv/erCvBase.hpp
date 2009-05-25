/** @file erCvBase.hpp 
  \brief Fichier contenant l encapsulation par une classe de la structure 
   IplImage d openCv ainsi que la redefinition de quelques fonctions d openCv
  @package erCv
  \defgroup cv_group erCv
  Decrit l encapsulation de base d opencv pour les developpements d edward
*/
#ifndef _erCvBase_hpp
#define _erCvBase_hpp

#include <cv.h>
#include <highgui.h>

// Une classe pour interfacer l image IplImage d OpenCv
/** \addtogroup cv_group */
/*@{*/

class Image
/** 
    Encapsulation de la structure IplImage d openCv
    pour utiliser Image dans des fonctions d openCv, il faut
    demander la fonction d acces : getCvImage qui ressort un IplImage*
 */
{
public:
  Image();
  Image(char* );
  Image(IplImage* );
  ~Image();
/** \brief Retourne le pointeur IplImage */
  IplImage* getCvImage(); 
private:
    IplImage* _im;
};

// Quelques fonctions utiles d' OpenCv
/** \brief Fonction permettant de visualiser une Image a l aide
 d openCv
 */
void erShowImage(char* ,Image);
/** \brief Fonction permettant de charge une  Image a l aide
 d openCv
 */
Image erLoadImage(char* );
/** \brief Fonction permettant de sauvegarder une image a l aide
 d openCv
 */
void erSaveImage(char*,Image);
/*@}*/
#endif
