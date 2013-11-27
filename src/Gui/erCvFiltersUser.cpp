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
#include<erCv/Gui/customKeys.hpp>
#include <erCv/Gui/erCvFiltersUser.hpp>
//#include <erCv/erCv.hpp>
#include <iostream>
#include <fstream>



void on_mouse_rect( int event, int x, int y, int flags, void* param)
{
  erImage* pru = (erImage*) param;
  switch( event)
    {
    case CV_EVENT_MOUSEMOVE:
      {
	if( pru->drawing)
	  {
	    pru->rectan.width = x-pru->rectan.x;
	    pru->rectan.height = y-pru->rectan.y;
	  }
      }
      break;
    case CV_EVENT_LBUTTONDOWN:
      {
	pru->drawing = true;
	pru->rectan = cvRect( x, y, 0, 0);
      }
      
      break;
    case CV_EVENT_LBUTTONUP:
      { 
	pru->drawing = false;
	if( pru->rectan.width < 0)
	  {
	    pru->rectan.x += pru->rectan.width;
	    pru->rectan.width *= -1;
	  }
	if( pru->rectan.height < 0)
	  {
	    pru->rectan.y += pru->rectan.height;
	    pru->rectan.height *= -1;
	  }
	  cvRectangle( pru, cvPoint( pru->rectan.x, pru->rectan.y), 
		       cvPoint( pru->rectan.x + pru->rectan.width, 
				pru->rectan.y + pru->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	  //draw_box( pru->img, pru->rec);
       
      }
      break;
      //finish = true;
    }
}




void erCvCannyUser( IplImage* simg, erCannyP* parm, bool with_trackbar)
{
  IplImage* img;
  int threshold[2], maxt[2], itrak[2];
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold[0] = 1;
  threshold[1] = 1;
  img = cvCloneImage(simg);
  int ok =1;
  while( ok)
    {
      cvNamedWindow( "Canny_trackbar", 0);
      if( !with_trackbar)
	{
	  std::cout << "Put the values to threshold thr1 of Canny fonction: ";
	  //std::cin >> threshold[0];
	  threshold[0] = 500;
	  std::cout << std::endl;
	  std::cout << "Put the values to threshold thr2 of Canny fonction: ";
	  //std::cin >> threshold[1];
	  threshold[1] = 500;
	  std::cout << std::endl; 
	}
      else
	{
	  //std::cout << "Put the max values to two thresholds (thr1, thr2) of Canny fonction: ";
	  //std::cin >> maxt[0];
	  maxt[1] = maxt[0] = 500;
	  std::cout << std::endl;
	  itrak[0] = cvCreateTrackbar( "threshold1", "Canny_trackbar", &threshold[0], maxt[0], NULL);
	  itrak[1] = cvCreateTrackbar( "threshold2", "Canny_trackbar", &threshold[1], maxt[1], NULL);
	}
      while( 1)
	{   
	  cvCanny( simg, img, (float)threshold[0], (float)threshold[1], 5);
	  //cvCanny( simg, img, (float)maxt[0], (float)maxt[1], 5);
	  cvShowImage( "Canny_trackbar", img);
	  if( cvWaitKey( 10) == EscapeKey) break;
	}
      //cvShowImage( "original", simg);
      //parm->trh1 = cvGetTrackbarPos( "threshold1", "Canny_trackbar");
      //parm->trh2 = cvGetTrackbarPos( "threshold2", "Canny_trackbar");
      cvDestroyWindow( "Canny_trackbar");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      //ok = 0;
      std::cout << std::endl;
    };
  //simg = cvCloneImage( img);
  parm->trh1 = threshold[0];
  parm->trh2 = threshold[1];
  *simg = *img;
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction CANNY***************\n";
  file << "Threshold 1:----------- " << parm->trh1 << std::endl;
  file << "Threshold 2:----------- " << parm->trh2 << std::endl;
  file << std::endl;
}







void erCvSmoothUser( IplImage* simg, erSmootP* parm)
{ 
 
  IplImage *img;
  uint size, itrak;
  uint type;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  img = cvCloneImage( simg);
  int ok =1;
  while(ok)
    {
      std::cout << "Put the size (in pixels) of neighboor to smooth operation (odd number: 1, 3, 5, 7): ";
      std::cin >> size;
      std::cout << std::endl;
      std::cout << "Choose smooth type: ";
      for(uint i=0;i<nbSmoothType;i++)
	{std::cout << i << " -> " << smoothtype[i] << "  ";}
      std::cout << std::endl;
      std::cin >> type;
      std::cout << std::endl;

      cvSmooth( simg, img, type, size , 0, 0, 0);
  
      cvNamedWindow( "Smooth", 0);
      cvShowImage( "Smooth", img);
      while(1){if(cvWaitKey(10) == EscapeKey) break;};
      cvDestroyWindow( "Smooth");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      //ok = 0;
      std::cout << std::endl;
    };
  parm->size = size;
  parm->type  = SmoothType(type);
  *simg = *img;

  // std::ofstream file( nameInfoFile(INFOFILE), std::ios_base::app );
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction THRESHOLD***********\n";
  file << "Dimensions :------------ " << parm->size << std::endl;
  file << "Type---------:---------- " << parm->type << std::endl;
  file << std::endl;
  file << parm; 
}




// void erCvSobelUser( IplImage* simg,erSobelP* parm)
// {
//   IplImage* img;
//   int threshold[2], maxt[2], itrak[2];

//   threshold[0] = 1;
//   threshold[1] = 1;
//   img = cvCloneImage( simg);
 
//   std::cout << "Put the order to derivates axes X and Y to Sobel operator: ";
//   std::cin >> maxt[0] >> maxt[1];
//   std::cout << std::endl;
  
//   cvNamedWindow( "Sobel_trackbar", 0);
//   itrak[0] = cvCreateTrackbar( "derivate_order_x", "Sobel_trackbar", &threshold[0], maxt[0], NULL);
//   itrak[1] = cvCreateTrackbar( "derivate_order_y", "Sobel_trackbar", &threshold[1], maxt[1], NULL);
//   while( 1)
//     {       
//       cvSobel( simg, img, threshold[0], threshold[1], 5);
//       cvShowImage( "Sobel_trackbar", img);
//       if( cvWaitKey( 10) == 27) break;
//     }
//   parm->trhX = cvGetTrackbarPos( "derivate_order_x", "Sobel_trackbar");
//   parm->trhY = cvGetTrackbarPos( "derivate_order_y", "Sobel_trackbar");
//   cvDestroyWindow( "Sobel_trackbar");
  
//   std::ofstream file( nameInfoFile(INFOFILE), std::ios_base::app );
//   file << "***********Filter fonction SOBEL***************\n";
//   file << "Order derivate X:------ " << parm->trhX << std::endl;
//   file << "Order derivate Y:------ " << parm->trhY << std::endl;
//   file << std::endl;
//   *simg = *img;
// }






void erCvThresholdUser( IplImage* simg, erThresP* parm, bool with_trackbar)
{
  IplImage* img;
  int threshold[2], maxt, itrak[2], threstype;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold[0] = 1;
  threshold[1] = 1;
  img = cvCloneImage(simg);
  int ok=1;
  while(ok)
    {
      std::cout << "Type of threshold: 1->CV_THRESH_BINARY  2->CV_THRESH_BINARY_INV  3->CV_THRESH_TRUNC  4->CV_THRESH_TOZERO  5->CV_THRESH_TOZERO_INV : ";
      //std::cin >> threstype;
      threstype = 1;
      std::cout << std::endl;
      cvNamedWindow( "Threshold_trackbar", 0);
      cvNamedWindow( "original", 0);
      maxt = 255;
      if(!with_trackbar)
	{
	  std::cout << "Put the value of Threshold fonction (to 8-bit image = 255): ";
	  std::cin >> threshold[0];
	  //  threshold[0] = 230;
	  std::cout << std::endl;
	  if( threstype == 1 || threstype == 2)
	    {
	      std::cout << "Put the value of Second Threshold fonction (to 8-bit image = 255): ";
	      std::cin >> threshold[1];
	      //threshold[1] = 255;
	      std::cout << std::endl;
	    }
	}
      else
	{
	  itrak[0] = cvCreateTrackbar( "max_threshold", "Threshold_trackbar", &threshold[0], maxt, NULL);
	  if( threstype == 1 || threstype == 2)
	    {
	      itrak[1] = cvCreateTrackbar( "threshold", "Threshold_trackbar", &threshold[1], maxt, NULL);
	    }
	}
      while( 1)
	{  
	  if( threstype == 1) cvThreshold( simg, img, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY);
	  if( threstype == 2) cvThreshold( simg, img, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY_INV);
	  if( threstype == 3) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TRUNC);
	  if( threstype == 4) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO);
	  if( threstype == 5) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO_INV);
	  cvShowImage( "Threshold_trackbar", img);
	  cvShowImage( "original", simg);
	  if( cvWaitKey( 10) == EscapeKey) break;
	} 
      cvDestroyWindow( "Threshold_trackbar");
      cvDestroyWindow( "original");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      //std::cin >> ok;
      ok = 0;
      std::cout << std::endl;
    }  
 
  *simg = *img;
  //parm->trh1 = cvGetTrackbarPos( "max_threshold", "Threshold_trackbar");
  //parm->trh2 = cvGetTrackbarPos( "threshold", "Threshold_trackbar");
  parm->trh1 = threshold[0];
  if( threstype == 1 || threstype == 2)
    {
      parm->trh2 = threshold[1];
    }
  parm->type = ThresholdType(threstype);

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction THRESHOLD***********\n";
  file << "Threshold :------------ " << parm->trh1 << std::endl;
  std::cout << "trh2: " << parm->trh1 << std::endl;
  if( threstype == 1 || threstype == 2)
    {
      file << "SubThreshold:---------- " << parm->trh2 << std::endl;
      std::cout << "trh2: " << parm->trh2 << std::endl;
    }
  file << "Threshold type:-------- " << parm->type << std::endl;
  file << std::endl;
}





