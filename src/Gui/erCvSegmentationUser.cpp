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
#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/Gui/erCvUserInteraction.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <erCv/Gui/erCvFiltersUser.hpp>
#include <erCv/Gui/erCvSegmentationUser.hpp>
#include <iostream>
#include <fstream>
#include<map>
#include<vector>
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


struct coordinate
{
  unsigned int x, y;
  void * data;
};

struct lineBlob
{
  unsigned int min, max;
  unsigned int blobId;
  unsigned int row;
  bool attached;
};

struct blob
{
  //unsigned int blobId;
  coordinate min, max;
  bool is_valid;
  coordinate center;
};






// void erCvDifferencingUser( IplImage* simg, erDiffeP* parm)
// {
//   int type;
//   std::cout << "Type de threshold: simple = 1 / adaptive = 0" << std::endl;
//   std::cin >> type;
//   parm->type = type;

//   IplImage *imge = cvCreateImage( cvGetSize(simg), simg->depth, simg->nChannels);
//   cvAbsDiff( parm->image, simg, imge);
//   //simg =  cvCloneImage( imge);
//   //erCvThresholdUser( imge, simg, 15, 255, CV_THRESH_BINARY);
//   if(type==1) erCvThresholdUser( imge, parm->threshold);
//   if(type==0) erCvAdaptiveThresholdUser( imge, parm->adapthold);
//   simg = imge;
// }



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
	  //parm->rectan.width = 8;
	  std::cout << std::endl;
	  std::cout << "height du zone echantillon: ";
	  std::cin >> parm->rectan.height;
	  //parm->rectan.height = 8;
	  std::cout << std::endl;
	  std::cout << "Point X coin sup gauche de la zone: ";
	  std::cin >> parm->rectan.x;
	  //parm->rectan.x = 9;
	  std::cout << std::endl;
	  std::cout << "Point Y coin sup gauche de la zone: ";
	  std::cin >> parm->rectan.y;
	  //parm->rectan.y = 208;
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
      //type = 2;
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
      //ok = 0;
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
	  //std::cout << "hola2" << std::endl;
	  erShow2Image("Result_equalize", img, "image_temoin", simg );
	  std::cout << " T'es content (Oui 0/Non 1)? ";
	  std::cin >> ok;
	  std::cout << std::endl;
	}
      else
	ok = 0;
    };
  //erShowImage("Result_equalize", img );
  //std::cout << "hola3" << std::endl;
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



// void erCvWatershed( IplImage* img, erWaterP* parm)
// {
//   IplImage *simg, *simg1, *image;
//   //erWaterP *prue, *parm; 
  
//   simg = cvCreateImage( cvGetSize(img), IPL_DEPTH_32S, 1);

//   parm->image = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
//   //std::cout << "hola-0" << std::endl;  
//   //simg1 = cvCreateImage( cvGetSize( img), img->depth, img->nChannels);
//   //std::cout << "hola-1" << std::endl; 
//   cvCopy( img, parm->image);
//   //simg1 = img;
//   //erShowImage( "simg1", parm->image);
//   //prue->image = cvCreateImage( cvGetSize(img), img->depth, img->nChannels);  

//   std::cout << "width: " << parm->image->width << "  height: " << parm->image->height <<  "  depth: " << parm->image->depth << "  chanel: " << parm-image->nChannels << std::endl; 
//   std::cout << "width: " << simg->width << "  height: " << simg->height <<  "  depth: " << simg->depth << "  chanel: " << simg->nChannels << std::endl; 
//   //cvCopy( img, simg);
 
//   parm->drawing = false;
//   parm->rectan = cvRect( 0,0,0,0);
//   cvNamedWindow( "Marquez la zone", 0);
//   cvSetMouseCallback( "Marquez la zone", on_mouse_rect2,  (void*)parm );
//   while( 1)
//     {
//       cvShowImage( "Marquez la zone", parm->image);
//       if( cvWaitKey( 700) == 27) break;
//     }
//   // std::cout << "depth (pru): " << prue->image->depth << std::endl;
//   // std::cout << "depth (sim): " << simg->depth << std::endl;  
//   // std::cout << "chanl (pru): " << pru->image->nChannels << std::endl;
//   // std::cout << "chanl (sim): " << simg->nChannels << std::endl;
  
