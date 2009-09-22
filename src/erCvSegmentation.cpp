#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <iostream>
#include <fstream>





void on_mouse_rect2( int event, int x, int y, int flags, void* param)
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


void erCvDifferencing( IplImage* simg, IplImage* ximg)
{
  IplImage *imge;
  imge = cvCreateImage( cvGetSize(ximg), ximg->depth, ximg->nChannels);
  cvAbsDiff( ximg, simg, imge);
  simg =  cvCloneImage( imge);
  cvThreshold( imge, simg, 15, 255, CV_THRESH_BINARY);
}



IplImage* erCvTemplate( IplImage* img)
{
  IplImage *img_temp, *result_img, *temp;
  erImage* rect_img = (erImage*) img;
  int type[4];
   
  img_temp = cvCloneImage( img);
  rect_img->drawing = false;
  
  /**Construction du rectangle de la zone d'interet**/
  cvNamedWindow( "Designer la zone patron ou template", 0);
  cvSetMouseCallback( "Draw-interesting-zone", on_mouse_rect2, (void*) &rect_img);
  while( 1)
    {
      if( rect_img->drawing)
	{
	  cvRectangle( img_temp, cvPoint( rect_img->rectan.x, rect_img->rectan.y), 
		       cvPoint( rect_img->rectan.x + rect_img->rectan.width, 
				rect_img->rectan.y + rect_img->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	}
      cvShowImage( "Designer la zone patron ou template", img_temp);
      if( cvWaitKey( 700) ==27) break;
    }
  cvDestroyWindow( "Designer la zone patron ou template");
  
  //---------NOTA REVISAR ESTA CONFIGURACION de imagenes entre:  img_temp y rect_img------------------------
  cvSetImageROI( img_temp, rect_img->rectan);
  cvSetImageROI( rect_img, rect_img->rectan);
  cvCopy( img_temp, rect_img);
  cvResetImageROI( img_temp);
  
  //cvSetImageROI( rect_img, rect_img.rectan);
  cvSaveImage( "ipru.bmp", rect_img);
  temp = cvLoadImage( "ipru.bmp", CV_LOAD_IMAGE_GRAYSCALE);
  cvResetImageROI( rect_img);
  
  /**Construction de l'image ou les resultats seront exposées**/
  int patchx = rect_img->rectan.width;                
  int patchy = rect_img->rectan.height;
  int iwidth = rect_img->width - patchx + 1; 
  int iheight = rect_img->height - patchy + 1;
  result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
  cvZero( result_img);
  
  /**Construction du template (segmentation)**/
  std::cout << "Introduire le type de comparaison a effectuer avec le template" << std::endl;
  std::cout << "1->SQDIFF  2->SQDIFF_NORMED  3->CCORR  4->CCORR_NORMED  5->CCOEFF  6->CCOEFF_NORMED: ";
  std::cin >> type[2];
  if( type[2] ==1) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF);
  if( type[2] ==2) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF_NORMED);
  if( type[2] ==3) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR);
  if( type[2] ==4) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR_NORMED);
  if( type[2] ==5) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF);
  if( type[2] ==6) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF_NORMED); 
  
  /**Exposition de l'image des resultats**/
  cvNamedWindow( "Back_Projection", 0);
  cvShowImage( "Back_Projection", result_img); 
  while( 1)
    {
      if(cvWaitKey(1)==27) break;
    }
  cvDestroyWindow( "Back_Projection"); 
  return result_img;
}





