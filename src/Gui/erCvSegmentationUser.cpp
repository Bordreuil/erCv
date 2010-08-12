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



IplImage* erCvTemplateUser( IplImage* img, erTemplP* parm, bool with_trackbar)
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
      if( !with_trackbar)
	{
	  std::cout << "width du zone echantillon: ";
	  std::cin >> parm->rectan.width;
	  std::cout << std::endl;
	  std::cout << "height du zone echantillon: ";
	  std::cin >> parm->rectan.height;
	  std::cout << std::endl;
	  std::cout << "Point X coin sup gauche de la zone: ";
	  std::cin >> parm->rectan.x;
	  std::cout << std::endl;
	  std::cout << "Point Y coin sup gauche de la zone: ";
	  std::cin >> parm->rectan.y;
	  std::cout << std::endl;
	  cvRectangle( parm->image, cvPoint( parm->rectan.x, parm->rectan.y), 
		       cvPoint( parm->rectan.x + parm->rectan.width, 
				parm->rectan.y + parm->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	}
      else
	{
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
	}
      
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
      std::cout << std::endl;
      if( type ==1) cvMatchTemplate( parm->image, temp, result_img, CV_TM_SQDIFF);
      if( type ==2) cvMatchTemplate( parm->image, temp, result_img, CV_TM_SQDIFF_NORMED);
      if( type ==3) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCORR);
      if( type ==4) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCORR_NORMED);
      if( type ==5) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCOEFF);
      if( type ==6) cvMatchTemplate( parm->image, temp, result_img, CV_TM_CCOEFF_NORMED);
      erShow2Image("Result-Template", result_img, "image-temoin", img );
      
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      std::cout << std::endl;
    }; 

  /**Conversion de l'image en 32 bit vers 8 bit**/
  img_p  = cvCreateImage( cvGetSize(result_img), IPL_DEPTH_8U, 1);
  erCvConvert32to8( result_img, img_p);
  img = cvCreateImage( cvGetSize(parm->image), IPL_DEPTH_8U, 1);
  cvResize( img_p, img, CV_INTER_CUBIC);
  parm->type = MatchTemplateType(type);
  //   std::cout << "color model: " << img->colorModel << std::endl;
  //   std::cout << "Depth: " << img->depth << " " << "Channels: " << img->nChannels << std::endl;
  //   std::cout << "width: " << img->width << " " << "height: " << img->height << std::endl;
  //erShowImage( "Segmentation par template", img);


  std::cout << "***********Segmentation fonction TEMPLATE***********\n";
  std::cout << "Rect(width):------------ " << parm->rectan.width << std::endl;
  std::cout << "Rect(height):---------- " << parm->rectan.height << std::endl;
  std::cout << "Rect(posX):------------ " << parm->rectan.x << std::endl;
  std::cout << "Rect(posY):------------ " << parm->rectan.y << std::endl;
  std::cout << "Template type:--------- " << parm->type << std::endl;
  
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Segmentation fonction TEMPLATE***********\n";
  file << "Rect(width):------------ " << parm->rectan.width << std::endl;
  file << "Rect(height):---------- " << parm->rectan.height << std::endl;
  file << "Rect(posX):------------ " << parm->rectan.x << std::endl;
  file << "Rect(posY):------------ " << parm->rectan.y << std::endl;
  file << "Template type:--------- " << parm->type << std::endl;
  file << std::endl;
  return img;
}





