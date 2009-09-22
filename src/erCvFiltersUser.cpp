#include <erCv/erCvFiltersUser.hpp>
#include <erCv/erCv.hpp>
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







void erCvCannyUser( IplImage* simg, p_canny* parm)
{
  IplImage* img1;
  int threshold[2], maxt[2], itrak[2];
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold[0] = 1;
  threshold[1] = 1;
  img1 = cvCloneImage(simg);
 
  std::cout << "Put the max values to two thresholds (thr1, thr2) of Canny fonction: ";
  std::cin >> maxt[0];
  maxt[1] = maxt[0];
  std::cout << std::endl;
  
  cvNamedWindow( "Canny_trackbar", 0);
  itrak[0] = cvCreateTrackbar( "threshold1", "Canny_trackbar", &threshold[0], maxt[0], NULL);
  itrak[1] = cvCreateTrackbar( "threshold2", "Canny_trackbar", &threshold[1], maxt[1], NULL);
  while( 1)
    {  
     
      cvCanny( simg, img1, (float)threshold[0]*10., (float)threshold[1]*10., 5);
      cvShowImage( "Canny_trackbar", img1);
      if( cvWaitKey( 10) == 27) break;
    }
  parm->trh1 = cvGetTrackbarPos( "threshold1", "Canny_trackbar");
  parm->trh2 = cvGetTrackbarPos( "threshold2", "Canny_trackbar");
  cvDestroyWindow( "Canny_trackbar");
  simg = cvCloneImage( img1);
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction CANNY***************\n";
  file << "Threshold 1:----------- " << parm->trh1 << std::endl;
  file << "Threshold 2:----------- " << parm->trh2 << std::endl;
  file << std::endl;
}




void erCvSmoothUser( IplImage* simg, p_smooth* parm)
{
  IplImage *img;
  int size, smoothtype, itrak;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  img = cvCloneImage( simg);

  std::cout << "Put the size (in pixels) of neighboor to smooth operation (odd number: 1, 3, 5, 7): ";
  std::cin >> size;
  std::cout << std::endl;
  std::cout << "Choose smooth type: 1->CV_BLUR_NO_SCALE  2->CV_BLUR  3->CV_GAUSSIAN  4->CV_MEDIAN  5->BILATERAL: ";
  std::cin >> smoothtype;
  std::cout << std::endl;

  if (smoothtype == 1) cvSmooth( simg, img, CV_BLUR_NO_SCALE, size , 0, 0, 0);
  if (smoothtype == 2) cvSmooth( simg, img, CV_BLUR, size , 0, 0, 0);
  if (smoothtype == 3) cvSmooth( simg, img, CV_GAUSSIAN, size , 0, 0, 0);
  if (smoothtype == 4) cvSmooth( simg, img, CV_MEDIAN, size , 0, 0, 0);
  if (smoothtype == 5) cvSmooth( simg, img, CV_BILATERAL, size , 0, 0, 0);
  cvNamedWindow( "Smooth", 0);
  cvShowImage( "Smooth", img);
  while(1)
    {
      if(cvWaitKey(10) == 27) break;
    }
  cvDestroyWindow( "Smooth");
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction SMOOTH**************\n";
  file << "neighboor size:-------- " << size << std::endl;
  file << "smooth type:----------- " << smoothtype << std::endl;
  file << std::endl;
  parm->size = size;
  parm->type = smoothtype;
  simg = cvCloneImage( img);
}




