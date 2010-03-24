#ifndef _ER_CV_EXTRACT_HPP_
#define _ER_CV_EXTRACT_HPP_

//#include "erCv.hpp"
#include "erCvBase.hpp"
#include "utilities/erPredicates.hpp"
#include "utilities/erManipFileName.hpp"
//#include <utilities/erPredicates.hpp>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include<fstream>
#include <erCv/Gui/erCvUserInteraction.hpp>
#include<boost/tuple/tuple.hpp>

/** \addtogroup cv_group */
/*@{*/
/**
   Permet d extraire des points d une image en niveau de gris et les placer dans 
   un container suivant un critere. Une liste de critere est disponible dans
   erPredicates.hpp
   \param IplImage * : une image 
   \param Container  : Un container STL (supportant le back_inserter ) de Point d OpenCv
   \param CvRect     : Rectangle contenant les coordones de la ROI dans l'image d'origine (coordones par defaut pas de ROI)
   \param delta      : On lis le lignes et colonnes des pixels de 2 en 2, 3 en 3,..., n en n (par defaut de 1 en 1, toutes les lignes)
   \param gray_level : Seuil niveau gris à partir du quel en extrait les points (Voir foncteurs dans utilities/erPredicates.hpp)
*/

//template< typename Container>
std::list<CvPoint> erExtractCvPoints( IplImage *im, CvRect rect=cvRect(0,0,0,0), uint delta=1, uint gray_level=255)
{  
  //typedef typename Container::value_type CvPoint;
  std::list<CvPoint> pts;
  int y, x;
  IsEqualTo is_equal_255( gray_level); /* Definition d un foncteur comme critere pour extraire des pixels suivant leur niveau de gris. cf->utilities/erPredicates.hpp */     

  for( y = 0; y < im->height; y+=delta)
    { 
      for( x = 0; x < im->width; x+=delta)
	{ 
	  CvScalar a = cvGet2D(im,y,x);
	  if( is_equal_255(a.val[0]))
	    { 
	      CvPoint p;
	      p.x = x+rect.x;
	      p.y = y+rect.y;
	      pts.push_back(p); 
	    }
	}
    }
  return pts;
};




//int* ptr = (int*)(im->imageData + y*im->widthStep ); (linea de commando alternativa, va entre los for)

/**
   Permet d extraire une ligne continue a partir d une image precedemment filtre
   \param IplImage* : une image 
   \param erCerc    : cercle pour le debut de la recherche
   \param char **   : ensemble des variables venant de l exterieur file_name[2] doit correspondre
                      au fichier a traiter
   \param Container (template) : container des points a extraire
   \param CvRect    : Rectangle pour extraire remettre les points dans les coordoonees de l image

 */

// ATTENTION: Regrouper les fonctions erExtractionCurve et  erExtractionCurveUser


//=======
//template< typename Container>
// void erExtractionCurveUser( IplImage* simag, erCerc* cerc, char* file_name, Container &pts, CvRect recROI)
// {

//   //typedef Container typeContainer;
//   typedef std::map< double, Container> erMap;
//   erMap ptsMap;
//   typename erMap::iterator iterMap;
//   typename Container::iterator iterV_polyvalent, iterV_pts;
  
//   for( iterV_polyvalent = pts.begin(); iterV_polyvalent != pts.end(); iterV_polyvalent++)
//     {
//       ptsMap[iterV_polyvalent->x].push_back(*iterV_polyvalent);
//     }
//   pts.clear();
  
//       std::pair< CvPoint, int> cercle = erCvDebutCurve( simag);
//       cerc->centro = cercle.first;
//       cerc->radio = cercle.second;
//       CvPoint p_polyvalent;
//       std::vector< int> ptsDmin, ptsY0;
//       std::vector< int>::iterator iterDmin;
//       bool Dmin = false;
//       int a = 0, b = 0, c = 0;
//       iterMap = ptsMap.begin();
//       for( iterV_polyvalent = iterMap->second.begin(); iterV_polyvalent != iterMap->second.end(); iterV_polyvalent++)
// 	{
// 	  a = abs( iterV_polyvalent->y - cercle.first.y);
// 	  if( a <= cercle.second)
// 	    {
// 	      if( a < b || Dmin==false)
// 		{
// 		  c = iterV_polyvalent->y;
// 		  Dmin = true;
// 		  b = a;
// 		}
// 	    }
// 	}
//       if( Dmin)
//  	{
	  
