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
#include <erCv/utilities/erFileUtilities.hpp>
#include <erCv/erCalibration.hpp>
// Peux être a enlever dans une prochaine version d'opencv ou cvFindChessBoardCorners Fonctionne
#include <erCv/erCvCalibinit/cvcalibinit.hpp>
#include <utility>
#include <boost/tuple/tuple.hpp>
#include <cmath>
#include <iostream>
#include <fstream>


erCalibration::erCalibration(){};


erCalibration::erCalibration(const char* name_image_patron,
			     const char* name_image_mesure, 
			     int         board_w, 
			     int         board_h, 
			     char*       file_dimention):
  _xoffset(0),_yoffset(0)
{ 
  _board_w              = board_w;
  _board_h              = board_h;
  _num_coins            = (board_w-1)*(board_h-1);
  
  bool mesure_loaded    = erFileExists(name_image_mesure);
  bool patron_loaded    = erFileExists(name_image_patron);
  bool files_loaded     = mesure_loaded*patron_loaded;
  
  if(files_loaded)
    {
      IplImage* image_mesure_color = cvLoadImage(name_image_mesure); // Faire les tests de bons chargements
      IplImage* image_patron_color = cvLoadImage(name_image_patron);
      _image_mesure = cvCreateImage( cvGetSize( image_mesure_color), image_mesure_color->depth, 1);
      _image_patron = cvCreateImage( cvGetSize( image_patron_color), image_patron_color->depth, 1); 
      
      cvCvtColor( image_mesure_color, _image_mesure, CV_RGB2GRAY);
      cvCvtColor( image_patron_color, _image_patron, CV_RGB2GRAY);
      double cuadro_dim_x, cuadro_dim_y;
      boost::tie( cuadro_dim_x, cuadro_dim_y) = real_dimensions( file_dimention);
      detect_corners(cuadro_dim_x,cuadro_dim_y);
    
    }
  else
    {
      std::cout << "...La calibration ne peut pas etre instancie\n";
    };
};


void erCalibration::detect_corners(double cuadro_dim_x,double cuadro_dim_y)
{
      _image_mesure->origin = _image_patron->origin;
      _board_sz             = cvSize(_board_w,_board_h);
      _warp_matrix          = cvCreateMat(3,3,CV_32FC1);
      //_warp_matrix          = cvCreateMat(2,3,CV_32FC1);
      bool idp              = find_corners(_image_patron,_corners_patron);
      bool idm              = find_corners(_image_mesure,_corners_mesure);
      _identified = idp * idm;
      
      if(_identified==true)
	
	{
	  CvPoint2D32f corners_patron[4],corners_mesure[4];
	  for(int i=0; i < 4; i++)
	    {
	      corners_patron[i] = _corners_patron[i];
	      corners_mesure[i] = _corners_mesure[i];
	    }
	  cvGetPerspectiveTransform(  corners_patron,corners_mesure, _warp_matrix);
	  //cvGetAffineTransform( corners_mesure, corners_patron, _warp_matrix);
	 
	  boost::tie( _mm_per_pixel_x, _mm_per_pixel_y) = compute_pixel_to_mm( corners_patron, cuadro_dim_x, cuadro_dim_y);
	};

};

void erCalibration::set_patron(IplImage* patron)
{
  _image_patron = patron;
}

void erCalibration::set_mesure(IplImage* mesure)
{
  _image_mesure = mesure;
};


erCalibration::~erCalibration(){}; 
// Methodes d initialisation
// Methodes d acces


erImage erCalibration::get_patron()
{ 
  return erImage(_image_patron);
};


erImage erCalibration::get_mesure()
{
  return erImage(_image_mesure);
};


std::pair<double,double> erCalibration::mm_per_pixels()
{ 
  return std::make_pair( _mm_per_pixel_x, _mm_per_pixel_y);
};
void erCalibration::setWrapOffset(double x,double y)
{
  _xoffset = x;
  _yoffset = y;
}
std::pair<double,double> erCalibration::distance_between_reference_corner()
{
 
  CvScalar cxx=cvGet2D(_warp_matrix,0,0);  
  CvScalar cxy=cvGet2D(_warp_matrix,0,1); 
  CvScalar cyx=cvGet2D(_warp_matrix,1,0);  
  CvScalar cyy=cvGet2D(_warp_matrix,1,1);
  CvScalar cxz=cvGet2D(_warp_matrix,0,2);  
  CvScalar cyz=cvGet2D(_warp_matrix,1,2); 
  CvScalar czz=cvGet2D(_warp_matrix,2,2);  
  CvScalar czx=cvGet2D(_warp_matrix,2,0);
  CvScalar czy=cvGet2D(_warp_matrix,2,1);
 
  cxz.val[0]-=_xoffset;
  cyz.val[0]-=_yoffset;
  cvSet2D(_warp_matrix,0,2,cxz);
  cvSet2D(_warp_matrix,1,2,cyz);
  

  double xmr = (cxx.val[0]*_corners_mesure[0].x + cxy.val[0]*_corners_mesure[0].y + cxz.val[0]-_corners_patron[0].x)/
    (czx.val[0]*_corners_mesure[0].x+czy.val[0]*_corners_mesure[0].y+czz.val[0]);
  double ymr = (cyx.val[0]*_corners_mesure[0].x + cyy.val[0]*_corners_mesure[0].y + cyz.val[0]-_corners_patron[0].y)/
    (czx.val[0]*_corners_mesure[0].x+czy.val[0]*_corners_mesure[0].y+czz.val[0]);
  // std::cout << cxz.val[0] << " " << cyz.val[0] << " " << czx.val[0]/
  //    (czx.val[0]*_corners_mesure[0].x+czy.val[0]*_corners_mesure[0].y+czz.val[0]) << " " << czy.val[0]/
  //    (czx.val[0]*_corners_mesure[0].x+czy.val[0]*_corners_mesure[0].y+czz.val[0])<< std::endl;
  double dx = _corners_patron[0].x-xmr;
  double dy = _corners_patron[0].y-ymr;
  
  return std::make_pair(dx,dy);
}


