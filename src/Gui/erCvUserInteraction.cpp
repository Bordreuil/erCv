#include <erCv/erCvBase.hpp> 
#include <erCv/Gui/erCvUserInteraction.hpp>
#include <erCv/utilities/erFileUtilities.hpp>
#include<fstream>
static uint n_right_click_rect = 0;
static uint n_right_click_circ = 0;

void on_mouse_cerc( int event, int x, int y, int flags, void* param)
{

  erCercleImg* pru = (erCercleImg*) param;
  switch( event)
    {
//     case CV_EVENT_MOUSEMOVE:
//       {
// 	if( pru->drawing)
// 	  {
// 	    pru->radiusi = cvRound(cvSqrt( (float)(( x - pru->centeri.x)*( x - pru->centeri.x) + ( y - pru->centeri.y)*( y - pru->centeri.y))));
// 	  }
//       }
//       break;

    case CV_EVENT_LBUTTONDOWN:
      {
	if( n_right_click_circ == 1)
	  {pru->radiusi = cvRound(cvSqrt( (float)(( x - pru->centeri.x)*( x - pru->centeri.x) + ( y - pru->centeri.y)*( y - pru->centeri.y))));
	   	cvCircle( pru->image, pru->centeri, pru->radiusi, cvScalar( 0xff, 0x00, 0x00));
		n_right_click_circ=0;
	    break;
	  }
	if( n_right_click_circ == 0)
	  {
	    pru->centeri = cvPoint(x,y);
	    n_right_click_circ+=1;
	    break;
	  }
      }      
//       break;
//     case CV_EVENT_LBUTTONUP:
//       { 
// 	pru->drawing = false;
// 	cvCircle( pru->image, pru->centeri, pru->radiusi, cvScalar( 0xff, 0x00, 0x00));
//       }
//       break;
      //finish = true;

    }
}




void on_mouse_rect3( int event, int x, int y, int flags, void* param)
{
  erImage* pru = (erImage*) param;
  switch( event)
    {
// <<<<<<< .mine
          case CV_EVENT_LBUTTONDOWN:
            if(n_right_click_rect == 1)
      	{
      	pru->rectan.width = x-pru->rectan.x;
       	pru->rectan.height = y-pru->rectan.y;
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
      	n_right_click_rect=0;
      	break;
      	}
            if(n_right_click_rect == 0)
      	{
      	pru->rectan = cvRect( x, y, 0, 0);
      	n_right_click_rect+=1;
            break;
      	}
      
      
      //     }
    case CV_EVENT_MOUSEMOVE:
      {
	// std::cout << "Mouse Moving: " << std::boolalpha << pru->drawing << std::endl;
	if( pru->drawing)
	  {
	    pru->rectan.width = x-pru->rectan.x;
	    pru->rectan.height = y-pru->rectan.y;
	  }
	//	std::cout << "on sort de move\n";
      }
      break;
      
//       // old version break;
//=======
//#ifdef MACOSX
      //>>>>>>> .r43
  //   case CV_EVENT_LBUTTONDOWN:
//       {
//     	pru->drawing = true;
// 	//std::cout << "Left Button down"<< std::boolalpha << pru->drawing << std::endl ;
// 	pru->rectan = cvRect( x, y, 0, 0);
// 	//std::cout << "On sort de button down\n";
//       }
//       break;
      
      
//       // old version break;
//     case CV_EVENT_LBUTTONUP:
//       {
// 	pru->drawing = false;
// 	if( pru->rectan.width < 0)
// 	  {
// 	    pru->rectan.x += pru->rectan.width;
// 	    pru->rectan.width *= -1;
// 	  }
// 	if( pru->rectan.height < 0)
// 	  {
// 	    pru->rectan.y += pru->rectan.height;
// 	    pru->rectan.height *= -1;
// 	  }
// 	cvRectangle( pru, cvPoint( pru->rectan.x, pru->rectan.y), 
// 		     cvPoint( pru->rectan.x + pru->rectan.width, 
// 			      pru->rectan.y + pru->rectan.height), cvScalar( 0xff, 0x00, 0x00));
// 	//draw_box( pru->img, pru->rec);
//       }
//       break;
// <<<<<<< .mine
      
//       // old version break;
//       //finish = true;
//     }
// }
// =======
	
  
//#else
//    case CV_EVENT_MOUSEMOVE:
      //      std::cout << "Mouse Moving: " << std::boolalpha << pru->drawing << std::endl;
      //	if( pru->drawing)
// 	  {
// 	    pru->rectan.width = x-pru->rectan.x;
// 	    pru->rectan.height = y-pru->rectan.y;
// 	  }
// 	//	std::cout << "on sort de move\n";
// 	break;
     
//       // old version break;
//     case CV_EVENT_LBUTTONDOWN:
//     	pru->drawing = true;
// 	//	std::cout << "Left Button down"<< std::boolalpha << pru->drawing << std::endl ;
// 	pru->rectan = cvRect( x, y, 0, 0);
// 	//	std::cout << "On sort de button down\n";
// 	break;
      
      
//       // old version break;
//     case CV_EVENT_LBUTTONUP:
      
// 	pru->drawing = false;
// 	if( pru->rectan.width < 0)
// 	  {
// 	    pru->rectan.x += pru->rectan.width;
// 	    pru->rectan.width *= -1;
// 	  }
// 	if( pru->rectan.height < 0)
// 	  {
// 	    pru->rectan.y += pru->rectan.height;
// 	    pru->rectan.height *= -1;
// 	  }
// 	  cvRectangle( pru, cvPoint( pru->rectan.x, pru->rectan.y), 
// 		       cvPoint( pru->rectan.x + pru->rectan.width, 
// 				pru->rectan.y + pru->rectan.height), cvScalar( 0xff, 0x00, 0x00));
// 	  //draw_box( pru->img, pru->rec);
// 	  break;
      
//       // old version break;
//       //fi
// 	  //>>>>>>> .r43


// #endif
	}
};