//   IplImage* wshed = cvCloneImage( parm->image);
//   IplImage* img_gray = cvCloneImage( parm->image);
//   cvCvtColor( parm->image, img_gray, CV_GRAY2BGR);
//   cvWatershed( parm->image, simg ); 
//   std::cout << "watershed" << std::endl;
//   int i,j, comp_count = 0;
//   CvMat* color_tab;
//   color_tab = cvCreateMat( 1, comp_count, CV_8UC3);
//   for( i = 0; i < simg->height; i++ )
//     for( j = 0; j < simg->width; j++ )
//       {
// 	int idx = CV_IMAGE_ELEM( simg, int, i, j );
// 	uchar* dst = &CV_IMAGE_ELEM( wshed, uchar, i, j*3 );
// 	if( idx == -1 )
// 	  dst[0] = dst[1] = dst[2] = (uchar)255;
// 	else if( idx <= 0 || idx > comp_count )
// 	  dst[0] = dst[1] = dst[2] = (uchar)0; // should not get here
// 	else
// 	  {
// 	    uchar* ptr = color_tab->data.ptr + (idx-1)*3;
// 	    dst[0] = ptr[0]; dst[1] = ptr[1]; dst[2] = ptr[2];
// 	  }
//       }
  
//   cvAddWeighted( wshed, 0.5, img_gray, 0.5, 0, wshed );
//   //cvShowImage( "watershed transform", wshed );
  
//   erShowImage( "WaterShet", wshed); 
// }


