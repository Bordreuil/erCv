
/** @file erCalibration.hpp 
 \brief Classe permettant d effectuer la calibration de la camera et
   de transforme les images prise par la camera dans une configuration
  @package erCv
 
*/
/**  @addtogroup cv_group */
#ifndef _erCalibration_hpp_
#define _erCalibration_hpp_
/*@{*/
#include<vector>
#include <cv.h>
#include <highgui.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <iostream>
#include "erCvBase.hpp"

using namespace std;
typedef std::pair<double,double> erFactorRealDimension;

//----------------------------------------------------------------------
//---------
//..Class pour la  calibration
//
class erCalibration
/**
   Classe permettant de calibrer la prise de vue de la camera et ainsi de se placer 
   dans le plan perpendiculaire au plan local.
   Mai-2009: Uniquement une wrap perspective est utilisé pour transformer les 
   images, pas de correction de distorsions d images
*/
{
public:
  // Quelques definitions de type utile par la suite
  typedef std::vector<CvPoint2D32f>   CornerContainer;
  typedef CornerContainer::iterator   CornerIterator;
  // Constructeurs Destructeurs
  erCalibration();
  /** \brief Permet de trouver la matrice de passage de l 
      image patron a image mesure 
      les entiers correspondent a la taille de l echiquier
      Aujourd'hui(mai 2009), uniquement (3,3)
  */
  //erCalibration( char*, char*, int, int);
  erCalibration( char*, char*, int, int, char* file_dimention = "cuadro_size.dat");
  ~erCalibration(); 
  
  // Methodes d acces
  /** \brief Permet d extraire l image patron */
  erImage get_patron(); 
  /** \brief Permet d extraire l image mesure */
  erImage get_mesure(); 
  /** \brief Permet de transformer une Image */
  erImage transform_image( erImage);
  /** \brief Permet d acceder au facteur de conversion */
  std::pair<double,double> mm_per_pixels();
  
private:
  // Fonctions internes utilises par cette class
  bool  find_corners( IplImage*, CornerContainer&);
  std::pair<double,double> compute_pixel_to_mm( CvPoint2D32f*, double, double);
  std::pair<double,double> real_dimensions( char*);
  
  // Variables membres......
  double          _mm_per_pixel_x, _mm_per_pixel_y;// Milimmetres par pixel (facteur de convertion)  
  bool            _identified;                     // Booleen pour savoir si tous les sommets on ete dectectes
  int             _board_w,_board_h,_num_coins;
  IplImage        *_image_mesure, *_image_patron;  // Image OpenCv pour 
  CvSize          _board_sz;                       
  CvMat*          _warp_matrix;                    // Matrice de passage pour la transformation perspective
  CornerContainer _corners_patron,_corners_mesure; // Stocke les sommets
};
/*@}*/
#endif