// <<<<<<< .mine

// =======


// >>>>>>> .r43
/* Definition and isolating the interesting zone by user */
IplImage* erDef_ROIuser( erImage* simag, CvRect* rect, bool with_trackbar)
{
  IplImage *img_trans, *imag; 
  std::string name = INFOFILE;
  name+= ".txt";
  const char* nomb = name.c_str();
  simag->drawing = false;
  img_trans = cvCreateImage( cvGetSize(simag), simag->depth, simag->nChannels);
  cvCopy( simag, img_trans);
  cvNamedWindow( "Draw_ROI", 0);
  if( !with_trackbar)
    {
      std::cout << "width du zone d'interet: ";
      //std::cin >> simag->rectan.width;
      simag->rectan.width = 140;
      std::cout << std::endl;
      std::cout << "height du zone d'interet: ";
      //std::cin >> simag->rectan.height;
      simag->rectan.height = 89;
      std::cout << std::endl;
      std::cout << "Point X coin sup gauche de la zone: ";
      //std::cin >> simag->rectan.x;
      simag->rectan.x = 160;
      std::cout << std::endl;
      std::cout << "Point Y coin sup gauche de la zone: ";
      //std::cin >> simag->rectan.y;
      simag->rectan.y = 126;
      std::cout << std::endl;
      cvRectangle( simag, cvPoint( simag->rectan.x, simag->rectan.y), 
		   cvPoint( simag->rectan.x + simag->rectan.width, 
			    simag->rectan.y + simag->rectan.height), cvScalar( 0xff, 0x00, 0x00));
    }
  else
    {
      cvSetMouseCallback( "Draw_ROI", on_mouse_rect3,  (void*) simag );
      while( 1)
	{
	  if( simag->drawing)
	    {
	      cvRectangle( simag, cvPoint( simag->rectan.x, simag->rectan.y), 
			   cvPoint( simag->rectan.x + simag->rectan.width, 
				    simag->rectan.y + simag->rectan.height), cvScalar( 0xff, 0x00, 0x00));
	    }
	  cvShowImage( "Draw_ROI", simag);
	  if( cvWaitKey( 700) == 27) break;
	}
      cvDestroyWindow("Draw_ROI");
    }
  
  cvSetImageROI( img_trans, simag->rectan);

  imag = cvCreateImage( cvGetSize(img_trans), img_trans->depth, img_trans->nChannels);
  cvCopy( img_trans, imag);
  *rect = simag->rectan;

  std::cout << "***********Zone d'interet principal** ***********\n";
  std::cout << "Rect(with):------------ " << rect->width << std::endl;
  std::cout << "Rect(height):---------- " << rect->height << std::endl;
  std::cout << "Rect(posX):------------ " << rect->x << std::endl;
  std::cout << "Rect(posY):------------ " << rect->y << std::endl;


  std::ofstream file( nomb, std::ios_base::app );
  file << "***********Zone d'interet principal** ***********\n";
  file << "Rect(with):------------ " << rect->width << std::endl;
  file << "Rect(height):---------- " << rect->height << std::endl;
  file << "Rect(posX):------------ " << rect->x << std::endl;
  file << "Rect(posY):------------ " << rect->y << std::endl;
  file << std::endl;

  return imag;
};





/* Definition and isolating the interesting zone in a pictures series*/
IplImage* erDef_ROI( erImage* simag, CvRect* rect)
{
  IplImage *imag;
  simag->rectan = *rect;
  cvSetImageROI( simag, simag->rectan);
  imag = cvCreateImage( cvGetSize(simag), simag->depth, simag->nChannels);
  cvCopy( simag, imag);
  return imag;
}






/* Reset of ROI and reconstitution of images */
void erRes_ROI_recons( IplImage* simag)
{
  //IplImage* result_img;
  
  //cvSetImageROI( result_img, temp.rectan);
  //cvAddWeighted( temp2.image, 1., result_img, 0., 1., result_img);
  cvResetImageROI( simag);
  //temp1 = temp;
  //cvNamedWindow( "final_image", 0);
  //cvShowImage( "final_image", simag->image);
  //cvResetImageROI( result_img);
  //cvWaitKey();
  //cvDestroyWindow( "final_image");
}


/*Rectangle demarquant le debut de la curve d interet */
std::pair< CvPoint, int> erCvDebutCurve( IplImage *simag)
{
  erCercleImg cer_img;
  cer_img.drawing = false;
  cer_img.image = cvCreateImage( cvGetSize(simag), simag->depth, simag->nChannels);
  cvCopy( simag, cer_img.image);
  cvNamedWindow( "Marquez le debut curve", 0);
  cvSetMouseCallback( "Marquez le debut curve", on_mouse_cerc,  (void*) &cer_img );
  while( 1)
    {
      // if( cer_img.drawing)
// 	{
// 	  cvCircle( cer_img.image, cer_img.centeri, cer_img.radiusi, cvScalar( 0xff, 0x00, 0x00));
// 	  //cvRectangle( img, cvPoint( img->rectan.x, img->rectan.y), 
// 	  //	       cvPoint( img->rectan.x + img->rectan.width, 
// 	  //		img->rectan.y + img->rectan.height), cvScalar( 0xff, 0x00, 0x00));
// 	}
      cvShowImage( "Marquez le debut curve", cer_img.image);
      if( cvWaitKey( 700) == 27) break;
    }
  cvDestroyWindow("Draw_ROI");
  return std::make_pair( cer_img.centeri, cer_img.radiusi);
}  

