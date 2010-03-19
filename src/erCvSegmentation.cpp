#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <iostream>
#include <fstream>





// void erCvDifferencing( IplImage* simg, IplImage* ximg)
// {
//   IplImage *imge;
//   imge = cvCreateImage( cvGetSize(ximg), ximg->depth, ximg->nChannels);
//   cvAbsDiff( ximg, simg, imge);
//   //simg =  cvCloneImage( imge);
//   cvThreshold( imge, simg, 15, 255, CV_THRESH_BINARY);
// }



IplImage* erCvTemplate( IplImage* img, erTemplP* parm)
{
  IplImage *temp, *result_img,*img_p;
  erImage *rect_img;
  int type;
  rect_img = (erImage*)img;
  rect_img->rectan = parm->rectan;
  type = parm->type;
   
  /**Cet configuration est mise en place pour empecher l'aparition des multiples rectangles lors du desin**/
  cvSetImageROI( rect_img, rect_img->rectan);
  
  temp = cvCreateImage( cvGetSize( rect_img), rect_img->depth, rect_img->nChannels);
  cvCopy( rect_img, temp);
  cvResetImageROI( rect_img);
 
  /**Construction de l'image ou les resultats seront exposées**/
  int patchx = rect_img->rectan.width;                
  int patchy = rect_img->rectan.height;
  int iwidth = rect_img->width - patchx + 1; 
  int iheight = rect_img->height - patchy + 1;
  result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
  cvZero( result_img);
  
  if( type ==1) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF);
  if( type ==2) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF_NORMED);
  if( type ==3) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR);
  if( type ==4) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR_NORMED);
  if( type ==5) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF);
  if( type ==6) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF_NORMED); 
  /**Conversion de l'image en 32 bit vers 8 bit**/
  img_p  = cvCreateImage( cvGetSize(result_img), IPL_DEPTH_8U, 1);
  erCvConvert32to8( result_img, img_p);
  img = cvCreateImage( cvGetSize(parm->image), IPL_DEPTH_8U, 1);
  cvResize( img_p, img, CV_INTER_CUBIC);
  return img; 
}





// /*--------- Methode de segmentation CallBackProject (comparaison par regions avec histogrames) ---------*/
// IplImage* erCvCallBackPatchProject( IplImage *img)
// {
//   IplImage *img_temp, *result_img, *temp;
//   erImage *rect_img = (erImage*) img;
//   int type[4];
  
//   img_temp = cvCloneImage( img);
//   rect_img->drawing = false;
  
//   /**Construction du rectangle de la zone d'interet**/
//   cvNamedWindow( "Draw-interesting-zone", 0);
//   cvSetMouseCallback( "Draw-interesting-zone", on_mouse_rect2, (void*) &rect_img);
//   while( 1)
//     {
//       if( rect_img->drawing)
// 	{
// 	  cvRectangle( img_temp, cvPoint( rect_img->rectan.x, rect_img->rectan.y), 
// 		       cvPoint( rect_img->rectan.x + rect_img->rectan.width, 
// 				rect_img->rectan.y + rect_img->rectan.height), cvScalar( 0xff, 0x00, 0x00));
// 	}
//       cvShowImage( "Draw-interesting-zone", img_temp);
//       if( cvWaitKey( 700) ==27) break;
//     }
//   cvDestroyWindow( "Draw-interesting-zone");
//   cvSetImageROI( rect_img, rect_img->rectan);
//   cvSaveImage( "ipru.bmp", rect_img);
//   temp = cvLoadImage( "ipru.bmp", CV_LOAD_IMAGE_GRAYSCALE);
//   //cvResetImageROI(rect_img.image);

