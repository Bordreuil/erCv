#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/Gui/erCvFiltersUser.hpp>
#include <erCv/Gui/erCvSegmentationUser.hpp>
#include <iostream>
#include <fstream>
//#include "highgui.h"
//#include <cstdio>

void on_mouse_rect2( int event, int x, int y, int flags, void* param)
{
  erTemplP* pru = ( erTemplP*) param;
  //erCallBP* pru = ( erCallBP*) param;
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
	cvRectangle( pru->image, cvPoint( pru->rectan.x, pru->rectan.y), 
		     cvPoint( pru->rectan.x + pru->rectan.width, 
			      pru->rectan.y + pru->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	//draw_box( pru->img, pru->rec);
	
      }
      break;
      //finish = true;
    }
}


void on_mouse_rect4( int event, int x, int y, int flags, void* param)
{
  //erTemplP* pru = ( erTemplP*) param;
  erCallBP* pru = ( erCallBP*) param;
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
	cvRectangle( pru->image, cvPoint( pru->rectan.x, pru->rectan.y), 
		     cvPoint( pru->rectan.x + pru->rectan.width, 
			      pru->rectan.y + pru->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	//draw_box( pru->img, pru->rec);
	
      }
      break;
      //finish = true;
    }
}


void erCvDifferencingUser( IplImage* simg, erDiffeP* parm)
{
  int type;
  std::cout << "Type de threshold: simple = 1 / adaptive = 0" << std::endl;
  std::cin >> type;
  parm->type = type;

  IplImage *imge = cvCreateImage( cvGetSize(simg), simg->depth, simg->nChannels);
  cvAbsDiff( parm->image, simg, imge);
  //simg =  cvCloneImage( imge);
  //erCvThresholdUser( imge, simg, 15, 255, CV_THRESH_BINARY);
  if(type==1) erCvThresholdUser( imge, parm->threshold);
  if(type==0) erCvAdaptiveThresholdUser( imge, parm->adapthold);
  simg = imge;
}



IplImage* erCvTemplateUser( IplImage* img, erTemplP* parm)
{

  IplImage *img_temp, *temp, *result_img, *img_p;
  int type;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  int ok =1; 
  while(ok)
    {  
      parm->image = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
      cvCopy( img, parm->image);
      img_temp = cvCreateImage( cvGetSize(img), img->depth, img->nChannels);
      cvCopy( img, img_temp);
      parm->drawing = false;
      /**Construction du rectangle de la zone d'interet**/
      cvNamedWindow( "Designer la zone patron ou template", 0);  
      cvSetMouseCallback( "Designer la zone patron ou template", on_mouse_rect2, (void*)parm);
      while( 1)
	{
	  if( parm->drawing)
	    {
	      cvRectangle( parm->image, cvPoint( parm->rectan.x, parm->rectan.y), 
			   cvPoint( parm->rectan.x + parm->rectan.width, 
				    parm->rectan.y + parm->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	    }
	  cvShowImage( "Designer la zone patron ou template", parm->image);
	  if( cvWaitKey( 700) ==27) break;
	}
      cvDestroyWindow( "Designer la zone patron ou template");
      
      //---------NOTA REVISAR ESTA CONFIGURACION de imagenes entre:  img_temp y rect_img------------------------
      cvSetImageROI( img_temp, parm->rectan);
      parm->image = NULL;
      parm->image = cvCloneImage( img);
      cvSetImageROI( parm->image, parm->rectan);
      cvCopy( img_temp, parm->image);
      cvResetImageROI( img_temp);
      
      temp = cvCreateImage( cvGetSize( parm->image), parm->image->depth, parm->image->nChannels); 
      cvCopy( parm->image, temp);
      cvResetImageROI( parm->image);
      
      
      /**Construction de l'image ou les resultats seront exposees**/
      int patchx = parm->rectan.width;                
      int patchy = parm->rectan.height;
      int iwidth = parm->image->width - patchx + 1; 
      int iheight = parm->image->height - patchy + 1;
      //result_img = ( erImage*)cvCreateImage( cvSize(iwidth,iheight),32,1);
      result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
      cvZero( result_img);
      
      /**Construction du template (segmentation)**/
      std::cout << "Introduire le type de comparaison a effectuer avec le template" << std::endl;
      std::cout << "1->SQDIFF  2->SQDIFF_NORMED  3->CCORR  4->CCORR_NORMED  5->CCOEFF  6->CCOEFF_NORMED: ";
      std::cin >> type;
      if( type ==1) cvMatchTemplate( parm->image, temp, result_img, CV_TM_SQDIFF);
      if( type ==2) cvMatchTemplate( parm->image, temp, result_img, CV_TM_SQDIFF_NORMED);
      if( type ==3) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCORR);
      if( type ==4) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCORR_NORMED);
      if( type ==5) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCOEFF);
      if( type ==6) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCOEFF_NORMED);
      erShow2Image("Result-Template", result_img, "image-temoin", img );
      
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
    }; 
  /**Conversion de l'image en 32 bit vers 8 bit**/
  img_p  = cvCreateImage( cvGetSize(result_img), IPL_DEPTH_8U, 1);
  erCvConvert32to8( result_img, img_p);
  img = cvCreateImage( cvGetSize(parm->image), IPL_DEPTH_8U, 1);
  cvResize( img_p, img, CV_INTER_CUBIC);