void erCvAdaptiveThresholdUser( IplImage* simg, erAdThrP* parm, bool with_trackbar)
{
  IplImage* img;
  int threshold, maxt[2], itrak[2], neigh, param;
  uint threstype,adapt;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold = 255;
  img = cvCloneImage(simg);
  int ok=1;
  while( ok)
    {  
      std::cout << std::endl;
      std::cout << "Type of threshold: 1->CV_THRESH_BINARY  2->CV_THRESH_BINARY_INV  : ";
      std::cin >> threstype;
      std::cout << std::endl;
      std::cout << "Type adaptative methode: 1->MEAN  2->GAUSSIAN  : ";
      std::cin >> adapt;
      std::cout << std::endl;
      cvNamedWindow( "Threshold_trackbar", 0);
      cvNamedWindow( "original", 0);
      if(!with_trackbar)
	{
	  std::cout << "Param to operate the adaptive threshold: ";
	  std::cin >> param;
	  std::cout << std::endl;
	  std::cout << "Neighboor to threshold in pixels (3,5,7,..): ";
	  std::cin >> neigh;
	  std::cout << std::endl;
	}
      else
	{
	  neigh = 1;
	  param = -20;
	  maxt[0] = 140;
	  maxt[1] = 130;
	  itrak[0] = cvCreateTrackbar( "premier_param", "Threshold_trackbar", &param, maxt[0], NULL);
	  itrak[1] = cvCreateTrackbar( "seconde_pixel", "Threshold_trackbar", &neigh, maxt[1], NULL);
	}
      while(1)
      	{
	  if( threstype == 1) 
	    {
	      if( adapt ==1) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, (2*neigh)+1, param-50);
	      if( adapt ==2) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, (2*neigh)+1, param-50);
	    }
	  if( threstype == 2)
	    {
	      if( adapt ==1) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, (2*neigh)+1, param-50);
	      if( adapt ==2) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, (2*neigh)+1, param-50);
	    }
	  cvShowImage( "Threshold_trackbar", img);
	  cvShowImage( "original", simg);
	  if( cvWaitKey( 10) == EscapeKey) break;
	}
      cvDestroyWindow( "Threshold_trackbar");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      std::cout << std::endl;
    }  
  *simg = *img;
  //std::cout << "param: " << param << std::endl;
  //std::cout << "neigh: " << neigh << std::endl;
  //parm->trhP = cvGetTrackbarPos( "premier_param", "Threshold_trackbar");
  //parm->neig = cvGetTrackbarPos( "seconde_pixel", "Threshold_trackbar");

  parm->trhP = param;
  parm->neig = neigh;
  parm->trh0 = threshold;
  parm->type = AdaptiveThresholdType(threstype);
  parm->adpt = AdaptiveMethodType(adapt);

  std::cout << "***********Filter fonction ADAPTIVE_THRESHOLD***********\n" << std::endl;
  std::cout << "Threshold type:------------- " << parm->type << std::endl;
  std::cout << "Adapt type:----------------- " << parm->adpt << std::endl;
  std::cout << "Parameter weight mean:------ " << parm->trhP << std::endl;
  std::cout << "Neighboor_size:------------- " << parm->neig << std::endl;
  std::cout  << "Threshold value:------------ " << parm->trh0 << std::endl;

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction ADAPTIVE_THRESHOLD***********\n";
  file << "Threshold type:------------- " << parm->type << std::endl;
  file << "Adapt type:----------------- " << parm->adpt << std::endl;
  file << "Parameter weight mean:------ " << parm->trhP << std::endl;
  file << "Neighboor_size:------------- " << parm->neig << std::endl;
  file << "Threshold value:------------ " << parm->trh0 << std::endl;
  file << std::endl;
  //std::cout << "parm->t: " << parm->trhP << std::endl;
  //std::cout << "parm->n: " << parm->neig << std::endl;
}





