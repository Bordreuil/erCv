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
  /** \brief Constructeur par defaul */
  erCalibration();
  /** \brief Permet de trouver la matrice de passage de l 
      image patron a image mesure 
      les entiers correspondent a la taille de l echiquier
      Aujourd'hui(mai 2009), uniquement (3,3)
      \param char*         : nom de l image patron
      \param char*         : nom de l image a traiter
      \param int           : nombre des carres de l echequier a prendre en compte (largeur)
      \param int           : nombre des carres de l echequier a prendre en compte (hauteur)
      \param char*         : nom du ficher avec les facteurs de conversion
  */
  erCalibration( char*,char*, int, int, char* file_dimention = "cuadro_size.dat");

  /** \brief Destructeur */
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
