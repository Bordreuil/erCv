#include <erCv/erCvBase.hpp> 
#include <erCv/utilities/erFileUtilities.hpp>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <string>
//#include "_highgui.h"

// Programmation de la classeImage
erImage::erImage():IplImage(){};
erImage::erImage(IplImage im):IplImage(im){};
erImage::erImage(char* name):IplImage(*cvLoadImage(name))
{
}; 
//erImage::erImage(IplImage* im):IplImage(*im){};
erImage::erImage(IplImage* im) :IplImage(*im){};

// erImage::~erImage(){
//   IplImage * thim = this;
  
//   cvReleaseImage(&thim);
// };



// Interface pour des fonctions d open cv
void erShowImage( char* name, IplImage* im)
{
  cvNamedWindow(name, 0);
  cvShowImage(name,im);
  cvWaitKey();
  cvDestroyWindow(name);
};


// Interface pour des fonctions d open cv
void erShow2Image( char* name, IplImage* im, char* name2, IplImage* im2)
{
  cvNamedWindow(name, 0);
  cvNamedWindow(name2, 0);
  cvShowImage(name,im);
  cvShowImage(name2, im2);
  cvWaitKey();
  cvDestroyWindow(name);
  cvDestroyWindow(name2);
};

std::pair<erImage,bool> erLoadImage(char* name)
{ 
  if(erFileExists(name))
    {
      return  std::make_pair(erImage(name),true);
    }
  else
    { 
      std::cout << "...Impossible d instancier un objet de type erImage a partir du fichier:" << name << std::endl;
      return std::make_pair(erImage(),false);
    };
};

std::pair<erImage,bool> erLoadImage(char** name)
{ 
  if(erFileExists(name[2]))
    {
      return  std::make_pair(erImage(name[2]),true);
    }
  else
    { 
      std::cout << "...Impossible d instancier un objet de type erImage a partir du fichier:" << name[2] << std::endl;
      return std::make_pair(erImage(),false);
    };
};



/* Read, name files manipulations, and convert to one channel the pictures in the loop */
std::pair<erImage,bool> erLoadImageSeries( char** file_name,uint inc)
{
  std::string name( file_name[2]); 
  size_t ext_pos = name.find_last_of( '_' );
  size_t ext_pos1 = name.find_last_of( '.');
  if( ext_pos != std::string::npos && ext_pos1 != std::string::npos )
    {
      std::string ext2 = name.substr( ext_pos + 1);
      std::string name2 = ext2.substr( 0,  ext_pos1 - (ext_pos + 1));
      int num = boost::lexical_cast<int>( name2);
      num+=inc;
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
      
      return erLoadImage( file_name);
    }
  else
    {
      std::cout << "Incorrect file name or end of the stockpile" << std::endl;
     
      return std::make_pair(erImage(),false);
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


/* Save final images to post processing procedure with CGAL */
void erSaveImage2( IplImage* simag, char** file_name, char* a )
{
  std::string name( file_name[2]);
  //std::string tipo( a)
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
      name4+= a;
      name4+= "_";
      name4+= name3; 
      name4+= ".png";
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      cvSaveImage( new_name, simag);
    }
}


// erImage erConvertToBlackAndWhite( IplImage* simag)
// {
//    IplImage * ipbw = cvCreateImage( cvGetSize(simag), simag->depth, 1);
//    cvCvtColor( simag, ipbw, CV_RGB2GRAY);

//    return erImage(ipbw);
   
// }
IplImage* erConvertToBlackAndWhite( IplImage* simag)
{
   IplImage * ipbw = cvCreateImage( cvGetSize(simag), simag->depth, 1);
   cvCvtColor( simag, ipbw, CV_RGB2GRAY);
   return ipbw;
   ;
}


/* Create the parametters record file of differents fonctions */
void erWriteRecordFile( char** file_name)
{

  std::string name = INFOFILE;
  std::cout << name << std::endl;
  name+= ".txt";
  const char* nomb = name.c_str();
  std::ofstream myfile( nomb);
  if (myfile.is_open())
    {
      std::cout << "";
      myfile << "Analysis type: " << nomb << std::endl;
      std::cout << "Analysis type: " << nomb << std::endl;
      myfile << std::endl;
      myfile << std::endl;
      myfile.close();
    }
  else 
    {
      std::cout << "Unable to open file";
    }
}



void erCvConvert32to8( IplImage* srcarr, IplImage* dstarr)
{
  CvMat* temp = 0;
  int flags = 0;
  CV_FUNCNAME( "cvConvertImage" );
  
  //__BEGIN__;
  
  CvMat srcstub, *src;
  CvMat dststub, *dst;
  int src_cn, dst_cn, swap_rb = flags & CV_CVTIMG_SWAP_RB;

  src = cvGetMat( srcarr, &srcstub );
  dst = cvGetMat( dstarr, &dststub );
  
  src_cn = CV_MAT_CN( src->type );
  dst_cn = CV_MAT_CN( dst->type ); 
  
  int src_depth = CV_MAT_DEPTH(src->type);
  double scale = src_depth <= CV_8S ? 1 : src_depth <= CV_32S ? 1./256 : 255;
  double shift = src_depth == CV_8S || src_depth == CV_16S ? 128 : 0;
  
  if( !CV_ARE_CNS_EQ( src, dst ))
    {
      temp = cvCreateMat( src->height, src->width,
			  (src->type & CV_MAT_CN_MASK)|(dst->type & CV_MAT_DEPTH_MASK));
      cvConvertScale( src, temp, scale, shift );
      src = temp;
    }
  else
    {
      cvConvertScale( src, dst, scale, shift );
      src = dst;
    }
  //__END__; 
  cvReleaseMat( &temp );
}


char* erEcrireNomFicher( char** file_name, std::string info)
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
      name4+= info;
      name4+= name3;
      name4+= ".txt";
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      return new_name;
    }
  else
    {
      std::cout << "format incorrect du nom des fichers d'entre" << std::endl;
      return "";
    }
};
char* erEcrireNomFichier( char* file_name, char* nameOut,std::string info)
{
  std::string name( file_name);
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
      std::string name4(nameOut);
      name4+= info;
      name4+= name3;
      name4+= ".txt";
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      return new_name;
    }
  else
    {
      std::cout << "format incorrect du nom des fichers d'entre" << std::endl;
      return "";
    }
};

ImageIncrement::ImageIncrement():current(0),base(0),delta(0),every(0){};
ImageIncrement::ImageIncrement(uint incbase,uint incD,uint every):current(0),base(incbase),
					                          delta(incD),every(every){};
uint ImageIncrement::inc()
{
    current+=base;
    if(current > every)
      {
      current=0;
      return delta;
      };
    return base;
};