void erWhiteBlobCorrectionUser( IplImage* simg, erWhitBP* parm)
{
  IplImage* img;
  unsigned char byte, byte_right, byte_left, col_avg_up = 0, col_avg_down = 0;
  unsigned char white_thres, black_thres;
  unsigned int id_refused[simg->width];
  bool valide_map, blob_nul;
  int int_white, int_black, vector_blob_size, k;  
  int blobCounter = 0, bord_blob = 5, size_blob = 100, col_avg = 0, count = 0, l;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  std::map<unsigned int, blob> blobs;
  std::map<unsigned int, int> color;
  std::map<unsigned int, std::vector<lineBlob> > manchas;
  std::map<unsigned int, std::vector<lineBlob> >::iterator iter_map_line;
  std::vector<lineBlob> vector_blob;
  std::vector<lineBlob>::iterator iter_vector_line, iter_vector_line_up, iter_vector_line_down;
  // std::vector<lineBlob>::reverse_iterator riter_vector_line_down;
  //img = cvCloneImage(simg);
  std::vector< std::vector<lineBlob> > imgData(simg->width);
  int ok = 1;
  while( ok)
    {
      img = cvCreateImage( cvGetSize( simg), simg->depth, simg->nChannels);
      cvCopy( simg, img);
      std::cout << "Threshold upper value to blob detection: ";
      //std::cin >> int_white;
      int_white = 150;
      white_thres = (unsigned char) int_white;
      std::cout << std::endl;
      std::cout << "Threshold donwest value to blob detection: ";
      //std::cin >> int_black;
      int_black = 150;
      black_thres = (unsigned char) int_black;
      std::cout << std::endl;
      std::cout << "Taille en No de pixles de la tache: ";
      //std::cin >> size_blob;
      size_blob = 50;
      std::cout << std::endl;
      std::cout << "Extension en pixels du bord de la tache: ";
      //std::cin >> bord_blob;
      bord_blob = 5;    
      std::cout << std::endl;
      



 for(int row = 0; row < simg->height; ++row)
    {
      
      for(int column = 0; column < simg->width; ++column)
	{
	  
	  //unsigned char byte = (unsigned char) imgStream.get();
	  unsigned char byte = ( unsigned char) simg->imageData[ ( row*simg->width) + column];
	  
	  if(byte >= white_thres)
	    {
	      int start = column;
	      
	      for( ;byte >= white_thres; byte = (unsigned char) simg->imageData[ ( row*simg->width) + column], ++column);
	      
	      int stop = column-1;
	      lineBlob lineBlobData = {start, stop, blobCounter, row, false};
	      
	      imgData[row].push_back(lineBlobData);
	      blobCounter++;
	    }
	}
    }
      
      /* Check lineBlobs for a touching lineblob on the next row */
      // Aqui se asocian los ima
      for(int row = 0; row < imgData.size(); ++row) //
	{      
	  for(int entryLine1 = 0; entryLine1 < imgData[row].size(); ++entryLine1)
	    {
	      for(int entryLine2 = 0; entryLine2 < imgData[row+1].size(); ++entryLine2)
		{
		  if(!((imgData[row][entryLine1].max < imgData[row+1][entryLine2].min) || (imgData[row][entryLine1].min > imgData[row+1][entryLine2].max)))
		    {
		      if(imgData[row+1][entryLine2].attached == false)
			{
			  imgData[row+1][entryLine2].blobId = imgData[row][entryLine1].blobId;
			  imgData[row+1][entryLine2].attached = true;
			}
		      else
			{
			  imgData[row][entryLine1].blobId = imgData[row+1][entryLine2].blobId;
			  imgData[row][entryLine1].attached = true;
			}
		    }
		}
	    }
	} 
      
      /* Allocation de la map "blobs" cet map contien les blobs dans la forme de le struc blob*/
      // Sort and group blobs  
      for(int row = 0; row < imgData.size(); ++row)
	{      
	  for(int entry = 0; entry < imgData[row].size(); ++entry)
	    {
	      if(blobs.find(imgData[row][entry].blobId) == blobs.end()) // Blob does not exist yet
		{
		  blob blobData = {{imgData[row][entry].min, row}, {imgData[row][entry].max, row}, false, {0,0}};	      
		  blobs[imgData[row][entry].blobId] = blobData;
		}
	      else	    
		{
		  if(imgData[row][entry].min < blobs[imgData[row][entry].blobId].min.x)
		    
		    blobs[imgData[row][entry].blobId].min.x = imgData[row][entry].min;
		  
		  else if(imgData[row][entry].max > blobs[imgData[row][entry].blobId].max.x)
		    
		    blobs[imgData[row][entry].blobId].max.x = imgData[row][entry].max;
		  
		  if(row < blobs[imgData[row][entry].blobId].min.y)	
	    
		    blobs[imgData[row][entry].blobId].min.y = row;		
  
		  else if(row > blobs[imgData[row][entry].blobId].max.y)		    

		    blobs[imgData[row][entry].blobId].max.y = row;
		}
	      //blobs[imgData[row][entry].blobId].is_valid = false;
	    }
	}
      
      // Calculate center
      for( std::map<unsigned int, blob>::iterator i = blobs.begin(); i != blobs.end(); ++i)
	{
	  (*i).second.center.x = (*i).second.min.x + ((*i).second.max.x - (*i).second.min.x) / 2;
	  (*i).second.center.y = (*i).second.min.y + ((*i).second.max.y - (*i).second.min.y) / 2;
	  
	  int size = ((*i).second.max.x - (*i).second.min.x) * ((*i).second.max.y - (*i).second.min.y);
	  
	  // Print coordinates on image, if it is large enough
	  if(size > size_blob)
	    {
	      (*i).second.is_valid = true;
	    }
	}
      
      /* Map des vecteurs denome "manchas" contenant les taches a colorer*/
      for(int row = 0; row < imgData.size(); ++row)
	{    
	  for(int entry = 0; entry < imgData[row].size(); ++entry)
	    {  
	      int id = imgData[ row][ entry].blobId;
	      if( blobs[id].is_valid)
		{
		  manchas[id].push_back( imgData[ row][ entry]);
		}
	    }
	}
      std::cout << "manchas.size_initial: " << manchas.size() << std::endl;
      if( manchas.size() == 0) return;
      

      
      /*Discriminateur des taches par les bordes gauche et droites*/
      int pos_x, pos_y_L, pos_y_R;
      CvScalar val_L, val_R;
      unsigned char valor;
      count = 0;
      int mancha = 0, linea = 0;
      blob_nul = false;
      valide_map = true;
      for(iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
	{
	  mancha++;
	  linea = 0;
	  vector_blob = iter_map_line->second;
	  vector_blob_size = vector_blob.size();
	  std::cout << "size mancha: " << iter_map_line->second.size() << " mancha #" << mancha << std::endl;
	  for( l = 0; l < vector_blob_size; l++) 
	    {
	      linea++;
	      if( vector_blob[l].min > bord_blob && vector_blob[l].max < simg->width - bord_blob)
		{
		  pos_x = vector_blob[l].row;
		  pos_y_L = vector_blob[l].min - bord_blob;
		  pos_y_R = vector_blob[l].max + bord_blob;
		  valor =  simg->imageData[pos_x*(simg->width) + pos_y_L];
		  val_L = cvGet2D( simg, pos_x, pos_y_L);
		  val_R = cvGet2D( simg, pos_x, pos_y_R);
		  if( val_L.val[0] >= black_thres)
		    {
		      std::cout << "linea L: " << linea << std::endl;
		      count++;
		      valide_map = false;
		      id_refused[count] = iter_map_line->first;
		    }
		  else
		    {
		      if( val_R.val[0] >= black_thres)
			{
			  std::cout << "linea R: " << linea << std::endl;
			  count++;
			  valide_map = false;
			  id_refused[count] = iter_map_line->first;
			}
		    }
		}
	      else
		{
		  count++;
		  valide_map = false;
		  id_refused[count] = iter_map_line->first;
		  std::cout << "ATTENTION: Bord_blob value thickest that distance beetwen image border and blob border" << std::endl;
		}
	      if( !valide_map) 
		{
		  blob_nul = true;
		  break;
		}
	    }
	  valide_map = true;
	}
      if( blob_nul)
	{
	  for( l = 0 ; l < count + 1; l++)
	    { 
	      manchas.erase(id_refused[l]);
	    }
	}
      std::cout << "map size_left_right: " << manchas.size() << std::endl;   
      if( manchas.size() == 0) return;   
      

      
      /* Discriminateur des taches par les bordes superieur et inferieur */
      count = 0;
      blob_nul = false;
      for(iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
	{
	  valide_map = true;
	  vector_blob = iter_map_line->second;
	  vector_blob_size = vector_blob.size();
	  int fila_up = vector_blob[0].row;
	  int fila_down = vector_blob[vector_blob_size - 1].row;
      	  if( fila_up > bord_blob && fila_down < simg->height - bord_blob)
	    {
	      int y;
	      for( y = vector_blob[0].min; y < vector_blob[0].max + 1; y++)
		{
		  CvScalar a;
		  a = cvGet2D( simg, fila_up - bord_blob, y);
		  if( a.val[0] >= black_thres) 
		    {
		      count++;
		      blob_nul = true;
		      valide_map = false;
		      id_refused[count] = iter_map_line->first;
		      break;
		    }
		}
	      if( valide_map)
		{
		  int yy;
		  for( yy = (vector_blob[vector_blob_size - 1].min); yy < (vector_blob[vector_blob_size -1].max) + 1; yy++)
		    {
		      CvScalar a;
		      a = cvGet2D( simg, fila_down + bord_blob, yy);
		      if( a.val[0] >= black_thres) 
			{
			  count++;
			  blob_nul = true;
			  id_refused[count] = iter_map_line->first;
			  break;
			} 
		    }
		}
	    }
	  else
	    {
	      count++;
	      blob_nul = true;
	      id_refused[count] = iter_map_line->first;
	      std::cout << "ATTENTION: Bord_blob value thickest that distance beetwen image border and blob border" << std::endl;
	    }
	}
      if( blob_nul)
	{
	  for( l = 0 ; l < count + 1; l++)
	    { 
	      manchas.erase(id_refused[l]);
	    }
	}
      if( manchas.size() == 0) return;      
      
      
      
      /* Recouvrement des taches blanches */
      int x, y, xx, yy, ii = 0, jj = 0;
      CvScalar a_up, a_down, a_left, a_right , d, bord_w;
      int bx, by, cxy, p_up, p_down, p_left, p_right;
      for(iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
	{
	  vector_blob = iter_map_line->second;
	  vector_blob_size = vector_blob.size();
	  for( l = 0; l < vector_blob_size; l++)
	    {
	      x = vector_blob[l].row;
	      if( x == vector_blob[0].row )
		{
		  for( yy = (vector_blob[0].min) - bord_blob; yy < (vector_blob[0].max) + bord_blob + 1; yy++)
		    {
		      bord_w = cvGet2D( simg, x - bord_blob, yy);
		      for( xx = x - bord_blob; xx < x; xx++)
			{
			  cvSet2D( img, xx, yy, bord_w);
			}
		    } 
		}
	      if( x == vector_blob[vector_blob_size - 1].row)
		{
		  for( yy = (vector_blob[vector_blob_size - 1].min) + bord_blob; yy < (vector_blob[vector_blob_size - 1].max) + bord_blob + 1; yy++)
		    {
		      bord_w = cvGet2D( simg, x + bord_blob, yy);
		      for( xx = x + 1; xx < x + bord_blob + 1; xx++)
			{
			  cvSet2D( img, xx, yy, bord_w);
			}
		    } 
		}
	      for( y = ( vector_blob[l].min) - bord_blob; y < ( vector_blob[l].max) + bord_blob + 1; y++)
		{
		  a_up = cvGet2D( simg, (vector_blob[0].row) - bord_blob, y);
		  a_down = cvGet2D( simg, (vector_blob[vector_blob_size - 1].row) + bord_blob, y);
		  a_left = cvGet2D( simg, x, (vector_blob[l].min) - bord_blob);
		  a_right = cvGet2D( simg, x, (vector_blob[l].max) + bord_blob);
		  bx = (a_up.val[0] + a_down.val[0])/2;
		  by = (a_left.val[0] + a_right.val[0])/2;
		  cxy = (by + bx)/2;
		  d.val[0] = (unsigned char) cxy;
		  cvSet2D( img, x, y, d);
		}
	    }
	}
      //       for( int x = 1; x < simg->width; x++)
      // 	{
      // 	  for( int y = 1; y < simg->height; y++)
      // 	    {
      // 	      CvScalar d;
      // 	      if( x > 10 && x < 30)
      // 		{
      // 		  d.val[0] = 230;
      // 		  //d.val[0] = 10;
      // 		  cvSet2D( img, x, y, d);      
      // 		}
      // 	    }
      // 	}
      //       //std::cout << "width: " << simg->width << " height : " << simg->height << std::endl;
      //       for( int column = 1; column < simg->width; ++column)
      // 	{
      // 	  for( int row = 1; row < simg->height; ++row)
      // 	    {
      // 	      if( column > 10 && column < 30)
      // 		{
      // 		  simg->imageData[ ( row*simg->width) + column] = 230;
      // 		}
      // 	    }
      // 	}

      erShow2Image( "Blob corrrection", img, "image_temoin", simg);
      //while(1){if(cvWaitKey(10) == 27) break;
      //cvDestroyWindow( "Blob correction");
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      //ok = 0;
      std::cout << std::endl;
    }    
  parm->trh_w = (int) white_thres;
  parm->trh_b = (int) black_thres;
  parm->blob_b = size_blob;
  parm->size_b = bord_blob;
  *simg = *img;
  //std::ofstream file( nameInfoFile(INFOFILE), std::ios_base::app );
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Segmentation fonction WhiteBlobCorrection***********\n";
  file << "upper Threshold :------------ " << parm->trh_w << std::endl;
  file << "down Threshold :------------- " << parm->trh_b << std::endl;
  file << "blob border :---------------- " << parm->blob_b << std::endl;
  file << "blob size :------------------ " << parm->size_b << std::endl;
  file << std::endl;
  file << parm; 
}



/* Logique: L'usager marque un petit cercle autour du pixels ou il souhaite realizer le growing.*/
/*L'algorithme cherchee par comparaison a travers une valeur de (seuil) definie par l'usager, si les pixels en haut, en bas , a gauche et a droite du pixel marque initialement respectent ou pas le criteria.
*/ 
void erRegionGrowingUser( IplImage* simg, erRegGrP* parm)
{
  CvRect rect = cvRect( 0,0,0,0);
  IplImage *img, *img_zero;
  int ok =1;
  int num_pix_total, nom_point;
  int reg_size = 1;
  int mindis;
  int mean_point;
  int nom_free = 10000;
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  std::vector< CvPoint> ext_point;
  std::pair< CvPoint, int> mdf_point, cercle;
  std::vector< std::pair< CvPoint, int> > list_mdf_point, abslist_mdf_point;
  std::vector< std::pair< CvPoint, int> >::iterator minlist_mdf_point, inlist_mdf_point; 
  CvPoint point_o, point_n;
  while(ok)
    {
      /** Creation de l'image initial des zeros ou sera enregistre l'image final del growing process**/
      img_zero = cvCreateImage( cvGetSize(simg), simg->depth, simg->nChannels);
      cvZero(img_zero);
      /**Distance min en termes de difference de grey level entre pixels pour considerer el growing**/
      mindis = parm->int_maxdis;
      /**selection du point du depart de la zone de growing**/
      cercle = erCvDebutCurve( simg);
      point_o.x = cercle.first.x + rect.x;
      point_o.y = cercle.first.y + rect.y;
      std::cout << "centro.x: " << cercle.first.x << std::endl;
      std::cout << "centro.y: " << cercle.first.y << std::endl;
      std::cout << "radio:    " << cercle.second << std::endl;
      /** extraction du niveau de gris du pixels selectione**/
      CvScalar mean_point_brut = cvGet2D( simg, point_o.x, point_o.y);      
      mean_point = (int)mean_point_brut.val[0];
      /** nombre total des pixels dans l'image**/
      num_pix_total = simg->width * simg->height;
      /** Definition de la matrice haut-bas, gauche-droite a utiliser pour chercher autour des pixles selectionnes**/
      ext_point.push_back( cvPoint( -1, 0));
      ext_point.push_back( cvPoint( 1, 0));
      ext_point.push_back( cvPoint( 0, -1));
      ext_point.push_back( cvPoint( 0, 1));
      
      /** Tant que la dif. des niveau entre les pixels selectiones et les nouveaux soit inf. au critere et que la taille des pixles selectionne ne depase pas la taille max possible pour la zone growing, chercher des nouveau pixels**/ 
      while( mindis < parm->int_maxdis && reg_size < num_pix_total)
	{
	  /** On balaye haut-bas ,gauche-droite du pixel en question**/
	  for( int l = 1; l <= 4; l++)
	    {
	      point_n.x = point_o.x + ext_point[ l].x;
	      point_n.y = point_o.y + ext_point[ l].y;
	      ext_point.push_back( point_n);
	      /** On verifie que notre nouveau point soie dans l'image**/
	      bool veri_bord = ( point_n.y <= simg->width && point_n.y >= 1 && point_n.x <= simg->height && point_n.x >= 1);
	      /** On prend le niveau de gris du nuveau pixel et on verifie que celui ci ne soie pas zero**/
	      CvScalar a = cvGet2D( img_zero, point_n.x, point_n.y); 
	      bool veri_zero = ( a.val[0] == 0);
	      if( veri_bord && veri_zero)
		{
		  /**Increment du nombre des pixels modifie**/
		  nom_point = nom_point + 1;
		  /**Niveau de gris du pixel**/
		  CvScalar b = cvGet2D( simg, point_n.x, point_n.y);
		  /**construction de la liste pair: avec le pixel en question et leur valeur de gris**/
		  list_mdf_point[ nom_point] = std::make_pair( point_n, (int)b.val[0]);
		  /** Modification de l'image des zeros, par la valeur 1 ou se trouve le pixels en question**/ 
		  CvScalar c;
		  c.val[0] = 1;
		  c.val[1] = 0;
		  c.val[2] = 0;
		  c.val[3] = 0;
		  cvSet2D( img_zero, point_n.x, point_n.y, c); 
		}
	    }
	  /** Verification que la taille initial prevue poru la zone growing soie suffisant**/
	  if( nom_point + 10 > nom_free)
	    {
	      nom_free = nom_free + 10000;
	      for( int ll = nom_point + 1; ll <= nom_free; ll++)
		{
		  list_mdf_point[ ll] = std::make_pair( cvPoint( 0, 0), 0);
		}
	    }
	  /**Creation d'une liste avec les valeurs absoluts de la difference des niveau de gris entre les pixles selectiones et le pixel initial**/
	  for( int lll = 1; lll <= nom_point; lll++)
	    {       
	      abslist_mdf_point[ lll] = std::make_pair( list_mdf_point[ lll].first, abs( list_mdf_point[ lll].second - mean_point));
	    }
	}
      /** Recherche du la valeur min de la liste des valeurs absoluts et le pixels au quelle corrspond**/
      int mindis = abslist_mdf_point.begin()->second;
      for( minlist_mdf_point = abslist_mdf_point.begin()+1; minlist_mdf_point != abslist_mdf_point.end(); ++minlist_mdf_point)
	{
	  if( minlist_mdf_point->second <= mindis)
	    {
	      mindis = minlist_mdf_point->second;
	      inlist_mdf_point = minlist_mdf_point;
	    }
	}
      /** Taille de la region **/
      reg_size = reg_size + 1;
      /** Initiation d'un nouveau point de depart pour le growing, point avec la difference min trouve **/
      /** Valeur de 2 pour le pixel dans la nouvelle image, pour ne pas lui confondre avec les points non modifie avec valeur 0, et celles modifies avec valeur 1 **/
      CvScalar d;
      d.val[0] = 2;
      d.val[1] = 0;
      d.val[2] = 0;
      d.val[3] = 0;
      cvSet2D( img_zero, point_n.x, point_n.y, d);
      *inlist_mdf_point = list_mdf_point[nom_point];
      nom_point = nom_point - 1;
      
      /** Impresion de l'image de zeoros modifie dans l'ecran **/
      erShow2Image( "Growing corrrection", img_zero, "image temoin", simg);
 
      std::cout << " T'es content (Oui 0/Non 1)? ";
      std::cin >> ok;
      std::cout << std::endl;
    }    
  parm->int_maxdis = mindis;
  parm->ini_point = cercle;
  *simg = *img_zero;
  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Segmentation fonction WhiteBlobCorrection***********\n";
  file << "Threshold intensity diff :--- " << parm->int_maxdis << std::endl;
  file << "cordenate X point :---------- " << parm->ini_point.first.x << std::endl;
  file << "cordenate Y point :---------- " << parm->ini_point.first.y << std::endl;
  file << "radius from point :---------- " << parm->ini_point.second << std::endl;
  file << std::endl;
  file << parm; 
}