// 	  p_polyvalent.x = iterMap->first;
// 	  p_polyvalent.y = c;
	 
// 	  pts.push_back( p_polyvalent);

//  	}
//       else
//       	{

// 	  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
// 	  file << file_name << std::endl;
// 	  file << std::endl;
// 	  pts.clear();
// 	  return; 
// 	}
//       int A=0;
//       iterMap++;
//       for( ; iterMap != ptsMap.end(); iterMap++)
// 	{ 
// 	  CvPoint cpt = pts.back();
// 	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
// 	  if( iterV_polyvalent == iterMap->second.end())
// 	    { 
// 	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
// 	      if( iterV_polyvalent == iterMap->second.end())
// 		{
// 		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
// 		  if( iterV_polyvalent == iterMap->second.end())
// 		    {
// 		      iterMap--;
// 		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
// 		      if( iterV_polyvalent == iterMap->second.end() || A==-1)
// 			{
// 			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
// 			  if( iterV_polyvalent == iterMap->second.end() || A==1)
// 			    {

// 			      std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
// 			      file << file_name << std::endl;
// 			      file << std::endl;
// 			      pts.clear();
// 			      return;
// 			    }
// 			  else
// 			    {
// 			      p_polyvalent.x = iterV_polyvalent->x;
// 			      p_polyvalent.y = iterV_polyvalent->y;
// 			      pts.push_back( p_polyvalent);
			     
// 			      A=-1;
// 			    }
// 			}
// 		      else
// 			{
// 			  p_polyvalent.x = iterV_polyvalent->x;
// 			  p_polyvalent.y = iterV_polyvalent->y;
// 			  pts.push_back( p_polyvalent);
			  
// 			  A=1;
// 			}
// 		    }
// 		  else
// 		    {
// 		      p_polyvalent.x = iterV_polyvalent->x;
// 		      p_polyvalent.y = iterV_polyvalent->y;
// 		      pts.push_back( p_polyvalent);
		     
// 		      A=0;
// 		    }
// 		}
// 	      else
// 		{
// 		  p_polyvalent.x = iterV_polyvalent->x;
// 		  p_polyvalent.y = iterV_polyvalent->y;
// 		  pts.push_back( p_polyvalent);
		 
// 		  A=0;
// 		}
// 	    }
// 	  else
// 	    {
// 	      p_polyvalent.x = iterV_polyvalent->x;
// 	      p_polyvalent.y = iterV_polyvalent->y;
// 	      pts.push_back( p_polyvalent);
	      
// 	      A=0;
// 	    }
// 	}
     
//       for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
// 	{
// 	  iterV_pts->x = iterV_pts->x + recROI.x;
// 	  iterV_pts->y = iterV_pts->y + recROI.y;
// 	}
// };