//   std::cout << "color model: " << img->colorModel << std::endl;
//   std::cout << "Depth: " << img->depth << " " << "Channels: " << img->nChannels << std::endl;
//   std::cout << "width: " << img->width << " " << "height: " << img->height << std::endl;
  //erShowImage( "Segmentation par template", img);
  parm->type = type;
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Segmentation fonction TEMPLATE***********\n";
  file << "Rect(with):------------ " << parm->rectan.width << std::endl;
  file << "Rect(height):---------- " << parm->rectan.height << std::endl;
  file << "Rect(posX):------------ " << parm->rectan.x << std::endl;
  file << "Rect(posY):------------ " << parm->rectan.y << std::endl;
  file << "Template type:--------- " << parm->type << std::endl;
  file << std::endl;
  return img;
}





/*--------- Methode de segmentation CallBackProject (comparaison par regions avec histogrames) ---------*/
IplImage* erCvCallBackPatchProjectUser( IplImage* img, erCallBP* parm)
{
  IplImage *img_temp, *temp, *result_img, *img_p;
  int type, typeH;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  int ok =1; 
  while(ok)
    { 
      parm->image = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
      cvCopy( img, parm->image);
      img_temp = cvCreateImage( cvGetSize(img), img->depth, img->nChannels);
      cvCopy( img, img_temp);
      parm->drawing = false;
      
      /**Construction du rectangle de la zone d'interet**/
      cvNamedWindow( "Designer la zone patron ou template", 0);  
      cvSetMouseCallback( "Designer la zone patron ou template", on_mouse_rect4, (void*)parm);
      while( 1)
	{
	  if( parm->drawing)
	    {
	      cvRectangle( parm->image, cvPoint( parm->rectan.x, parm->rectan.y), 
			   cvPoint( parm->rectan.x + parm->rectan.width, 
				    parm->rectan.y + parm->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	    }
	  cvShowImage( "Designer la zone patron ou template", parm->image);
	  if( cvWaitKey( 100) ==27) break;
	}
      cvDestroyWindow( "Designer la zone patron ou template");
      
      //---------NOTA REVISAR ESTA CONFIGURACION de imagenes entre:  img_temp y rect_img------------------------
      cvSetImageROI( img_temp, parm->rectan);
      parm->image = NULL;
      parm->image = cvCloneImage( img);
      cvSetImageROI( parm->image, parm->rectan);
      cvCopy( img_temp, parm->image);
      //cvResetImageROI( img_temp);
      
      temp = cvCreateImage( cvGetSize( parm->image), parm->image->depth, parm->image->nChannels); 
      cvCopy( parm->image, temp);
      //cvResetImageROI( parm->image);
      
      
      /**Creation de l'image HSV**/
      IplImage *hsv[2], *h_plan[2], *s_plan[2], *v_plan[2], *plan[2][3]; 
      //cvSetImageROI( fuente_img2, box);
      std::cout << "colorModel de la imagen: " << parm->image->colorModel << std::endl;
      std::cout << std::endl;
      std::cout << "Type de conversion de color de l'image: " << std::endl;
      std::cout << "1->XYZ  2->HSV  3->HLS  4->Lab  5->YCrCb: ";
      std::cin >> typeH;
      for( int i = 0; i < 2; i++)
	{
	  if( i==1) cvResetImageROI( parm->image);
	  hsv[i] = cvCreateImage( cvGetSize( parm->image), parm->image->depth, 3);      
	  if( typeH ==1) cvCvtColor( parm->image, hsv[i], CV_RGB2XYZ);
	  if( typeH ==2) cvCvtColor( parm->image, hsv[i], CV_RGB2HSV);
	  if( typeH ==3) cvCvtColor( parm->image, hsv[i], CV_RGB2HLS);
	  if( typeH ==4) cvCvtColor( parm->image, hsv[i], CV_RGB2Lab);
	  if( typeH ==5) cvCvtColor( parm->image, hsv[i], CV_RGB2YCrCb);
	  h_plan[i] = cvCreateImage( cvGetSize( parm->image), parm->image->depth, 1);
	  s_plan[i] = cvCreateImage( cvGetSize( parm->image), parm->image->depth, 1);
	  v_plan[i] = cvCreateImage( cvGetSize( parm->image), parm->image->depth, 1);
	  plan[i][0] = h_plan[i];
	  plan[i][1] = s_plan[i];      
	  plan[i][2] = v_plan[i];
	  cvCvtPixToPlane( hsv[i], h_plan[i], s_plan[i], v_plan[i], 0);
	}
      
      /**Construction de l'histograma**/
      CvHistogram* hist;
      int h_bin = 50, s_bin = 50, v_bin = 50;
      int hist_size[] = { h_bin, s_bin, v_bin};
      float rang_h[] = { 0, 250};
      float rang_s[] = { 0, 255};
      float rang_v[] = { 0, 255};
      float *rang[] = { rang_h, rang_s, rang_v};  
      hist = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, rang, 1);
      cvCalcHist( plan[0], hist, 0, 0);
      cvNormalizeHist( hist, 1.0 );
      
      /**Construction de l'image ou les resultats seront exposees**/
      int patchx = parm->rectan.width;                
      int patchy = parm->rectan.height;
      int iwidth = parm->image->width - patchx + 1; 
      int iheight = parm->image->height - patchy + 1;
      result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
      cvZero(result_img);
      
      /**Construction du  BackProjectPatch**/
      std::cout << "Type de coparaison entre les histogrames dans le BackProjectPatch" << std::endl;
      std::cout << "1->CORREL  2->CHISQR  3->INTERSECT  4->BHATTACHARYYA :";
      std::cin >> type; 
      CvSize patch = cvSize(patchx,patchy);
      if( type == 1) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CORREL, 1.0);
      if( type == 2) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CHISQR, 1.0);
      if( type == 3) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_INTERSECT, 1.0);
      if( type == 4) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_BHATTACHARYYA, 1.0);
      erShow2Image("Result-Template", result_img, "image-temoin", img );
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
    };
  
  /**Conversion de l'image en 32 bit vers 8 bit**/
  img_p  = cvCreateImage( cvGetSize(result_img), IPL_DEPTH_8U, 1);
  erCvConvert32to8( result_img, img_p);
  img = cvCreateImage( cvGetSize(parm->image), IPL_DEPTH_8U, 1);
  cvResize( img_p, img, CV_INTER_CUBIC);

  
  parm->type = type;

  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Segmentation fonction TEMPLATE***********\n";
  file << "Rect(with):------------ " << parm->rectan.width << std::endl;
  file << "Rect(height):---------- " << parm->rectan.height << std::endl;
  file << "Rect(posX):------------ " << parm->rectan.x << std::endl;
  file << "Rect(posY):------------ " << parm->rectan.y << std::endl;
  file << "Template type:--------- " << parm->type << std::endl;
  file << std::endl;
  return img;
}


