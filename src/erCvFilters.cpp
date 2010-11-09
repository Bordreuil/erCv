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
#include <erCv/erCvFilters.hpp>
#include <iostream>
#include <fstream>



// erImage erSmoothAndCanny( IplImage* pic1, int A, int B)
// {
//   /* Test picture is gray: only one channel */
//   if(pic1->nChannels != 1)
//     {
//       std::cout << "Picture must be have only one channel" << std::endl;
//       return erImage();
//     }
//   else
//     { 
//       cvSmooth( &pic1, pic1, CV_BLUR, 5, 5, 0, 0);
//       cvCanny( pic1, pic1, (float)A*10., (float)B*10., 5); 
//       return erImage(pic1);
//     }
// };




void erCvSmooth( IplImage* simg, erSmootP* parm)
{
  cvSmooth( simg, simg, parm->type, parm->size, 0, 0, 0);
 }



// void erCvSobel( IplImage* simg, erSobelP* parm)
// {
//   int threshold[2];
//   threshold[0] = parm->trhX;
//   threshold[1] = parm->trhY; 
//   cvSobel( simg, simg, threshold[0], threshold[1], 5);
// }



void erCvCanny( IplImage* simg, erCannyP* parm)
{
  int threshold[2];
  threshold[0] = parm->trh1;
  threshold[1] = parm->trh2;
  //std::cout << "cany_0: " << threshold[0] << std::endl;
  //std::cout << "cany_1: " << threshold[1] << std::endl;
  cvCanny( simg, simg, (float)threshold[0], (float)threshold[1], 5);
}



void erCvThreshold( IplImage* simg, erThresP* parm)
{
  int threshold[2], threstype;  
  threshold[0] = parm->trh1;
  threshold[1] = parm->trh2;
  threstype =  parm->type;
  //std::cout << "thrsh_0: " << threshold[0] << std::endl;
  //std::cout << "thrsh_1: " << threshold[1] << std::endl;
  //std::cout << "thrstyp: " << threstype << std::endl;
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
      if( adapt ==1) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, (2*neigh)+1, param-50);
      if( adapt ==2) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, (2*neigh)+1, param-50);
    }
  if( threstype == 2)
    {
      if( adapt ==1) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, (2*neigh)+1, param-50);
      if( adapt ==2) cvAdaptiveThreshold( simg, simg, (double)threshold, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY_INV, (2*neigh)+1, param-50);
    }
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
