#include <iostream>
#include <fstream>
#include <erCv/erCv.hpp>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <utility>
#include "cv.h"
#include "highgui.h"

using namespace std;

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

// Gueule de l interface pour etre cabler dans python
// Est ce qu il ne faut pas prevoir le niveau de seuillage en parametre d entree
//bool erDetectBlobs(std::string,std::string);
bool detectBlobs(IplImage* frame, IplImage* finalFrame)
{
  unsigned char threshold2 = 120, threshold = 185, byte, byte2;  
  int blobCounter = 0, blob_bord = 5, isize = 100;
  std::map<unsigned int, blob> blobs;
  std::map<unsigned int, std::vector<lineBlob> > manchas;
  //std::map<unsigned int, std::pair<std::vector<lineBlob>, blob> > taches;
  std::map<unsigned int, std::vector<lineBlob> >::iterator iter_map_line;
  //std::map<unsigned int, std::pair< std::vector< lineBlob>, blob> >::iterator iter_map_pair;
  std::vector<lineBlob>::iterator iter_vector_line;
  //unsigned char threshold = ithreshold;
  
  
  vector< vector<lineBlob> > imgData(frame->width);
  //std::cout << "chanels: " << frame->nChannels << "   depth: " << frame->depth << std::endl;
  for(int row = 0; row < frame->height; ++row)
    {
      
      for(int column = 0; column < frame->width; ++column)
	{
	  //unsigned char byte = (unsigned char) imgStream.get();
	  byte =  (unsigned char) frame->imageData[ ( row * frame->width) + column];
	  //std::cout << "column: " << column << "   row: " << row << std::endl;
	  //unsigned char byte2 = (unsigned char) frame->imageData[(row*frame->width)+ (column-1)];
	  //std::cout << "byte: " << byte << std::endl;
	  if(byte >= threshold && column > blob_bord)
	    {
	      byte2 = (unsigned char) frame->imageData[ ( row * frame->width) + ( column - blob_bord)];
	      //std::cout << "byte2: " << byte << std::endl;
	      //std::cout << "premier" << std::endl;
	      if( byte2 <= threshold2)
		{		
		  //std::cout << "seconde: " << std::endl;
		  int start = column;
		  do
		    {
		      column++;
		      byte = (unsigned char) frame->imageData[ ( row * frame->width) + column];
		      if( column >= (frame->width - blob_bord)) break;
		    }
		  while( byte >= threshold);
		 
		  if(  (unsigned char) frame->imageData[ ( row * frame->width) + (column + blob_bord)] <= threshold2)
		    {
		      
		      //for(;byte >= threshold; byte = (unsigned char) frame->imageData[(row*frame->width)+ column], ++column);
		      
		      int stop = column-1;
		      lineBlob lineBlobData = {start, stop, blobCounter, row, false};
		      //std::cout << "row: " << row << "   column: " << column << std::endl;
		      //std::cout << "row: " << row << "   start: " << start << std::endl;
		      //std::cout << "row: " << row << "   stop: " << stop << std::endl;
		      //std::cout << "row: " << row << "   blobCounter: " << blobCounter << std::endl;
		      //std::cout << "       "  << std::endl;
		      imgData[row].push_back(lineBlobData);

		      blobCounter++;
		    }
		}
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


  /* C'est une modification fait par EDWARD ROMERO______________________________________________________    */
  /* Module d'ecriture ou de changement de la couleur de la tache blanche en noir  */
  /* Attention cet module doit etre place apres la creation de la map "taches"
  //std::cout << "imgData.size: " << imgData.size() << "  image->with: " << frame->width << "  image finale- width: " << finalFrame->width << std::endl;
  //   for( int row2=0; row2 < imgData.size(); row2++)
  //     {
  //       for( int entry=0; entry < imgData[row2].size(); entry++)
  // 	{
  // 	  int column2 = 0;
  // 	  //std::cout << "imgData.min: " <<  imgData[ row2][entry].min << "  imgData.max: " << imgData[ row2][entry].max << std::endl;
  // 	  do
  // 	    {
  // 	      //std::cout << "imageData: " <<  finalFrame->imageData[ (row2 * finalFrame->width) + imgData[ row2][entry].min + column2] << " get2D: " << cvGet2D( finalFrame, row2, imgData[ row2][entry].min + column2).val[0] << std::endl;
  // 	      //std::cout << "imgData.min: " <<  imgData[ row2][entry].min << "  imgData.max: " << imgData[ row2][entry].max << std::endl;
  // 	      CvScalar a;
  // 	      a.val[0] = (int) threshold2;
  // 	      cvSet2D( finalFrame, row2, imgData[ row2][entry].min + column2, a);
  // 	      //finalFrame->imageData[ ( row2 * finalFrame->width) + imgData[ row2][entry].min + column2] = threshold2;
  // 	      column2++;
  // 	      //std:cout << "HOLA " << imgData[ row2][entry].min + column2 << std::endl;
  // 	    }
  // 	  while( column2 != imgData[ row2][entry].max - imgData[ row2][ entry].min);
  // 	  //std::cout << "row: " << row2 << "  entry: " << entry << "  blobId: " << imgData[row2][entry].blobId << std::endl;
  // 	  //std::cout << "row: " << row2 << std::endl;
  // 	  //std::cout << "entry: " << entry << std::endl;
  // 	  //std::cout << "blobId: " << imgData[row2][entry].blobId << std::endl;
  // 	  //std::cout << " " << std::endl;
  // 	}
  //     }
  
  
  
  /* Allocation de la map "blobs" cet map contien les blobs dans la forme de le struc blob*/
  // Sort and group blobs  
  for(int row = 0; row < imgData.size(); ++row)
    {      
      for(int entry = 0; entry < imgData[row].size(); ++entry)
	{
	  if(blobs.find(imgData[row][entry].blobId) == blobs.end()) // Blob does not exist yet
	    {
	      //std::cout << "row: " << row << std::endl;
	      //std::cout << "blobId: " << imgData[row][entry].blobId << std::endl;
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
 std::cout << "map size: " << blobs.size() << std::endl;
  
  
  
 //<<<<<<< .mine
  /* Fusion du map "blobs" avec la map "manchas" dans une seule map<int, pair> de nom "taches" */
  //std::cout << "map size: " << manchas.size() << std::endl;
  //for(int row = 0; row < imgData.size(); ++row)
  //  {    
  //    for(int entry = 0; entry < imgData[row].size(); ++entry)
  //	{  
  //for( iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
    //  {
      //taches[].push_back( std::make_pair( iter_map_line->second, blobs[iter_map_line->first]));
      // taches[ iter_map_line->first].push_back( std::make_pair( iter_map_line->second, blobs[iter_map_line->first]));
	  //taches[ iter_map_line->first].first.push_back( std::make_pair( iter_map_line->second, blobs[iter_map_line->first]));  
	  //  }
  //}
  //}
  //std::cout << "map size: " << taches.size() << std::endl;
  
  
  //=======
    //>>>>>>> .r119
  // Calculate center
  for(map<unsigned int, blob>::iterator i = blobs.begin(); i != blobs.end(); ++i)
    {
      (*i).second.center.x = (*i).second.min.x + ((*i).second.max.x - (*i).second.min.x) / 2;
      (*i).second.center.y = (*i).second.min.y + ((*i).second.max.y - (*i).second.min.y) / 2;
      
      int size = ((*i).second.max.x - (*i).second.min.x) * ((*i).second.max.y - (*i).second.min.y);
      
      // Print coordinates on image, if it is large enough
      if(size > isize)
	{
	  (*i).second.is_valid = true;
	  CvFont font;
	  cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 1.0, 1.0, 0, 1, CV_AA);
	  
	  char textBuffer[128];
	  
	  // Draw crosshair and print coordinates (just for debugging, not necessary for later multi-touch use)
	  cvLine(finalFrame, cvPoint((*i).second.center.x - 5, (*i).second.center.y), cvPoint((*i).second.center.x + 5, (*i).second.center.y), cvScalar(0, 0, 153), 1);
	  
	  cvLine(finalFrame, cvPoint((*i).second.center.x, (*i).second.center.y - 5), cvPoint((*i).second.center.x, (*i).second.center.y + 5), cvScalar(0, 0, 153), 1);
	  
	  sprintf(textBuffer, "(%d, %d)", (*i).second.center.x, (*i).second.center.y);
	  
	  cvPutText(finalFrame, textBuffer, cvPoint((*i).second.center.x + 5, (*i).second.center.y - 5), &font, cvScalar(0, 0, 153));
	  
	  cvRectangle(finalFrame, cvPoint((*i).second.min.x, (*i).second.min.y), cvPoint((*i).second.max.x, (*i).second.max.y), cvScalar(0, 0, 153), 1);
	  
	  // Show center point
	  //cout << "(" << (*i).second.center.x << ", " << (*i).second.center.y << ")" << endl;
	}
    }

  /* Map des vecteurs appele "manchas" par Edward ROMERO */
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
  /* Discriminateur des taches par les bordes superieur et inferieur */
  //  for( iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
  //{
      // iter_vector_line
  //}
  int x;
  for(iter_map_line = manchas.begin(); iter_map_line != manchas.end(); iter_map_line++)
    {
      std::cout << "blobId: " << iter_map_line->first << std::endl;
      for( iter_vector_line = (iter_map_line->second).begin(); iter_vector_line != (iter_map_line->second).end(); iter_vector_line++)
	{	  
	  std::cout << "row: " << iter_vector_line->row << "  blobId: " << iter_vector_line->blobId << std::endl;
	  std::cout << "min: " << iter_vector_line->min << "  max: " << iter_vector_line->max << std::endl;
	  for( x = iter_vector_line->min; x < iter_vector_line->max + 1; x++)
	    {

	      //std::cout << "x: " << x << std::endl;
	      CvScalar a;
	      a.val[0] = (int) threshold2;
   	      cvSet2D( finalFrame, iter_vector_line->row, x, a);
	    }
	}
    }

  std::cout << "map size: " << manchas.size() << std::endl;}
	  



int main(int HOLA, char** file_name)
{
  //char* exit = file_name[1];
  char* name = file_name[1];
  //erImage ea;
  IplImage* ea;
  //bool loaded;
  //boost::tie(ea,loaded) = erLoadImage(name);
  ea = cvLoadImage(name);
  //CvCapture * capture = cvCaptureFromCAM(CV_CAP_ANY);
  //unsigned char peo = 5;
  //int peo2 = 5;
  //std::cout << "peo: " << peo << "   peo2: " << peo2 << std::endl;
  //if(!capture)
  //  {
  //    fprintf( stderr, "ERROR: capture is NULL \n" );
      
  //    getchar();
  //    return -1;
  //  }
  
  // Create a window in which the captured images will be presented
  //cvNamedWindow( "Capture", CV_WINDOW_AUTOSIZE );
  cvNamedWindow("Capture", 0);
  
  //cvNamedWindow("Result", 0);
  
  //while(1)
  //  {	
      //    // Get one frame from the web cam
      
      //    IplImage* frame = cvQueryFrame(capture);
      //    if(!frame)
      //	{
      
      //	  fprintf( stderr, "ERROR: frame is null...\n" );
      //	  getchar();
      //	  break;
      //	}
      
      IplImage* gsFrame;
      IplImage* finalFrame;
      gsFrame = cvCreateImage(cvSize(ea->width,ea->height), IPL_DEPTH_8U, 1);
      
      finalFrame = cvCloneImage(ea);
      
      // Convert image to grayscale
      cvCvtColor(ea, gsFrame, CV_RGB2GRAY);
      
      
      // Blur the images to reduce the false positives
      cvSmooth(gsFrame, gsFrame, CV_BLUR);
      cvSmooth(finalFrame, finalFrame, CV_BLUR);
      
      // Detection (with timer for debugging purposes)
      clock_t start = clock();

      //std::cout << "entra" << std::endl;
      detectBlobs(gsFrame, finalFrame);
      //std::cout << "sale" << std::endl;
      clock_t end = clock();
      //cout << end-start << endl;
      
      // Show images in a nice window
      //cvShowImage( "Capture", ea );
      //cvShowImage( "Result", finalFrame );
      
      // Do not release the frame!
      
      //cvReleaseImage(&gsFrame);
      //cvReleaseImage(&finalFrame);
      
      //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
      //remove higher bits using AND operator
  while( 1)
    {
      cvShowImage( "Capture", finalFrame);
      if( cvWaitKey( 700) == 27) break;
    }      
  // if( (cvWaitKey(10) & 255) == 27 ) break;
  // }
  
  // Release the capture device housekeeping
  //cvReleaseCapture( &capture );
  //cvDestroyWindow( "Capture" );
  
  //cvDestroyWindow( "Result" );
  return 0;
}
