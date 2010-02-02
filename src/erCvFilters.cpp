#include <erCv/erCvFilters.hpp>
#include <iostream>
#include <fstream>



erImage erSmoothAndCanny( IplImage* pic1, int A=1, int B=2)
{
  /* Test picture is gray: only one channel */
  if(pic1->nChannels != 1)
    {
      std::cout << "Picture must be have only one channel" << std::endl;
      return erImage();
    }
  else
    { 
      cvSmooth( &pic1, pic1, CV_BLUR, 5, 5, 0, 0);
      cvCanny( pic1, pic1, (float)A*10., (float)B*10., 5); 
      return erImage(pic1);
    }
};




void erCvSmooth( IplImage* simg, erSmootP* parm)
{
  // int size= parm->size;
  //SmoothType smooth = parm->type;
  //std::cout << "size: " << size << std::endl;
  //std::cout << "smoothtype: " << smoothtype[smooth] << std::endl;
  //std::cout << parm;
  //cvSmooth( simg, simg, smooth, size , 0, 0, 0);
  cvSmooth( simg, simg, parm->type, parm->size, 0, 0, 0);
 }



void erCvSobel( IplImage* simg, erSobelP* parm)
{
  int threshold[2];
  threshold[0] = parm->trhX;
  threshold[1] = parm->trhY; 
  cvSobel( simg, simg, threshold[0], threshold[1], 5);
}



void erCvCanny( IplImage* simg, erCannyP* parm)
{
  int threshold[2];
  threshold[0] = parm->trh1;
  threshold[1] = parm->trh2;
  //std::cout << "cany_0: " << threshold[0] << std::endl;
  //std::cout << "cany_1: " << threshold[1] << std::endl;
  cvCanny( simg, simg, (float)threshold[0]*10., (float)threshold[1]*10., 5);
}



void erCvThreshold( IplImage* simg, erThresP* parm)
{
  int threshold[2], threstype;  
  threshold[0] = parm->trh1;
  threshold[1] = parm->trh2;
  threstype =  parm->type;
  std::cout << "thrsh_0: " << threshold[0] << std::endl;
  std::cout << "thrsh_1: " << threshold[1] << std::endl;
  std::cout << "thrstyp: " << threstype << std::endl;
  if( threstype == 1) cvThreshold( simg, simg, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY);
  if( threstype == 2) cvThreshold( simg, simg, (float)threshold[0], (float)threshold[1], CV_THRESH_BINARY_INV);
  if( threstype == 3) cvThreshold( simg, simg, (float)threshold[0], (float)threshold[0], CV_THRESH_TRUNC);
  if( threstype == 4) cvThreshold( simg, simg, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO);
  if( threstype == 5) cvThreshold( simg, simg, (float)threshold[0], (float)threshold[0], CV_THRESH_TOZERO_INV);
}





void erCvAdaptiveThreshold( IplImage* simg, erAdThrP* parm)
{
  int threshold, maxt, itrak, threstype, adapt, neigh, param;
  
  param = parm->trhP;
  neigh = parm->neig;
  threshold = parm->trh0;
  threstype = parm->type;
  adapt = parm->adpt;
  maxt = 255;
  if( threstype == 1) 
    {
      if( adapt ==1) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, neigh, param);
      if( adapt ==2) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, neigh, param);
    }
  if( threstype == 2)
    {
      if( adapt ==1) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, neigh, param);
      if( adapt ==2) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, neigh, param);
    }
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




void erCvDilate( IplImage* simg, erDilatP* parm)
{
  int iteration; 
  IplConvKernel* ele=NULL;
  iteration = 1;
  iteration = parm->iter;
  cvDilate( simg, simg, ele, iteration);
}




void erCvErode( IplImage* simg, erErodeP* parm)
{
  int iteration; 
  IplConvKernel* ele=NULL;
  iteration = 1;
  iteration = parm->iter;
  cvErode(simg, simg, ele, iteration); 
};

std::ostream& operator << (std::ostream& o, erSmootP* smp)
{
  o << "***********Filter fonction SMOOTH**************\n";
  o << "neighboor size:-------- " << smp->size << std::endl;
  o << "smooth type:----------- " << smoothtype[smp->type] << std::endl;
  o << std::endl;
};