/*--------- Methode de segmentation CallBackProject (comparaison par regions avec histogrames) ---------*/
IplImage* erCvCallBackPatchProjectUser( IplImage* img, erCallBP* parm, bool with_trackbar)
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
      float rang_h[] = { 0, 255};
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
  int ok = 1; 

  

  while( ok)
    { 
      img = cvCloneImage(simg);
      img = cvCreateImage( cvGetSize( simg), simg->depth, simg->nChannels);
      cvCopy( simg, img );
      std::cout << "Appliquer l'equalisation des histrogrames (Oui 0 / Non 1)";
      std::cin >> usar;
      std::cout << std::endl;
      if( usar == 0)
	{ 
	  std::cout << "  simg widht: " << simg->width << "  simg height: " << simg->height << "  simg depth: " << simg->depth <<  std::endl;
	  std::cout << "  img widht: " << img->width << "  img height: " << img->height << "  img depth: " << img->depth <<  std::endl;
	  cvEqualizeHist( simg, img);
	  std::cout << "hola2" << std::endl;
	  erShow2Image("Result_equalize", img, "image_temoin", simg );
	  std::cout << " T'es content (Oui 0/Non 1)? ";
	  std::cin >> ok;
	  std::cout << std::endl;
	}
      else
	ok = 0;
    };
  //erShowImage("Result_equalize", img );
  std::cout << "hola3" << std::endl;
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
  CvMemStorage* stg;
  img = cvCloneImage( simg);

  int ok = 1;
  while(ok)
    {
      stg = cvCreateMemStorage( 1000);
      cvNamedWindow( "Pyramid_trackbar", 0);
      cvNamedWindow( "original", 0);
      if( !with_trackbar)
	{
	  std::cout << "Put the level of pyramid segmentation: ";
	  std::cin >> level;
	  std::cout << std::endl;
	  std::cout << "Put the error of threshold1(link 0 up up to 30): ";
	  std::cin >> threshold[0];
	  std::cout << std::endl;
	  std::cout << "Put the error of threshold2(clustering 0 up to 30): ";
	  std::cin >> threshold[1];
	  std::cout << std::endl;
	}
      else
	{
	  threshold[0] = 1;
	  threshold[1] = 1;
	  level = 2;
	  maxt[0] = maxt[1] = 30;
	  itrak[0] = cvCreateTrackbar( "max_thresh_link", "Pyramid_trackbar", &threshold[0], maxt[0], NULL);
	  itrak[1] = cvCreateTrackbar( "max_thresh_clus", "Pyramid_trackbar", &threshold[1], maxt[1], NULL);
	}
      while(1)
	{
	  
	  // 	  if (stg==NULL)
	  // 	    {
	  // 	      stg = cvCreateMemStorage(1000);
	  // 	    }
	  // 	  else 
	  // 	    {
	  // 	      cvClearMemStorage(stg);
	  // 	    }
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
  
void erCvFindContours(std::string name, erFindcP* parm, bool with_trackbar)
{
  IplImage* simg;
  simg=cvLoadImage(name.c_str());
  erCvFindContours(simg,parm,with_trackbar);
};


void erCvFindContours( IplImage* simg, erFindcP* parm, bool with_trackbar)
{
  CvSeq* contours = 0;
  CvSeq* result = 0;
  int level = 1, itrak, mode, meth;
  CvMemStorage* storage = cvCreateMemStorage(0);
  IplImage *img;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  img = cvCreateImage( cvGetSize( simg), simg->depth, simg->nChannels);
  cvCopy( simg, img);
  //img_temp = cvCreateImage( cvGetSize(img), img->depth, img->nChannels);
  //cvCopy( img, img_temp);
  int ok =1;
  while(ok)
    {
      std::cout << "Choose find contour mode: ";
      for( uint i=0; i < nbFindContoursMode; i++)
	{std::cout << i << " -> " << findcontoursmode[i] << "  ";}
      //std::cout << std::endl;
      std::cin >> mode;
      std::cout << std::endl;
      std::cout << "Choose find contour method: ";
      for( uint i=0; i < nbFindContoursMeth; i++)
	{std::cout << i << " -> " << findcontoursmeth[i] << "  ";}
      //std::cout << std::endl;
      std::cin >> meth;
      std::cout << std::endl;
      if( !storage) 
	{
	  cvClearMemStorage(storage);
	}
      cvNamedWindow( "Original", 0);
      cvNamedWindow( "Findc_trackbar", 0);
      if( !with_trackbar)
	{
	  std::cout << "Choose level to draw the find contour: ";
	  std::cin >> level;
	  std::cout << std::endl;
	}
      else
	{
	  itrak = cvCreateTrackbar( "levels+3", "Findc_trackbar", &level, 4, NULL );
	}
      while( 1)
	{

	  cvFindContours( simg, storage, &contours, sizeof(CvContour), mode, meth, cvPoint(0,0) );
	  std::cout << "hola0" << std::endl;
	  // comment this out if you do not want approximation
	  contours = cvApproxPoly( contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, 3, 1 );
	  //if( level-3 <= 0 ) // get to the nearest face to make it look more funny
	  //  contours = contours->h_next->h_next->h_next;
	  //cvZero( img );
	  cvDrawContours( img, contours, CV_RGB(255,0,0), CV_RGB(0,255,0), level, 4, 4, cvPoint(0,0) );
	  cvShowImage( "Original", simg );
	  cvShowImage( "Findc_trackbar", img );

	  //cvReleaseImage( &cnt_img );
	  if( cvWaitKey( 10) == 27) break;
	} 
      cvDestroyWindow( "Original");
      cvDestroyWindow( "Findc_trackbar");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      std::cout << std::endl;
    }
  parm->level = level;
  parm->mode = FindContoursMode(mode);
  parm->meth = FindContoursMeth(meth);
  *simg = *img;
  
  // std::ofstream file( nameInfoFile(INFOFILE), std::ios_base::app );
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Filter fonction THRESHOLD***********\n";
  file << "Level Draw Contour :------------ " << parm->level << std::endl;
  file << "Mode contour---------:---------- " << parm->mode << std::endl;
  file << "Methode Contour------:---------- " << parm->meth << std::endl;
  file << std::endl;
  file << parm;
}



void erCvWatershed( IplImage* img, erWaterP* parm)
{
  IplImage *simg, *simg1, *image;
  //erWaterP *prue, *parm; 
  
  simg = cvCreateImage( cvGetSize(img), IPL_DEPTH_32S, 1);

  parm->image = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
  //std::cout << "hola-0" << std::endl;  
  //simg1 = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
  //std::cout << "hola-1" << std::endl; 
  cvCopy( img, parm->image);
  //simg1 = img;
  //erShowImage( "simg1", parm->image);
  //prue->image = cvCreateImage( cvGetSize(img), img->depth, img->nChannels);  

  std::cout << "width: " << parm->image->width << "  height: " << parm->image->height <<  "  depth: " << parm->image->depth << "  chanel: " << parm-image->nChannels << std::endl; 
  std::cout << "width: " << simg->width << "  height: " << simg->height <<  "  depth: " << simg->depth << "  chanel: " << simg->nChannels << std::endl; 
  //cvCopy( img, simg);
 
  parm->drawing = false;
  parm->rectan = cvRect( 0,0,0,0);
  cvNamedWindow( "Marquez la zone", 0);
  cvSetMouseCallback( "Marquez la zone", on_mouse_rect2,  (void*)parm );
  while( 1)
    {
      cvShowImage( "Marquez la zone", parm->image);
      if( cvWaitKey( 700) == 27) break;
    }
  // std::cout << "depth (pru): " << prue->image->depth << std::endl;
  // std::cout << "depth (sim): " << simg->depth << std::endl;  
  // std::cout << "chanl (pru): " << pru->image->nChannels << std::endl;
  // std::cout << "chanl (sim): " << simg->nChannels << std::endl;
  
  IplImage* wshed = cvCloneImage( parm->image);
  IplImage* img_gray = cvCloneImage( parm->image);
  cvCvtColor( parm->image, img_gray, CV_GRAY2BGR);
  cvWatershed( parm->image, simg ); 
  std::cout << "watershed" << std::endl;
  int i,j, comp_count = 0;
  CvMat* color_tab;
  color_tab = cvCreateMat( 1, comp_count, CV_8UC3);
  for( i = 0; i < simg->height; i++ )
    for( j = 0; j < simg->width; j++ )
      {
	int idx = CV_IMAGE_ELEM( simg, int, i, j );
	uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );
	if( idx == -1 )
	  dst[0] = dst[1] = dst[2] = (uchar)255;
	else if( idx <= 0 || idx > comp_count )
	  dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
	else
	  {
	    uchar* ptr = color_tab->data.ptr + (idx-1)*3;
	    dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
	  }
      }
  
  cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );
  //cvShowImage( "watershed transform", wshed );
  
  erShowImage( "WaterShet", wshed); 
}
