#include <erCv/erCvBase.hpp> 
#include <erCv/utilities/erFileUtilities.hpp>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <string>

// Programmation de la classeImage
erImage::erImage():IplImage(){};
erImage::erImage(IplImage im):IplImage(im){};
erImage::erImage(char* name):IplImage(*cvLoadImage(name))
{
}; 

erImage::erImage(IplImage* im):IplImage(*im){};
erImage::~erImage(){};

//CvRect& erImage::rectan(){return __rect;};


// Interface pour des fonctions d open cv
void erShowImage(char* name,IplImage* im)
{
  cvNamedWindow(name);
  cvShowImage(name,im);
  cvWaitKey();
  cvDestroyWindow(name);
};



// /* Read and adapt to one channel the pictures */
// void erRead_picture( IplImage* simag, char** file_name)
// {
//   IplImage *pic0, *pic1;
//   /* Test to file picture: exist or not */
//   std::cout << "file name " << file_name[2] << std::endl;
//   FILE* f = fopen( file_name[2], "r");
//   if(f==NULL)
//     {
//       std::cout << "The file do not exist in the folder ~/erCV_0_0_0/test/pictures" << std::endl;
//       simag = NULL;
//     }
//   else
//     {
//       pic0 = cvLoadImage( file_name[2], CV_LOAD_IMAGE_COLOR);
//       simag = cvCreateImage( cvGetSize(pic0), pic0->depth, 1);
//       //simag = cvCloneImage( pic0);
//       cvCvtColor( pic0, simag, CV_RGB2GRAY);
//     }
// }
erImage erLoadImage(char* name)
{ 
  if(erFileExists(name))
    {
      return  erImage(name);
    }
  else
    { std::cout << "...Impossible d instancier un objet de type erImage a partir du fichier:" << name << std::endl;
      IplImage * im = NULL;
      return erImage(im);
    };
}



/* Read, name files manipulations, and convert to one channel the pictures in the loop */
erImage erLoadImageSeries( char** file_name)
{
  std::string name( file_name[2]); 
  size_t ext_pos = name.find_last_of( '_' );
  size_t ext_pos1 = name.find_last_of( '.');
  if( ext_pos != std::string::npos && ext_pos1 != std::string::npos )
    {
      std::string ext2 = name.substr( ext_pos + 1);
      std::string name2 = ext2.substr( 0,  ext_pos1 - (ext_pos + 1));
      int num = boost::lexical_cast<int>( name2);
      num++;
      std::string name3 = boost::lexical_cast<std::string>(num);
      while(name2.size()>name3.size())
	{
	  name3.insert( 0, "0" );
	}
      std::string name4 = name.substr( 0,  ext_pos+1);
      name4.insert( ext_pos + 1, name3 );
      std::string name5 = name.substr( ext_pos1);
      name4+=name5;
      file_name[2] = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), file_name[2]);
      file_name[2][ name4.size()] = '\0';
      return erLoadImage( file_name[2]);
    }
  else
    {
      std::cout << "Incorrect file name or end of the stockpile" << std::endl;
      IplImage* nula=NULL;

      return erImage(nula);
    }
}





/* Save final images to post processing procedure with CGAL */
void erSaveImage( IplImage* simag, char** file_name)
{
  std::string name( file_name[2]);
  size_t ext_pos = name.find_last_of( '_' );
  size_t ext_pos1 = name.find_last_of( '.');
  if( ext_pos != std::string::npos && ext_pos1 != std::string::npos )
    {
      
      std::string ext2 = name.substr( ext_pos + 1);
      std::string name2 = ext2.substr( 0,  ext_pos1 - (ext_pos + 1));
      int num = boost::lexical_cast<int>( name2);
      std::string name3 = boost::lexical_cast<std::string>(num);
      while(name2.size()>name3.size())
	{
	  name3.insert( 0, "0" );
	}
      std::string name4( file_name[1]);
      name4+= "_";
      name4+= name3;
      name4+= ".bmp";
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      cvSaveImage( new_name, simag);
    }
}
// void erSaveImage(char* name,IplImage* im)
// {
//   cvSaveImage(name,im);
// };




erImage erConvertToBlackAndWhite( IplImage* simag)
{
   IplImage * ipbw = cvCreateImage( cvGetSize(simag), simag->depth, 1);
   cvCvtColor( simag, ipbw, CV_RGB2GRAY);
   return erImage(ipbw);
   //cvReleaseImage( &simag); 
   //simag = cvCloneImage( ipbw);
}



/* Create the parametters record file of differents fonctions */
void erWriteRecordFile( char** file_name)
{
//   std::string name;
//   std::cout << "Analysis type: " << std::endl;
//   std::cin >> name;
  std::string name = INFOFILE;
  std::cout << name << std::endl;
  name+= ".txt";
  const char* nomb = name.c_str();
  std::ofstream myfile( nomb);
  if (myfile.is_open()){
    std::cout << "";
    myfile << "Analysis type: " << nomb << std::endl;
    std::cout << "Analysis type: " << nomb << std::endl;
    myfile << std::endl;
    myfile << std::endl;
    myfile.close();
  }
  else 
    std::cout << "Unable to open file";
}