void erCvSobelUser( IplImage* simg, p_sobel* parm)
{
  IplImage* img;
  int threshold[2], maxt[2], itrak[2];
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold[0] = 1;
  threshold[1] = 1;
  img = cvCloneImage( simg);
 
  std::cout << "Put the order to derivates axes X and Y to Sobel operator: ";
  std::cin >> maxt[0] >> maxt[1];
  std::cout << std::endl;
  
  cvNamedWindow( "Sobel_trackbar", 0);
  itrak[0] = cvCreateTrackbar( "derivate_order_x", "Sobel_trackbar", &threshold[0], maxt[0], NULL);
  itrak[1] = cvCreateTrackbar( "derivate_order_y", "Sobel_trackbar", &threshold[1], maxt[1], NULL);
  while( 1)
    {       
      cvSobel( simg, img, threshold[0], threshold[1], 5);
      cvShowImage( "Sobel_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }
  parm->trhX = cvGetTrackbarPos( "derivate_order_x", "Sobel_trackbar");
  parm->trhY = cvGetTrackbarPos( "derivate_order_y", "Sobel_trackbar");
  cvDestroyWindow( "Sobel_trackbar");
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction SOBEL***************\n";
  file << "Order derivate X:------ " << parm->trhX << std::endl;
  file << "Order derivate Y:------ " << parm->trhY << std::endl;
  file << std::endl;
  simg = cvCloneImage( img);
}






void erCvThresholdUser( IplImage* simg, p_threshold* parm)
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

  std::cout << "Type of threshold: 1->CV_THRESH_BINARY  2->CV_THRESH_BINARY_INV  3->CV_THRESH_TRUNC  4->CV_THRESH_TOZERO  5->CV_THRESH_TOZERO_INV : ";
  std::cin >> threstype;
  std::cout << std::endl;
  std::cout << "Put the max value to threshold of Threshold fonction (to 8-bit image = 255): ";
  std::cin >> maxt;
  std::cout << std::endl;
  
  cvNamedWindow( "Threshold_trackbar", 0);
  itrak[0] = cvCreateTrackbar( "max_threshold", "Threshold_trackbar", &threshold[0], maxt, NULL);
  if( threstype == 1 or threstype == 2)
    {
      itrak[1] = cvCreateTrackbar( "threshold", "Threshold_trackbar", &threshold[1], maxt, NULL);
    }
  
  
  while( 1)
    {  
      if( threstype == 1) cvThreshold( simg, img, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY);
      if( threstype == 2) cvThreshold( simg, img, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY_INV);
      if( threstype == 3) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TRUNC);
      if( threstype == 4) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO);
      if( threstype == 5) cvThreshold( simg, img, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO_INV);
      cvShowImage( "Threshold_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }  
  simg = cvCloneImage( img);
  parm->trh1 = cvGetTrackbarPos( "max_threshold", "Threshold_trackbar");
  parm->trh2 = cvGetTrackbarPos( "threshold", "Threshold_trackbar");
  parm->type = threstype;
  cvDestroyWindow( "Threshold_trackbar");

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction THRESHOLD***********\n";
  file << "Threshold :------------ " << parm->trh1 << std::endl;
  file << "SubThreshold:---------- " << parm->trh2 << std::endl;
  file << "Threshold type:-------- " << parm->type << std::endl;
  file << std::endl;
}





void erCvAdaptiveThresholdUser( IplImage* simg, p_adaptivethreshold* parm)
{
  IplImage* img;
  int threshold, maxt, itrak, threstype, adapt, neigh, param;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  threshold = 1;
  img = cvCloneImage(simg);

  std::cout << "Param to operate the adaptive threshold: ";
  std::cin >> param;
  std::cout << std::endl;
  std::cout << "Neighboor to threshold in pixels (3,5,7,..): ";
  std::cin >> neigh;
  std::cout << std::endl;
  std::cout << "Type of threshold: 1->CV_THRESH_BINARY  2->CV_THRESH_BINARY_INV  : ";
  std::cin >> threstype;
  std::cout << std::endl;
  std::cout << "Type adaptative methode: 1->MEAN  2->GAUSSIAN  : ";
  std::cin >> adapt;
  std::cout << std::endl;
  maxt = 255;
  cvNamedWindow( "Threshold_trackbar", 0);
  itrak = cvCreateTrackbar( "max_threshold", "Threshold_trackbar", &threshold, maxt, NULL);  
  while( 1)
    {  
      if( threstype == 1) 
	{
	  if( adapt ==1) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, neigh, param);
	  if( adapt ==2) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, neigh, param);
	}
      if( threstype == 2)
	{
	  if( adapt ==1) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, neigh, param);
	  if( adapt ==2) cvAdaptiveThreshold( simg, img, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, neigh, param);
	}
      cvShowImage( "Threshold_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }  
  simg = cvCloneImage( img);
  parm->trhP = param;
  parm->neig = neigh;
  parm->trh0 = cvGetTrackbarPos( "max_threshold", "Threshold_trackbar");
  parm->type = threstype;
  parm->adpt = adapt;
  cvDestroyWindow( "Threshold_trackbar");

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction ADAPTIVE_THRESHOLD***********\n";
  file << "Parameter weight mean:------ " << parm->trhP << std::endl;
  file << "Neighboor_size:------------- " << parm->neig << std::endl;
  file << "Threshold value:------------ " << parm->trh0 << std::endl;
  file << "Threshold type:------------- " << parm->type << std::endl;
  file << "Adapt type:----------------- " << parm->adpt << std::endl;
  file << std::endl;
}





