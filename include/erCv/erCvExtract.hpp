#ifndef _ER_CV_EXTRACT_HPP_
#define _ER_CV_EXTRACT_HPP_

#include "erCv.hpp"
#include "utilities/erPredicates.hpp"
#include <list>
#include <vector>
#include <map>
#include <algorithm>

/** \addtogroup cv_group */
/*@{*/
/**
   Permet d extraire des points d une image en niveau de gris et les placer dans 
   un container suivant un critere. Une liste de critere est disponible dans
   erPredicates.hpp
   \param IplImage * : une image 
   \param Container  : Un container STL (supportant le back_inserter ) de Point d OpenCv
   \param Criteria   :  un critere de selection des points
 */

template< typename Container, typename Criteria>
void erExtractPoints( IplImage *im, Container &pts, Criteria crit,CvRect rect=cvRect(0,0,0,0))
{  
  typedef typename Container::value_type CvPoint;;
  int y, x;
  for( y = 0; y < im->height; y++)
    { 
      for( x = 0; x < im->width; x++)
	{ 
	  //std::cout << "x =    " << x         << "  " << "y =     " << y       ;//   << std::endl;
	  CvScalar a = cvGet2D(im,y,x);
	  //std::cout << "  widht: " << im->width << "  " << "height: " << im->height << std::endl;
	  if(crit(a.val[0]))
	    { 
	      //std::cout << "dentro" << std::endl;
	      CvPoint p;
	      p.x = x+rect.x;
	      p.y = y+rect.y;
	      pts.push_back(p); 

	    }
	}
    }
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

template< typename Container>
void erExtractionCurveUser( IplImage* simag, erCerc* cerc, char** file_name, Container &pts, CvRect recROI)
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
  
  //char* new_name = erEcrireNomFicher( file_name, "_curve_");
  //std::ofstream myfile( new_name);
  //if ( myfile.is_open())
  // {
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
	  //iterDmin = std::min_element( ptsDmin.begin(), ptsDmin.end());
	  p_polyvalent.x = iterMap->first;
	  p_polyvalent.y = c;
	  //p_polyvalent.y = abs((*iterDmin) + cercle.first.y);
	  pts.push_back( p_polyvalent);
	  //myfile <<  p_polyvalent.x << " " << p_polyvalent.y << std::endl;
 	}
      else
      	{
	  std::string name = INFOFILE;
	  name+= "_imagesOUT.txt";
	  const char* nomb = name.c_str();
	  std::ofstream file( nomb, std::ios_base::app );
	  file << file_name[2] << std::endl;
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
			      std::string name = INFOFILE;
			      name+= "_imagesOUT.txt";
			      const char* nomb = name.c_str();
			      std::ofstream file( nomb, std::ios_base::app );
			      file << file_name[2] << std::endl;
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			      //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
			      A=-1;
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			  //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
			  A=1;
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		      //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
		      A=0;
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		  //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
		  A=0;
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	      //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
	      A=0;
	    }
	}
      // myfile.close();
      // } 
      for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
	{
	  iterV_pts->x = iterV_pts->x + recROI.x;
	  iterV_pts->y = iterV_pts->y + recROI.y;
	}
};



template< typename Container>
void erExtractionCurve( IplImage* simag, erCerc* cerc, char** file_name, Container &pts, CvRect recROI )
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
  
  // char* new_name = erEcrireNomFicher( file_name, "_curve_");
  //std::ofstream myfile( new_name);
  //if ( myfile.is_open())
  //  {
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
	  //iterDmin = std::min_element( ptsDmin.begin(), ptsDmin.end());
	  p_polyvalent.x = iterMap->first;
	  p_polyvalent.y = c;
	  //p_polyvalent.y = abs((*iterDmin) + cercle.first.y);
	  pts.push_back( p_polyvalent);
	  //myfile <<  p_polyvalent.x << " " << p_polyvalent.y << std::endl;
 	}
      else
      	{
	  std::string name = INFOFILE;
	  name+= "_imagesOUT.txt";   // ATTENTION : declarer cette variable de maniere globale.
	  const char* nomb = name.c_str();
	  std::ofstream file( nomb, std::ios_base::app );
	  file << file_name[2] << std::endl;
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
			      std::string name = INFOFILE;
			      name+= "_imagesOUT.txt";
			      const char* nomb = name.c_str();
			      std::ofstream file( nomb, std::ios_base::app );
			      file << file_name[2] << std::endl;
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			      //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
			      A=-1;
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			  //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
			  A=1;
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		      //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
		      A=0;
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		  //myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
		  A=0;
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	      // myfile <<  p_polyvalent.x << " " <<  p_polyvalent.y << std::endl;
	      A=0;
	    }
	}
      //myfile.close();
      // } 
      for( iterV_pts = pts.begin(); iterV_pts != pts.end(); iterV_pts++)
	{
	  iterV_pts->x = iterV_pts->x + recROI.x;
	  iterV_pts->y = iterV_pts->y + recROI.y;
	}
};



template< typename Container>
void erConvertPixelToMks( std::pair< double, double> factor, Container &pts, char** file_name)
{
  //Ecriture du nom du ficher 
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
      name4+= "_data_";
      name4+= name3;
      name4+= ".txt";
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      
      //Ouverture du ficher
      std::ofstream myfile( new_name);
      if (myfile.is_open())
	{
	  //Ecriture des donnes dans le ficher
	  typedef typename Container::iterator Iterator;
	  Iterator deb=pts.begin();
	  Iterator fin=pts.end();
	  
	  for(;deb!=fin;deb++)
	    {
	      //std::cout << deb->x*factor.first << std::endl;
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
void erEcriturePointPixel( Container &pts, char** file_name)
{
  //Ecriture du nom du ficher 
  char* new_name = erEcrireNomFicher( file_name, "_curve_");

  //Ouverture du ficher
  std::ofstream myfile( new_name);
  if (myfile.is_open())
    {
      //Ecriture des donnes dans le ficher
      typedef typename Container::iterator Iterator;
      Iterator deb=pts.begin();
      Iterator fin=pts.end();
      
      for(;deb!=fin;deb++)
	{
	  //std::cout << deb->x*factor.first << std::endl;
	  myfile << deb->x << "  " << deb->y << std::endl;
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