bool erCalibration::find_corners( IplImage *im, CornerContainer& corners_container)
{
  int          corner_count=0;
  IplImage     *image ; 
  CvPoint2D32f corners[_num_coins],cornersTemp[_num_coins];
  bool         identified;
  image = cvCloneImage(im);

  int found = erCvFindChessboardCorners( image, _board_sz, cornersTemp, &corner_count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
 
  if (found==0)
    { 
      double xmin = 100000.;
      double ymax = -100000.;
      int start;
      for(int i=0;i < _num_coins;i++)
	{
	if (cornersTemp[i].x  <= xmin)
	  {
	    xmin   = cornersTemp[i].x;
	  };
	};
      for(int i=0;i < _num_coins;i++)
	{
	if (cornersTemp[i].y  >= ymax)
	  {
	    ymax   = cornersTemp[i].y;
	  };
	}
      double minDist=100000.;
      for(int i=0;i < _num_coins;i++)
	{
	  double dist = std::sqrt(std::pow(cornersTemp[i].x-xmin,2)+std::pow(cornersTemp[i].y-ymax,2)); 

	if ( dist < minDist)
	  {

	    minDist = dist;
	    start  = i;
	  };
	}
      for(int i=0;i < _num_coins;i++)
	{
	  int j = start-i;
	  if (j < 0.){j+=_num_coins;}
	  corners[j] = cornersTemp[i];
	}
      
    
    }
  erCvDrawChessboardCorners(im,_board_sz,corners,corner_count,1);
  //erShowImage("corners", im);
  
  if(corner_count<4)
    {
      identified = false;
      std::cout << "...erCv : Les coins n ont pas ete detecte..\n";      
    }
  else
    {
      identified = true;
      // Attention au cas ou la version opencv permet de tracer .. revernir a cvDrawChessboardCorners
      erCvDrawChessboardCorners(im,_board_sz,corners,corner_count,1);
      //erShowImage("corners", im);
      corners_container.insert(corners_container.end(),corners,corners+_num_coins);      
    }
  return identified;
};


erImage erCalibration::transform_image( erImage ima)
{ CvSize   cs   = cvGetSize(_image_patron);
  IplImage * ir = cvCreateImage( cvGetSize(_image_patron), ima.depth, ima.nChannels);
  IplImage * im = &ima;
  if(_identified)
    {
      cvWarpPerspective(im,ir,_warp_matrix); 
      //cvWarpAffine(im,ir,_warp_matrix);      
    }
  else
    {
      std::cout << "..Transformation impossible\n";
    }
  return erImage(ir);
};


std::pair<double,double> erCalibration::compute_pixel_to_mm( CvPoint2D32f *corn, double cuadro_x, double cuadro_y)
{
  double mm_per_pixel_x;
  double mm_per_pixel_y;
  if( corn[1].y = corn[2].y)
    {
      mm_per_pixel_x = abs((double)(corn[1].x - corn[2].x)/ cuadro_x);
      mm_per_pixel_y = abs((double)(corn[2].y - corn[3].y)/ cuadro_y);
    }
  else
    {
      mm_per_pixel_x = abs(corn[2].x - corn[3].x)/ cuadro_x;
      mm_per_pixel_y = abs(corn[1].y - corn[2].y)/ cuadro_y; 
    }
  return std::make_pair( mm_per_pixel_x, mm_per_pixel_y); 
};


//std::pair<double,double> erCalibration::real_dimensions( char* file_dim)
erFactorRealDimension erCalibration::real_dimensions( char* file_dim)
{
  double dim_x, dim_y;
  std::ifstream myfile( file_dim);
  if( myfile.is_open())
    {
      myfile >> dim_x; 
      myfile >> dim_y;
      myfile.close();
      return std::make_pair( dim_x, dim_y);
    }
  else
    {
      std::cerr << "--erCv::Lecture de ficher pour le dimension du 'cuadro' imposible" << std::endl;
      std::cerr << "--erCv::Facteur de conversion par defaut 1" << std::endl;
      dim_x = 1;
      dim_y = 1;
      return std::make_pair( dim_x, dim_y);
    }
};