void erCvPyramidUser( IplImage* simg, p_pyramid* parm)
{
  IplImage* img;
  int threshold[2], maxt[2], itrak[2], level;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  double a[2];
  CvSeq* comp = NULL;
  CvMemStorage* stg = NULL;
  threshold[0] = 1;
  threshold[1] = 1;
  img = cvCloneImage( simg);

  std::cout << "Put the max level of pyramid segmentation: ";
  std::cin >> level;
  std::cout << std::endl;
  std::cout << "Put the error max value (100) of threshold1(link) et threshold2(clustering): ";
  std::cin >> maxt[0] >> maxt[1];

  cvNamedWindow( "Pyramid_trackbar", 0);

  itrak[0] = cvCreateTrackbar( "max_thresh_link", "Pyramid_trackbar", &threshold[0], maxt[0], NULL);
  itrak[1] = cvCreateTrackbar( "max_thresh_clus", "Pyramid_trackbar", &threshold[1], maxt[1], NULL);

  while(1)
    {
      if (stg==NULL)
	{
	  stg = cvCreateMemStorage(0);
	}
      else 
	{
	  cvClearMemStorage(stg);
	}
      a[0] = (double)(threshold[0]/1);
      a[1] = (double)(threshold[1]/1);
      cvPyrSegmentation(simg, img, stg, &comp, level, a[0], a[1]);
      cvShowImage( "Pyramid_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }
  parm->trh1 = cvGetTrackbarPos( "max_thresh_link", "Pyramid_trackbar");
  parm->trh2 = cvGetTrackbarPos( "max_thresh_clus", "Pyramid_trackbar");
  parm->levl = level;
  cvDestroyWindow( "Pyramid_trackbar");

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction PYRAMID*************\n";
  file << "Error linking :-------- " << parm->trh1 << std::endl;
  file << "Error clustering:------ " << parm->trh2 << std::endl;
  file << "Level of pyramid:------ " << parm->levl << std::endl;
  file << std::endl;
  simg = cvCloneImage( img);
}






void erCvDilateUser( IplImage* simg, p_dilate* parm)
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
  std::cout << std::endl;

  cvNamedWindow( "Dilate_trackbar", 0);
  itrak = cvCreateTrackbar( "iteration number", "Dilate_trackbar", &iteration, maxt, NULL);

  
  while(1)
    {
      cvDilate( simg, img, ele, iteration);
      cvShowImage( "Dilate_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }
  parm->iter = cvGetTrackbarPos( "iteration number", "Dilate_trackbar");
  cvDestroyWindow( "Dilate_trackbar");

   std::ofstream file( nomb, std::ios_base::app );
   file << "***********Filter fonction DILATE**************\n";
   file << "No Iterations :-------- " << parm->iter << std::endl;
   file << std::endl;
   simg = cvCloneImage( img);
}





void erCvErodeUser( IplImage* simg, p_erode* parm)
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

  std::cout << "Put max iteration numbers of erode its applies: ";
  std::cin >> maxt;
  std::cout << std::endl;

  /*Construction du trackbar*/
  cvNamedWindow( "Erode_trackbar", 0);
  itrak = cvCreateTrackbar( "iteration number", "Erode_trackbar", &iteration, maxt, NULL);

  /*Erosion de l'image avec trackbar*/
  while(1)
    {
      cvErode(simg, img, ele, iteration);
      cvShowImage( "Erode_trackbar", img);
      if( cvWaitKey( 10) == 27) break;
    }
  parm->iter = cvGetTrackbarPos( "iteration number", "Erode_trackbar");
  cvDestroyWindow( "Erode_trackbar");
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction ERODE***************\n";
  file << "No Iterations :-------- " << parm->iter << std::endl;
  file << std::endl;
  simg = cvCloneImage( img);
}



