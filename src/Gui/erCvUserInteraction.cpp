#include <erCv/erCvBase.hpp> 
#include <erCv/Gui/erCvUserInteraction.hpp>
#include <erCv/utilities/erFileUtilities.hpp>







void on_mouse_rect3( int event, int x, int y, int flags, void* param)
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





/* Definition and isolating the interesting zone by user */
void erDef_ROIuser( erImage* simag)
{
  IplImage *img_trans; 
  
  simag->drawing = false;

  img_trans = cvCloneImage( simag);
      
  cvNamedWindow( "Draw_ROI", 0);
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
  
  cvSetImageROI( img_trans, simag->rectan);
  cvSetImageROI( simag, simag->rectan);
  cvCopy( img_trans, simag);
  cvResetImageROI( img_trans);
}





/* Definition and isolating the interesting zone in a pictures series*/
void erDef_ROI( erImage* simag)
{
  cvSetImageROI( simag, simag->rectan);
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
