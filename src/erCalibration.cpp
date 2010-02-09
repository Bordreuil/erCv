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


erCalibration::erCalibration( char* name_image_patron, char* name_image_mesure, int board_w, int board_h, char* file_dimention)
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
     
      _image_mesure->origin = _image_patron->origin;
      _board_sz             = cvSize(board_w,board_h);
      _warp_matrix          = cvCreateMat(3,3,CV_32FC1);
 
      bool idp              = find_corners(_image_patron,_corners_patron);
      bool idm              = find_corners(_image_mesure,_corners_mesure);
      _identified = idp * idm;
      
      if(_identified==true)
	
	{
	  CvPoint2D32f corners_patron[4],corners_mesure[4];
	  for(int i=0; i<4; i++)
	    {
	      corners_patron[i] = _corners_patron[i];
	      corners_mesure[i] = _corners_mesure[i];
	    }
	  cvGetPerspectiveTransform( corners_mesure, corners_patron, _warp_matrix);
	  //double cuadro_dim_x, cuadro_dim_y;
	  //boost::tie( cuadro_dim_x, cuadro_dim_y) = real_dimensions( file_dimention);
	  //boost::tie( _mm_per_pixel_x, _mm_per_pixel_y) = compute_pixel_to_mm( corners_patron, cuadro_dim_x, cuadro_dim_y);
	};
    }
  else
    {
      std::cout << "...La calibration ne peut pas etre instancie\n";
    };
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


bool erCalibration::find_corners( IplImage *im, CornerContainer& corners_container)
{
  int          corner_count=0;
  IplImage     *image ; 
  CvPoint2D32f corners[_num_coins];
  bool identified;
  image = cvCloneImage(im);

  int found = erCvFindChessboardCorners( image, _board_sz, corners, &corner_count, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

  std::cout << "corner_count: " << corner_count << std::endl;
  std::cout << "_board_sz.x: " << _board_sz.width << "_board_sz.y: " << _board_sz.height <<  std::endl;
  if(corner_count==0)
    {
      identified = false;
      std::cout << "...erCv : Les coins n ont pas ete detecte..\n";      
    }
  else
    {
      identified = true;
      // Attention au cas ou la version opencv permet de tracer .. revernir a cvDrawChessboardCorners
      erCvDrawChessboardCorners(im,_board_sz,corners,corner_count,1);
      erShowImage("corners", im);
      corners_container.insert(corners_container.end(),corners,corners+_num_coins);      
    }
  erShowImage("corners", im);
  return identified;
};


erImage erCalibration::transform_image( erImage ima)
{ 
  IplImage * ir = cvCreateImage( cvGetSize(_image_patron), ima.depth, ima.nChannels);
  IplImage * im = &ima;
  if(_identified)
    {
      cvWarpPerspective(im,ir,_warp_matrix);      
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
      std::cout << "Lecture de ficher pour le dimension du 'cuadro' imposible" << std::endl;
      return std::make_pair( dim_x, dim_y);
    }
};