//   /**Creation de l'image HSV**/
//   IplImage *hsv[2], *h_plan[2], *s_plan[2], *v_plan[2], *plan[2][3]; 
//   //cvSetImageROI( fuente_img2, box);
//   std::cout << "colorModel de la imagen: " << rect_img->colorModel << std::endl;
//   std::cout << std::endl;
//   std::cout << "Type de conversion de color de l'image: " << std::endl;
//   std::cout << "1->XYZ  2->HSV  3->HLS  4->Lab  5->YCrCb: ";
//   std::cin >> type[1];
//   for( int i = 0; i < 2; i++)
//     {
//       if( i==1) cvResetImageROI( rect_img);
//       hsv[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 3);      
//       if( type[1] ==1) cvCvtColor( rect_img, hsv[i], CV_RGB2XYZ);
//       if( type[1] ==2) cvCvtColor( rect_img, hsv[i], CV_RGB2HSV);
//       if( type[1] ==3) cvCvtColor( rect_img, hsv[i], CV_RGB2HLS);
//       if( type[1] ==4) cvCvtColor( rect_img, hsv[i], CV_RGB2Lab);
//       if( type[1] ==5) cvCvtColor( rect_img, hsv[i], CV_RGB2YCrCb);
//       h_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
//       s_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
//       v_plan[i] = cvCreateImage( cvGetSize( rect_img), rect_img->depth, 1);
//       plan[i][0] = h_plan[i];
//       plan[i][1] = s_plan[i];      
//       plan[i][2] = v_plan[i];
//       cvCvtPixToPlane( hsv[i], h_plan[i], s_plan[i], v_plan[i], 0);
//     }

//   /**Construction de l'histograma**/
//   std::cout << "PRUEBA" << std::endl;
//   CvHistogram* hist;
//   int h_bin = 15, s_bin = 15, v_bin = 15;
//   int hist_size[] = { h_bin, s_bin, v_bin};
//   float rang_h[] = { 0, 360};
//   float rang_s[] = { 0, 1};
//   float rang_v[] = { 0, 1};
//   float *rang[] = { rang_h, rang_s, rang_v};  
//   hist = cvCreateHist( 3, hist_size, CV_HIST_ARRAY, rang, 1);
//   cvCalcHist( plan[0], hist, 0, 0);
//   //cvNormalizeHist( hist, 1.0 );

//   /**Construction de l'image ou les resultats seront exposées**/
//   int patchx = rect_img->rectan.width;                
//   int patchy = rect_img->rectan.height;
//   int iwidth = rect_img->width - patchx + 1; 
//   int iheight = rect_img->height - patchy + 1;
//   result_img = cvCreateImage( cvSize(iwidth,iheight),32,1);
//   cvZero(result_img);

//   /**Construction du  BackProjectPatch**/
//   std::cout << "Type de coparaison entre les histogrames dans le BackProjectPatch" << std::endl;
//   std::cout << "1->CORREL  2->CHISQR  3->INTERSECT  4->BHATTACHARYYA :";
//   std::cin >> type[0]; 
//   CvSize patch = cvSize(patchx,patchy);
//   if( type[0]== 1) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CORREL, 1.0);
//   if( type[0]== 2) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_CHISQR, 1.0);
//   if( type[0]== 3) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_INTERSECT, 1.0);
//   if( type[0]== 4) cvCalcBackProjectPatch( plan[1], result_img, patch, hist, CV_COMP_BHATTACHARYYA, 1.0);
  
//   /**Exposition de l'image des resultats**/
//   cvNamedWindow( "Back_Projection", 0);
//   cvShowImage( "Back_Projection", result_img); 
//   while( 1)
//     {
//       if(cvWaitKey(1)==27) break;
//     }
//   cvDestroyWindow( "Back_Projection");
//   return result_img;
// }



/*--------- Methode de equalisation des histogrames (celle ci permet d'amellier le contraste de l'image) ---------*/
void erCvEqualizeHist( IplImage* simg, erEqualP* param)
{
  IplImage* img;
  int usar;
  usar = param->applic;
  img = cvCloneImage(simg);
  if( usar == 0)
    {
      cvEqualizeHist( simg, img);
      erShow2Image("Result_equalize", simg, "image-temoin", img );
    }
  //erShowImage("Result_equalize", img );
  *simg = *img;
}



void erCvPyramid( IplImage* simg, erPyramP* parm )
{
  int threshold[2], level;
  double a[2];
  CvSeq* comp = NULL;
  CvMemStorage* stg = NULL;
  threshold[0] = 1;
  threshold[1] = 1;
  threshold[0] = parm->trh1;
  threshold[1] = parm->trh2;
  level = parm->levl;
  std::cout << "pyr_0: " << threshold[0] << std::endl;
  std::cout << "pyr_1: " << threshold[1] << std::endl;
  std::cout << "level: " << level << std::endl;
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
  cvPyrSegmentation(simg, simg, stg, &comp, level, a[0], a[1]);
}