/*--------- Methode de segmentation CallBackProject (comparaison par regions avec histogrames) ---------*/
IplImage* erCvCallBackPatchProject( IplImage *img)
{
  IplImage *img_temp, *result_img, *temp;
  erImage *rect_img = (erImage*) img;
  int type[4];
  
  img_temp = cvCloneImage( img);
  rect_img->drawing = false;
  
  /**Construction du rectangle de la zone d'interet**/
  cvNamedWindow( "Draw-interesting-zone", 0);
  cvSetMouseCallback( "Draw-interesting-zone", on_mouse_rect2, (void*) &rect_img);
  while( 1)
    {
      if( rect_img->drawing)
	{
	  cvRectangle( img_temp, cvPoint( rect_img->rectan.x, rect_img->rectan.y), 
		       cvPoint( rect_img->rectan.x + rect_img->rectan.width, 
				rect_img->rectan.y + rect_img->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	}
      cvShowImage( "Draw-interesting-zone", img_temp);
      if( cvWaitKey( 700) ==27) break;
    }
  cvDestroyWindow( "Draw-interesting-zone");
  cvSetImageROI( rect_img, rect_img->rectan);
  cvSaveImage( "ipru.bmp", rect_img);
  temp = cvLoadImage( "ipru.bmp", CV_LOAD_IMAGE_GRAYSCALE);
  //cvResetImageROI(rect_img.image);

  /**Creation de l'image HSV**/
  IplImage *hsv[2], *h_plan[2], *s_plan[2], *v_plan[2], *plan[2][3]; 
  //cvSetImageROI( fuente_img2, box);
  std::cout << "colorModel de la imagen: " << rect_img->colorModel << std::endl;
  std::cout << std::endl;
  std::cout << "Type de conversion de color de l'image: " << std::endl;
  std::cout << "1->XYZ  2->HSV  3->HLS  4->Lab  5->YCrCb: ";
  std::cin >> type[1];
  for( int i = 0; i < 2; i++)
    {
      if( i==1) cvResetImageROI( rect_img);
      hsv[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 3);      
      if( type[1] ==1) cvCvtColor( rect_img, hsv[i], CV_RGB2XYZ);
      if( type[1] ==2) cvCvtColor( rect_img, hsv[i], CV_RGB2HSV);
      if( type[1] ==3) cvCvtColor( rect_img, hsv[i], CV_RGB2HLS);
      if( type[1] ==4) cvCvtColor( rect_img, hsv[i], CV_RGB2Lab);
      if( type[1] ==5) cvCvtColor( rect_img, hsv[i], CV_RGB2YCrCb);
      h_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
      s_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
      v_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
      plan[i][0] = h_plan[i];
      plan[i][1] = s_plan[i];      
      plan[i][2] = v_plan[i];
      cvCvtPixToPlane( hsv[i], h_plan[i], s_plan[i], v_plan[i], 0);
    }

  /**Construction de l'histograma**/
  std::cout << "PRUEBA" << std::endl;
  CvHistogram* hist;
  int h_bin = 15, s_bin = 15, v_bin = 15;
  int hist_size[] = { h_bin, s_bin, v_bin};
  float rang_h[] = { 0, 360};
  float rang_s[] = { 0, 1};
  float rang_v[] = { 0, 1};
  float *rang[] = { rang_h, rang_s, rang_v};  
  hist = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, rang, 1);
  cvCalcHist( plan[0], hist, 0, 0);
  //cvNormalizeHist( hist, 1.0 );

  /**Construction de l'image ou les resultats seront exposées**/
  int patchx = rect_img->rectan.width;                
  int patchy = rect_img->rectan.height;
  int iwidth = rect_img->width - patchx + 1; 
  int iheight = rect_img->height - patchy + 1;
  result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
  cvZero(result_img);

  /**Construction du  BackProjectPatch**/
  std::cout << "Type de coparaison entre les histogrames dans le BackProjectPatch" << std::endl;
  std::cout << "1->CORREL  2->CHISQR  3->INTERSECT  4->BHATTACHARYYA :";
  std::cin >> type[0]; 
  CvSize patch = cvSize(patchx,patchy);
  if( type[0]== 1) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CORREL, 1.0);
  if( type[0]== 2) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CHISQR, 1.0);
  if( type[0]== 3) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_INTERSECT, 1.0);
  if( type[0]== 4) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_BHATTACHARYYA, 1.0);
  
  /**Exposition de l'image des resultats**/
  cvNamedWindow( "Back_Projection", 0);
  cvShowImage( "Back_Projection", result_img); 
  while( 1)
    {
      if(cvWaitKey(1)==27) break;
    }
  cvDestroyWindow( "Back_Projection");
  return result_img;
}