// template< typename Container>
// void erExtractionCurveUser( IplImage* simag, erCerc* cerc, char** file_name, Container &pts, CvRect recROI)
// >>>>>>> .r56
template< typename Container>
void erExtractCurveMacroDropUser( IplImage* simag, Container &pts, CvRect recROI, erCerc* cerc, char* file_name)
{
  //typedef Container typeContainer;
  typedef std::map< double, Container> erMap;
  erMap ptsMap;
  typename erMap::iterator iterMap;
  typename Container::iterator iterV_polyvalent, iterV_pts;
  
  for( iterV_polyvalent = pts.begin(); iterV_polyvalent != pts.end(); iterV_polyvalent++)
    {
      ptsMap[iterV_polyvalent->x].push_back(*iterV_polyvalent);
    }
  pts.clear();
  
      std::pair< CvPoint, int> cercle = erCvDebutCurve( simag);
      cerc->centro = cercle.first;
      cerc->radio = cercle.second;
      CvPoint p_polyvalent;
      std::vector< int> ptsDmin, ptsY0;
      std::vector< int>::iterator iterDmin;
      bool Dmin = false;
      int a = 0, b = 0, c = 0;
      iterMap = ptsMap.begin();
      for( iterV_polyvalent = iterMap->second.begin(); iterV_polyvalent != iterMap->second.end(); iterV_polyvalent++)
	{
	  a = abs( iterV_polyvalent->y - cercle.first.y);
	  if( a <= cercle.second)
	    {
	      if( a < b || Dmin==false)
		{
		  c = iterV_polyvalent->y;
		  Dmin = true;
		  b = a;
		}
	    }
	}
      if( Dmin)
 	{
	  
	  p_polyvalent.x = iterMap->first;
	  p_polyvalent.y = c;
	 
	  pts.push_back( p_polyvalent);

 	}
      else
      	{

	  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
	  file << file_name << std::endl;
	  file << std::endl;
	  pts.clear();
	  return; 
	}
      int A=0;
      iterMap++;
      for( ; iterMap != ptsMap.end(); iterMap++)
	{ 
	  CvPoint cpt = pts.back();
	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
	  if( iterV_polyvalent == iterMap->second.end())
	    { 
	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
	      if( iterV_polyvalent == iterMap->second.end())
		{
		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
		  if( iterV_polyvalent == iterMap->second.end())
		    {
		      iterMap--;
		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
		      if( iterV_polyvalent == iterMap->second.end() || A==-1)
			{
			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
			  if( iterV_polyvalent == iterMap->second.end() || A==1)
			    {

			      std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
			      file << file_name << std::endl;
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			     
			      A=-1;
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			  
			  A=1;
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		     
		      A=0;
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		 
		  A=0;
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	      
	      A=0;
	    }
	}
     
      for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
	{
	  iterV_pts->x = iterV_pts->x + recROI.x;
	  iterV_pts->y = iterV_pts->y + recROI.y;
	}
};



// =======
// void erExtractionCurve( IplImage* simag, erCerc* cerc, char* file_name, Container &pts, CvRect recROI )
// {
//   //typedef Container typeContainer;
//   typedef std::map< double, Container> erMap;
//   erMap ptsMap;
//   typename erMap::iterator iterMap;
//   typename Container::iterator iterV_polyvalent, iterV_pts;
  
//   for( iterV_polyvalent = pts.begin(); iterV_polyvalent != pts.end(); iterV_polyvalent++)
//     {
//       ptsMap[iterV_polyvalent->x].push_back(*iterV_polyvalent);
//     }
//   pts.clear();
  
//       std::pair< CvPoint, int> cercle(cerc->centro, cerc->radio);
//       CvPoint p_polyvalent;
//       std::vector< int> ptsDmin, ptsY0;
//       std::vector< int>::iterator iterDmin;
//       bool Dmin = false;
//       int a = 0, b = 0, c = 0;
//       iterMap = ptsMap.begin();
//       for( iterV_polyvalent = iterMap->second.begin(); iterV_polyvalent != iterMap->second.end(); iterV_polyvalent++)
// 	{
// 	  a = abs( iterV_polyvalent->y - cercle.first.y);
// 	  if( a <= cercle.second)
// 	    {
// 	      if( a < b || Dmin==false)
// 		{
// 		  c = iterV_polyvalent->y;
// 		  Dmin = true;
// 		  b = a;
// 		}
// 	    }
// 	}
//       if( Dmin)
//  	{
	  
// 	  p_polyvalent.x = iterMap->first;
// 	  p_polyvalent.y = c;
	 
// 	  pts.push_back( p_polyvalent);
	
//  	}
//       else
//       	{
// 	  std::ofstream file(nameGoodImagesFile(INFOFILE), std::ios_base::app );
// 	  file << file_name << std::endl; // A proscrire
// 	  file << std::endl;
// 	  pts.clear();
// 	  return; 
// 	}
//       int A=0;
//       iterMap++;
//       for( ; iterMap != ptsMap.end(); iterMap++)
// 	{ 
// 	  CvPoint cpt = pts.back();
// 	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
// 	  if( iterV_polyvalent == iterMap->second.end())
// 	    { 
// 	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
// 	      if( iterV_polyvalent == iterMap->second.end())
// 		{
// 		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
// 		  if( iterV_polyvalent == iterMap->second.end())
// 		    {
// 		      iterMap--;
// 		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
// 		      if( iterV_polyvalent == iterMap->second.end() || A==-1)
// 			{
// 			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
// 			  if( iterV_polyvalent == iterMap->second.end() || A==1)
// 			    {
// 			      std::ofstream file(nameGoodImagesFile(INFOFILE), std::ios_base::app );
// 			      file << file_name << std::endl;  // A proscire
// 			      file << std::endl;
// 			      pts.clear();
// 			      return;
// 			    }
// 			  else
// 			    {
// 			      p_polyvalent.x = iterV_polyvalent->x;
// 			      p_polyvalent.y = iterV_polyvalent->y;
// 			      pts.push_back( p_polyvalent);
			   
// 			      A=-1;
// 			    }
// 			}
// 		      else
// 			{
// 			  p_polyvalent.x = iterV_polyvalent->x;
// 			  p_polyvalent.y = iterV_polyvalent->y;
// 			  pts.push_back( p_polyvalent);
			
// 			  A=1;
// 			}
// 		    }
// 		  else
// 		    {
// 		      p_polyvalent.x = iterV_polyvalent->x;
// 		      p_polyvalent.y = iterV_polyvalent->y;
// 		      pts.push_back( p_polyvalent);
		      
// 		      A=0;
// 		    }
// 		}
// 	      else
// 		{
// 		  p_polyvalent.x = iterV_polyvalent->x;
// 		  p_polyvalent.y = iterV_polyvalent->y;
// 		  pts.push_back( p_polyvalent);
		
// 		  A=0;
// 		}
// 	    }
// 	  else
// 	    {
// 	      p_polyvalent.x = iterV_polyvalent->x;
// 	      p_polyvalent.y = iterV_polyvalent->y;
// 	      pts.push_back( p_polyvalent);
	    
// 	      A=0;
// 	    }
// 	};
    
//       for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
// 	{
// 	  iterV_pts->x = iterV_pts->x + recROI.x;
// 	  iterV_pts->y = iterV_pts->y + recROI.y;
// 	}
// };

// template< typename Container>
// void erExtractionCurve( IplImage* simag, erCerc* cerc, char** file_name, Container &pts, CvRect recROI )
// >>>>>>> .r56
template< typename Container>
void erExtractCurveMacroDrop( IplImage* simag, Container &pts, CvRect recROI, erCerc* cerc, char* file_name )
{
  //typedef Container typeContainer;
  typedef std::map< double, Container> erMap;
  erMap ptsMap;
  typename erMap::iterator iterMap;
  typename Container::iterator iterV_polyvalent, iterV_pts;
  
  for( iterV_polyvalent = pts.begin(); iterV_polyvalent != pts.end(); iterV_polyvalent++)
    {
      ptsMap[iterV_polyvalent->x].push_back(*iterV_polyvalent);
    }
  pts.clear();
  
      std::pair< CvPoint, int> cercle(cerc->centro, cerc->radio);
      CvPoint p_polyvalent;
      std::vector< int> ptsDmin, ptsY0;
      std::vector< int>::iterator iterDmin;
      bool Dmin = false;
      int a = 0, b = 0, c = 0;
      iterMap = ptsMap.begin();
      for( iterV_polyvalent = iterMap->second.begin(); iterV_polyvalent != iterMap->second.end(); iterV_polyvalent++)
	{
	  a = abs( iterV_polyvalent->y - cercle.first.y);
	  if( a <= cercle.second)
	    {
	      if( a < b || Dmin==false)
		{
		  c = iterV_polyvalent->y;
		  Dmin = true;
		  b = a;
		}
	    }
	}
      if( Dmin)
 	{
	  
	  p_polyvalent.x = iterMap->first;
	  p_polyvalent.y = c;
	 
	  pts.push_back( p_polyvalent);
	
 	}
      else
      	{
	  std::ofstream file(nameGoodImagesFile(INFOFILE), std::ios_base::app );
	  file << file_name << std::endl; // A proscrire
	  file << std::endl;
	  pts.clear();
	  return; 
	}
      int A=0;
      iterMap++;
      for( ; iterMap != ptsMap.end(); iterMap++)
	{ 
	  CvPoint cpt = pts.back();
	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
	  if( iterV_polyvalent == iterMap->second.end())
	    { 
	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
	      if( iterV_polyvalent == iterMap->second.end())
		{
		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
		  if( iterV_polyvalent == iterMap->second.end())
		    {
		      iterMap--;
		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
		      if( iterV_polyvalent == iterMap->second.end() || A==-1)
			{
			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
			  if( iterV_polyvalent == iterMap->second.end() || A==1)
			    {
			      std::ofstream file(nameGoodImagesFile(INFOFILE), std::ios_base::app );
			      file << file_name << std::endl;  // A proscire
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			   
			      A=-1;
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			
			  A=1;
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		      
		      A=0;
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		
		  A=0;
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	    
	      A=0;
	    }
	};
    
      for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
	{
	  iterV_pts->x = iterV_pts->x + recROI.x;
	  iterV_pts->y = iterV_pts->y + recROI.y;
	}
};




template< typename Container>
void erConvertPixelToMks( std::pair< double, double> factor, Container &pts, char* file_name, char* exit_name)
{
  //Ecriture du nom du ficher 
  bool good_format;
  const char* num;
  boost::tie(good_format,num) = erGetNumberInFileName( file_name);


  if(good_format)
    {
      char* new_name = erConcatenateFileName( exit_name,"_data_",num,".txt");     
      //Ouverture du fichier
      std::ofstream myfile( new_name);
      if (myfile.is_open())
	{
	  //Ecriture des donnes dans le ficher
	  typedef typename Container::iterator Iterator;
	  Iterator deb=pts.begin();
	  Iterator fin=pts.end();
	  
	  for(;deb!=fin;deb++)
	    {
	      myfile << deb->x*factor.first << "  " << deb->y*factor.second << std::endl;
	    }	  
	  myfile.close();
	}
      else 
	{
	  std::cout << "Unable to open file";
	}
    }
  else
    {
      std::cout << "error in format input file images";
    } 
};






template< typename Container>
void erPrintCgalPoint( Container & pts, char* file_name, char* exit_name)
{
  //Ecriture du nom du ficher 
  char* new_name = erEcrireNomFichier( file_name, exit_name, "_curveCgal_");
  //Ouverture du ficher
  std::ofstream myfile( new_name);
  if (myfile.is_open())
    {
      //Ecriture des donnes dans le ficher
      typedef typename Container::iterator Iterator;
      Iterator it;      
      for( it = pts.begin(); it != pts.end(); it++)
	{	  
	  myfile << *it << std::endl;
	}	  
      myfile.close();
    }
  else 
    {
      std::cout << "Unable to open file";
    }
};
// =======
//   //Ouverture du ficher
//   std::ofstream myfile( new_name);
//   if (myfile.is_open())
//     {
//       //Ecriture des donnes dans le ficher
//       typedef typename Container::iterator Iterator;
//       Iterator deb=pts.begin();
//       Iterator fin=pts.end();
//       for(;deb!=fin;deb++)
// 	{	  
// 	  myfile << deb->x << "  " << deb->y << std::endl;
// 	}	  
//       myfile.close();
//     }
//   else 
//     {
//       std::cout << "Unable to open file";
//     }
// };






template< typename Container>
void erPrintCvPoint( Container & pts, char* file_name, char* exit_name)
{
  //Ecriture du nom du ficher 
  char* new_name = erEcrireNomFichier( file_name, exit_name, "_curvCV_");

  //Ouverture du ficher
  std::ofstream myfile( new_name);
  if (myfile.is_open())
    {
      //Ecriture des donnes dans le ficher
      typedef typename Container::iterator Iterator;
      Iterator it;      
      for( it = pts.begin(); it != pts.end(); it++)
	{	  
	  myfile << it->x << "  " << it->y << std::endl;
	}	  
      myfile.close();
    }
  else 
    {
      std::cout << "Unable to open file";
    }
};




// ATTENTION Test uniquement sur y precise a quoi sert cette fonction
template< typename Iterator>
Iterator erFindCvPoint( Iterator p1, Iterator p2, CvPoint punto)
{
  while(p1 != p2)
    {
      if( p1->y == punto.y)
	{
	  return p1;
	  break;
	}
      p1++;
    }
  return p2;
}; 

/*@}*/
#endif
