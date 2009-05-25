#include "erFileUtilities.hpp"
#include "erCalibration.hpp"


erCalibration::erCalibration(){};
erCalibration::erCalibration(char* name_image_patron,char* name_image_mesure,int board_w,int board_h)
{ 
    _board_w              = board_w;
    _board_h              = board_h;
    _num_coins            = (board_w-1)*(board_h-1);

    bool mesure_loaded    = erFileExists(name_image_mesure);
    bool patron_loaded    = erFileExists(name_image_patron);
    bool files_loaded = mesure_loaded*patron_loaded;
    if(files_loaded)
      {
	_image_mesure         = cvLoadImage(name_image_mesure); // Faire les tests de bons chargements
	_image_patron         = cvLoadImage(name_image_patron);
	_image_mesure->origin = _image_patron->origin;
	_board_sz             = cvSize(board_w,board_h);
	_warp_matrix          = cvCreateMat(3,3,CV_32F);

	bool idp              = findCorners(_image_patron,_corners_patron);
	bool idm              = findCorners(_image_mesure,_corners_mesure);
	_identified = idp * idm;
	if(_identified)
      
	  { CvPoint2D32f corners_patron[4],corners_mesure[4];
	    for(int i=0;i<4;i++)
	      {
		corners_patron[i] = _corners_patron[i];
		corners_mesure[i] = _corners_mesure[i];
	      }
	    cvGetPerspectiveTransform(corners_mesure,corners_patron,_warp_matrix);
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

Image erCalibration::getPatron()
  { 
    return Image(_image_patron);
  };
Image erCalibration::getMesure()
  {
    return Image(_image_mesure);
  };
bool erCalibration::findCorners(IplImage *im,CornerContainer& corners_container)
  { int          corner_count=0;
    IplImage     *image ; 
    CvPoint2D32f corners[_num_coins];
    bool identified;
    image = cvCloneImage(im);
    
    int found = cvFindChessboardCorners( image, _board_sz, corners, &corner_count, 
       					   CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
    if(found==0)
      {
	identified = true;
	cvDrawChessboardCorners(im,_board_sz,corners,corner_count,1);
	corners_container.insert(corners_container.end(),corners,corners+_num_coins);

      }
    else
      {
	std::cout << "...erCV : Nb coins detectes:" << corner_count << std::endl;
	identified = false;
	std::cout << "...erCv : Les coins n ont pas ete detecte..\n";
      }
    return identified;
  };

Image  erCalibration::transformImage(Image ima)
  {
    IplImage * ir = cvCloneImage(ima.getCvImage());
    IplImage * im = ima.getCvImage();
    

    if(_identified)
      {
	cvWarpPerspective(im,ir,_warp_matrix);

      }
    else
      {
	std::cout << "..Transformation impossible\n";
      }
 
    return Image(ir);
  };