/*--------- Methode de equalisation des histogrames (celle ci permet d'amellier le contraste de l'image) ---------*/
void erCvEqualizeHistUser( IplImage* simg, erEqualP* param)
{
  IplImage* img;
  int usar;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  img = cvCloneImage(simg);
  int ok =1; 
  while(ok)
    { 
      std::cout << "Appliquer l'equalisation des histrogrames (Oui 0 / Non 1)";
      std::cin >> usar;
      if( usar == 0)
	{
	  cvEqualizeHist( simg, img);
	  erShow2Image("Result_equalize", img, "image_temoin", simg );
	  std::cout << " T'es content (Oui 0/Non 1)? ";
	  std::cin >> ok;
	}
      else
	ok = 0;
    };
  //erShowImage("Result_equalize", img );
  param->applic = usar;
  *simg = *img;
}



void erCvPyramidUser( IplImage* simg, erPyramP* parm, bool with_trackbar)
{
  IplImage* img;
  int threshold[2], maxt[2], itrak[2], level;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  //std::ofstream myfile( nomb);
  double a[2];
  CvSeq *comp; 
  //= NULL;
  CvMemStorage* stg = NULL;
  img = cvCloneImage( simg);

  int ok = 1;
  while(ok)
    {
      cvNamedWindow( "Pyramid_trackbar", 0);
      cvNamedWindow( "original", 0);
      if( !with_trackbar)
	{
	  std::cout << "Put the level of pyramid segmentation: ";
	  std::cin >> level;
	  std::cout << std::endl;
	  std::cout << "Put the error of threshold1(link) et threshold2(clustering): ";
	  std::cin >> threshold[0] >> threshold[1];
	  std::cout << std::endl;
	}
      else
	{
	  threshold[0] = 1;
	  threshold[1] = 1;
	  level = 3;
	  maxt[0] = maxt[1] = 30;
	  itrak[0] = cvCreateTrackbar( "max_thresh_link", "Pyramid_trackbar", &threshold[0], maxt[0], NULL);
	  itrak[1] = cvCreateTrackbar( "max_thresh_clus", "Pyramid_trackbar", &threshold[1], maxt[1], NULL);
	}
      while(1)
	{
	  if (stg==NULL)
	    {
	      stg = cvCreateMemStorage(1000);
	    }
	  else 
	    {
	      cvClearMemStorage(stg);
	    }
	  //a[0] = (double)(threshold[0]/1);
	  //a[1] = (double)(threshold[1]/1);
	  std::cout << "hola1" << std::endl;
	  cvPyrSegmentation(simg, img, stg, &comp, level, threshold[0], threshold[1]);
	  cvShowImage( "Pyramid_trackbar", img);
	  cvShowImage( "original", simg);
	  if( cvWaitKey( 10) == 27) break;
	}
      cvDestroyWindow( "Threshold_trackbar");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
    }  	 
  parm->trh1 = cvGetTrackbarPos( "max_thresh_link", "Pyramid_trackbar");
  parm->trh2 = cvGetTrackbarPos( "max_thresh_clus", "Pyramid_trackbar");
  parm->levl = level;
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction PYRAMID*************\n";
  file << "Error linking :-------- " << parm->trh1 << std::endl;
  file << "Error clustering:------ " << parm->trh2 << std::endl;
  file << "Level of pyramid:------ " << parm->levl << std::endl;
  file << std::endl;
  *simg = *img;
}



// void erCvPyrMeanShiftFiltering( IplImage* img, erPyrme* param)
// { 
//   IplImage* simg;
//   int usar;
//   std::string name = INFOFILE;
//   name+= ".txt";
//   const char* nomb = name.c_str();
//   img = cvCloneImage(simg);
//   int ok =1; 
//   while(ok)
//     { 
//       std::cout << "";
//       std::cin >> usar;
//       if( usar == 0)
// 	{
// 	  cvEqualizeHist( simg, img);
// 	  erShow2Image("Result_equalize", img, "image_temoin", simg );
// 	  std::cout << " T'es content (Oui 0/Non 1)? ";
// 	  std::cin >> ok;
// 	}
//       else
// 	ok = 0;
//     };
//   //erShowImage("Result_equalize", img );
//   param->applic = usar;
//   *simg = *img;
// }


//void erCvDrawLines( IplImage* img)
//{
  

