#ifndef _erCV_SEGMENTATION_PARAMS_HPP_
#define _erCV_SEGMENTATION_PARAMS_HPP_
#include "erCvFiltersParams.hpp"
#include "erCvBase.hpp"
#include<iostream>
#include<string>
/** \defgroup seg_params SegmentationsParams */
/** \ingroup segmentations  */

/** \addtogroup seg_params */
/*@{*/




/** \brief
    Structure regroupant les paramettres pour la fonction erDifferencing
*/
struct erDiffeP
{
  //erDiffeP();
  //erDiffeP(erAdThrP,erThresP,std::string,int);
  erAdThrP *adapthold; 
  erThresP *threshold;
  IplImage *image;
  int type;
};



/**
   \brief
   Structure regroupant les paramettres pour la fonction erCvTemplate
 */
enum Templ{};
enum MatchTemplateType {SQDIFF=1, /** < Methode de la difference des moindres carres */ 
			SQDIFF_NORMED=2, /** < Methode de la difference des moindres carres normalize */
			CCORR=3, /** < Methode de correlation */
			CCORR_NORMED=4, /** Methode de correlation normalize */
			CCOEFF=5, /** Methode des coefficients */
			CCOEFF_NORMED=6 /** < Methode des coeffients normalize */
};
extern char* matchtemplatetype[];
struct erTemplP
{
  //erTemplP(MatchTemplateType, CvRect,bool,IplImage*);    /*REVISAR cet declaration avec Cyril */
  //erTemplP(MatchTemplateType, CvRect,bool,std::string);  /*REVISAR cet declaration avec Cyril */
  erTemplP( MatchTemplateType, CvRect, bool); /** < Constructeur avec les paramettres */
  erTemplP(); /** < Constructeur par default */
  CvRect rectan; /**  < Contien les dimension et coordones du rectangle de l echantillon a utiliser. x et y : coordones de vertices superieur gauche de l echantillon.
		  width et height: dimensions de l echantillon */
  bool drawing; /** < Permet de choisir entre designe (drawing = true) ou introduire les coordones et dimension de l echantillon (drawing = false) */  
  IplImage* image; /** < Guarde une copie de l image initial avant l application du template */
  MatchTemplateType type; /** < Methode a utiliser pour la segmentation */
};


// enum CallBP{};
// enum CallBPColorConversion {CV_RGB2XYZ=1,
// 			    CV_RGB2HSV=2,
// 			    CV_RGB2HLS=3,
// 			    CV_RGB2Lab=4,
// 			    CV_RGB2YCrCb=5,
// 			    CCOEFF_NORMED=6
// };
// extern char* matchtemplatetype[];
// struct erTemplP
// {
//   erTemplP(MatchTemplateType,CvRect,bool,IplImage*);
//   erTemplP();
//   CvRect rectan;
//   bool drawing;
//   IplImage *image;
//   MatchTemplateType type;
// };
struct erCallBP
{
  CvRect rectan;
  int type;
  int typeH;
  bool drawing;
  IplImage *image;
};



/** \brief    
    Paramettre pour l equalisation des histogrames
 */
struct erEqualP
{
  erEqualP( int); /** < Constructeur avec le paramettre */
  erEqualP(); /** < Constructeur par default */
  int applic; /** < Paramettre qu indique si l equalisateur est applique ou non */
};



/**
   \brief
   Structure regroupant les paramettres pour la fonction erCvPyramid
 */
struct erPyramP
{
  erPyramP();
  erPyramP(int,int,int);
  int trh1; /** < Threshold value to link in pyramid fonction */
  int trh2; /** < Threshold value to clustering in pyramid fonction */
  int levl; /** < Number of level to pyramid be applied */
};




/**
   \brief Structure contenant les parametre utilise par la fonction FindContours
 */
extern const int nbFindContoursMode;
extern char* findcontoursmode[]; 
enum FindContoursMode {erCV_RETR_EXTERNAL, /** < Repere seulement les contours externes   */
		       erCV_RETR_LIST, /** < Repere tous les contours et le place dans une liste   */
		       erCV_RETR_CCOM, /** < Repere tous les contours et les organize par hierarchie   */
		       erCV_RETR_TREE /** <  Repere tous les contours et les organize en fonction des contours qui sont conectes entre eux */
};
extern const int nbFindContoursMeth;
extern char* findcontoursmeth[]; 
enum FindContoursMeth {erCV_CHAIN_CODE, /** < */
		       erCV_CHAIN_APPROX_NONE, /** < */
		       erCV_CHAIN_APPROX_SIMPLE, /** < */
		       erCV_CHAIN_APPROX_TC89_L1 /** < */
};
struct erFindcP
{ 
  erFindcP(); /** < Constructeur par default */
  erFindcP( FindContoursMode, FindContoursMeth, int); /** < Constructeur avec les paramettres */
  int        level; /** <  */
  FindContoursMode  mode; /** < Mode d organization pour les contours */
  FindContoursMeth  meth; /** < Methode utilise pour retrouver les contours */
};
std::ostream& operator << (std::ostream&, const erFindcP);




// struct erWaterP
// {
//   bool drawing;
//   CvRect rectan;
//   IplImage *image;
// };

/** \brief
    Parammetres de la fonction WhiteBlobCorrector
*/
struct erWhitBP
{
  erWhitBP(); /** < Constructeur par defaut */
  erWhitBP( int, int, int, int); /** < Constructeur avec les paramettres */
  int trh_w; /** < Seuil inferieur a partir du quelle une zone blache est considere comme une tache */ 
  int trh_b; /** < Seuil superieur a partir du quelle une zone noire est considere comme un rebord noir de la tache */
  int blob_b; /** < Bord exterieur de la tache */
  int size_b; /** < Taille minimal en nombre de pixels de la tache a detecter */
};

/*@}*/
#endif


