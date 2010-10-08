#include <erCv/erCvBase.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/erCvSegmentation.hpp>
#include <iostream>
#include <fstream>

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
  IplImage *temp, *result_img, *img_p;
  erImage *rect_img;
  int type;
  rect_img = (erImage*)img;
  //std::cout << " rect-width:" << parm->rectan.width << " rect-height:" << parm->rectan.height << std::endl;
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
  //std::cout << "width:" << rect_img->width << " height:" << rect_img->height << " depth:" << rect_img->depth << std::endl;
  //std::cout << "width:" << temp->width << " height:" << temp->height << " depth:" << temp->depth << std::endl;
  //std::cout << "width:" << result_img->width << " height:" << result_img->height << " depth:" << result_img->depth << std::endl;
  if( type ==1) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF);
  if( type ==2) cvMatchTemplate( rect_img, temp, result_img, CV_TM_SQDIFF_NORMED);
  if( type ==3) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR);
  if( type ==4) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCORR_NORMED);
  if( type ==5) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF);
  if( type ==6) cvMatchTemplate( rect_img, temp, result_img, CV_TM_CCOEFF_NORMED); 
  /**Conversion de l'image en 32 bit vers 8 bit**/
  img_p  = cvCreateImage( cvGetSize(result_img), IPL_DEPTH_8U, 1);
  erCvConvert32to8( result_img, img_p);
  img = cvCreateImage( cvGetSize(rect_img), IPL_DEPTH_8U, 1);
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
      //erShow2Image("Result_equalize", simg, "image-temoin", img );
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



void erWhiteBlobCorrection( IplImage* simg, erWhitBP* parm)
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
  //img = cvCloneImage(simg);
  std::vector< std::vector<lineBlob> > imgData(simg->width);
  //int ok = 1;
  //while( ok)
  //  {
  img = cvCreateImage( cvGetSize( simg), simg->depth, simg->nChannels);
  cvCopy( simg, img);
  //white_thres = parm->trh_w;
  white_thres = (unsigned char) parm->trh_w;
  //black_thres = parm->trh_b;
  black_thres = (unsigned char) parm->trh_b;
  size_blob = parm->size_b;
  bord_blob = parm->blob_b;
  
  
  
  for(int row = 0; row < simg->height; ++row)
    {
      
      for(int column = 0; column < simg->width; ++column)
	{
	  
	  //unsigned char byte = (unsigned char) imgStream.get();
	  unsigned char byte = (unsigned char) simg->imageData[(row*simg->width)+ column];
	  
	  if(byte >= white_thres)
	    {
	      int start = column;
	      
	      for(;byte >= white_thres; byte = (unsigned char) simg->imageData[(row*simg->width)+ column], ++column);
	      
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
	  blobs[imgData[row][entry].blobId].is_valid = false;
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
  //std::cout << "manchas.size_initial: " << manchas.size() << std::endl;
  
  
  
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
		  count++;
		  valide_map = false;
		  id_refused[count] = iter_map_line->first;
		}
	      else
		{
		  if( val_R.val[0] >= black_thres)
		    {
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
  *simg = *img;
}

