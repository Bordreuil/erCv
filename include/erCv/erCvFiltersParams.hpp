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
#ifndef _erCV_FILTERS_PARAMS_HPP_
#define _erCV_FILTERS_PARAMS_HPP_
#include<iostream>
/** \defgroup filters_params FiltersParams */
/** \ingroup filters  */

/** \addtogroup filters_params */
/*@{*/



/**
   \brief 
   Structure contenant les paramettres pour le lissage ou smooth
 */

extern const int nbSmoothType;
extern char* smoothtype[]; 
enum SmoothType {BLUR_NO_SCALE, /** < 0 : Lissage d'average d'intensite de gris  */
		 BLUR,          /** < 1 : Lissage d'avergage d'intensite de gris moyenne  */
		 GAUSSIAN,      /** < 2 : Lissage des pixles utilisant une adoucissement gaussiene pour leur intensites de gris  */
		 MEDIAN,        /** < 3 : Lissage utilissant la valeur median des intensites de gris sur les zones  */
		 BILATERAL      /** < 4 : Lissage utilissant un filtre bilateral  */
};
struct erSmootP
{ 
  erSmootP( );     /** < Constructeur par defaut */
  erSmootP( SmoothType, int); /** < Constructeur du smooth: d'abord le type de smooth 
				  et apres la taille des zones d'application du smooth */
  int        size; /** < Le lissage sera applique par zones de taille: size x size */
  SmoothType type; /** < Le type de lissage que sera applique au groupes de pixles dans chaque zone */
};

std::ostream& operator << (std::ostream&, const erSmootP);



/**
   \brief 
   Filtre 
 */

struct erSobelP
{ 
  int trhX; /** < Order X derivated in sobel fonction */
  int trhY; /** < Order Y derivated in sobel fonction */
};

 

/**
   \brief
   Paramettres utilis� pour le filtre de Canny, pour regler le seuil de detection de contours
 */
struct erCannyP
{ erCannyP(int,int);
  erCannyP();
  int trh1; /** < Threshold 1 to canny fonction */
  int trh2; /** < Threshold 2 to canny fonction */
};
std::ostream& operator << (std::ostream&,const erCannyP);



/**
   \brief
   Paramettres utilises effecteur seuillage sur l'image 
*/
enum ThresholdType{ THRESH_BINARY_    = 1, /** < 1: Seuillage binaire  */
		    THRESH_BINARY_INV_= 2, /** < 2: Seuilage binaire inverse  */
		    THRESH_TRUNC_     = 3, /** < 3: Seuillage truncate  */
		    THRESH_TOZERO_    = 4, /** < 4: Seuillage vers zero  */
		    THRESH_TOZERO_INV_= 5  /** < 5: Seuillage vers le zero inverse  */
};
extern char* thresholdtype[ ];
struct erThresP
{
  erThresP(); /** < Constructeur par defaul */
  erThresP(ThresholdType,int,int); /** < Constructeur avec les paramettres */
  int trh1; /** < Niveau de gris dans l'image binaire resultant */
  int trh2; /** < Valeur du seuil dans l'image */
  ThresholdType type; /** < Type de seuillage a appliquer */
};
//std::ostream& operator << (std::ostream&,const erThresP);



/**
   \brief
   Paramettres utilises pour le seuillage adapte par zones d'une image en different niveaux de gris 
*/
//enum Adapt{};
enum AdaptiveThresholdType{THRESH_BINARY=1,     /** < 1: Seuillage du type blanche et noir  */
			   THRESH_BINARY_INV=2  /** < 2: Seuillage du type noir et blache  */
};
enum AdaptiveMethodType{AM_MEAN=1,              /** < 1:  Calcul la moyenne des niveau de gris entre les pixels compris dans les zones */
			AM_GAUSSIAN=2           /** < 2:  Etablie la moyenne gaussiene des niveaux de gris entre les pixels compris dans les zones */
};
extern char* adaptivethresholdtype[]; /** < Type de seuillage a appliquer (Binaire ou binaire invers�) */
extern char* adaptivemethodtype[]; /** < Methode a appliquer pour ressembler le niveux de gris des pixels par zone (gaussien ou moyennage) */
struct erAdThrP
{ 
  erAdThrP(); /** < Constructeur par defaul */
  erAdThrP( AdaptiveThresholdType, AdaptiveMethodType, int, int, int);
  int trhP;  /** < Valeur constant qui modifie le valeur moyenne dans l'image (il peut agmenter ou diminuer le contraste par zones */
  int neig;  /** < Taille en pixles des zones ou est applique le seuillage 
		 (plus grand est la zone, plus ca resamblera a une methode de seuillage classique) */
  int trh0;  /** < Niveau de gris a partir du quel l'image est segment� soit en blanch ou en noir */
  AdaptiveThresholdType type;  /** < Type de seuillage a appliquer (Binaire ou binaire invers�) */
  AdaptiveMethodType    adpt;  /** < Methode a appliquer pour ressembler le niveux de gris des pixels par zone (gaussien ou moyennage) */
};
std::ostream& operator << (std::ostream&,const erAdThrP);


/**
   \brief
   Paramettre pour la fonction Dilate
 */
struct erDilatP
{
  erDilatP(); /** < Constructeur par defaul */
  erDilatP( int); /** < Constructeur avec le paramettre */
  int iter; /** < Numero d'iterations a appliquer sur l'image pour reduire les zones blaches (pixels) */
};


/**
   \brief
   Paramettre pour la fonction Erode
 */
struct erErodeP
{
  erErodeP( ); /** < Constructeur par defaul */
  erErodeP( int); /** < Constructeur avec le paramettre */
  int iter; /** < Numero d'iteration pour augmenter les zones (pixels) blanches dans l'image */
};




/*@}*/
#endif