void erCvDilateUser( IplImage* simg, erDilatP* parm, bool with_trackbar)
{
  IplImage* img;
  int iteration, itrak, maxt; 
  IplConvKernel* ele=NULL;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  iteration = 1;
  img = cvCloneImage( simg);
  std::cout << "Put max iteration numbers of dilate its applies: ";
  std::cin >> maxt;
  //maxt = 20;
  //std::cout << std::endl;
  int ok=1;
  while(ok)
    {
      cvNamedWindow( "Dilate_trackbar", 0);
      if( !with_trackbar)
	{
	  std::cout << "Put the number of dilate iterations (int < 20): ";
	  std::cin >> iteration;
	  //iteration = 1;
	  std::cout << std::endl;
	}
      else
	{
	  itrak = cvCreateTrackbar( "iteration number", "Dilate_trackbar", &iteration, maxt, NULL);
	}
      while(1)
	{
	  cvDilate( simg, img, ele, iteration);
	  cvShowImage( "Dilate_trackbar", img);
	  if( cvWaitKey( 10) == EscapeKey) break;
	}
      parm->iter = cvGetTrackbarPos( "iteration number", "Dilate_trackbar");
      cvDestroyWindow( "Dilate_trackbar");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      //std::cin >> ok;
      ok = 0;
      std::cout << std::endl;
    }
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction DILATE**************\n";
  file << "No Iterations :-------- " << parm->iter << std::endl;
  file << std::endl;
  *simg = *img;
}





void erCvErodeUser( IplImage* simg, erErodeP* parm)
{
  IplImage* img;
  int iteration, itrak, maxt, value; 
  IplConvKernel* ele=NULL;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  iteration = 1;
  img = cvCloneImage( simg);

  //std::cout << "Put max iteration numbers of erode its applies: ";
  //std::cin >> maxt;
  maxt = 20;
  //std::cout << std::endl;

  /*Construction du trackbar*/
  cvNamedWindow( "Erode_trackbar", 0);
  itrak = cvCreateTrackbar( "iteration number", "Erode_trackbar", &iteration, maxt, NULL);

  /*Erosion de l'image avec trackbar*/
  while(1)
    {
      cvErode(simg, img, ele, iteration);
      cvShowImage( "Erode_trackbar", img);
      if( cvWaitKey( 10) == EscapeKey) break;
    }
  parm->iter = cvGetTrackbarPos( "iteration number", "Erode_trackbar");
  cvDestroyWindow( "Erode_trackbar");
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction ERODE***************\n";
  file << "No Iterations :-------- " << parm->iter << std::endl;
  file << std::endl;
  *simg = *img;
  //simg = cvCloneImage( img);
  //erShowImage( "hola", simg);
}



