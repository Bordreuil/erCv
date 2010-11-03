#ifndef _ER_CV_EXTRACT_HPP_
#define _ER_CV_EXTRACT_HPP_

#include "erCv.hpp"
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
template< typename Container, typename Criteria>
void erExtractCvPoints( Container &pts, IplImage *im, Criteria crit, CvRect rect=cvRect(0,0,0,0), uint delta=1)
{  
 
  typedef typename Container::value_type CvPoint;
  int y, x;
  for( y = 0; y < im->height; y+=delta)
    { 
      for( x = 0; x < im->width; x+=delta)
	{ 
	  CvScalar a = cvGet2D( im, y, x);
	  if( crit(a.val[0]))
	    { 
	      CvPoint p;
	      p.x = x+rect.x;
	      p.y = y+rect.y;

	      pts.push_back(p); 
	    }
	}
    }
};






/**
   Permet d extraire une ligne continue a partir d une image precedemment filtre
   L'utilisateur doit marquer le debut de la curve ou ligne qu'il souhaite extraire
   \param IplImage* : une image 
   \param erCerc    : cercle pour le debut de la recherche
   \param char **   : ensemble des variables venant de l exterieur file_name[2] doit correspondre
                      au fichier a traiter
   \param Container (template) : container des points a extraire
   \param CvRect    : Rectangle pour extraire remettre les points dans les coordoonees de l image

 */
template< typename Container>
void erExtractCurveMacroDropUser( Container &pts, IplImage* simag, CvRect rect, erCerc* cerc, char* file_name)
{
  //typedef Container typeContainer; 
  typedef std::map< double, Container> erMap;
  erMap ptsMap;
  typename erMap::iterator iterMap, iterMap_border;
  typename Container::iterator iterV_polyvalent, iterV_insidecurv, iterV_border_bas, iterV_border_hau;
  
  for( iterV_polyvalent = pts.begin(); iterV_polyvalent != pts.end(); iterV_polyvalent++)
    {
      ptsMap[iterV_polyvalent->x].push_back(*iterV_polyvalent);
    }
  pts.clear();
  
  std::pair< CvPoint, int> cercle = erCvDebutCurve( simag);
  cercle.first.x = cercle.first.x + rect.x;
  cercle.first.y = cercle.first.y + rect.y;
  std::cout << "centro.x: " << cercle.first.x << std::endl;
  std::cout << "centro.y: " << cercle.first.y << std::endl;
  std::cout << "radio:    " << cercle.second << std::endl;
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
  int SSmap = 7*(ptsMap.size())/10;
  bool candidat;
  iterMap++;
  iterMap_border = ptsMap.end();
  iterMap_border--;
  for( ; iterMap != iterMap_border; iterMap++)
    { 
      int Dmap =  distance( ptsMap.begin(), iterMap);
      CvPoint cpt = pts.back();
      //iterV_pts = pts.begin();
      candidat = false;
      //iterV_border_bas = iterMap->second.begin();
      //iterV_border_hau = iterMap->second.end();
      //iterV_border_hau--;
      if( cpt.y <= rect.y || cpt.y >= rect.y + rect.height)
	{
	  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
	  file << file_name << std::endl;
	  file << std::endl;
	  pts.clear();
	  return;
	}
      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
      if( iterV_polyvalent != iterMap->second.end())
	{
	  candidat = true;
	  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
       	}
      if( !candidat || iterV_insidecurv != pts.end())
	{ 
	  candidat = false;
	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
	  if( iterV_polyvalent != iterMap->second.end())
	    {
	      candidat = true;
	      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
	    }
	  if( !candidat || iterV_insidecurv != pts.end())
	    {
	      candidat = false;
	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
	      if( iterV_polyvalent != iterMap->second.end())
		{
		  candidat = true;
		  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
		}
	      if( !candidat || iterV_insidecurv != pts.end())
		{
		  iterMap--;
		  candidat = false;
		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
		  if( iterV_polyvalent != iterMap->second.end())
		    {
		      candidat = true;
		      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
		    }
		  if( !candidat || iterV_insidecurv != pts.end())
		    {
		      candidat = false;
		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
		      if( iterV_polyvalent != iterMap->second.end())
			{
			  candidat = true;
			  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
			}
		      if( !candidat || iterV_insidecurv != pts.end())
			{
			  if( iterMap == ptsMap.begin())
			    {
			      std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
			      file << file_name << std::endl;
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  iterMap--;
			  candidat = false;
			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
			  if( iterV_polyvalent != iterMap->second.end())
			    {
			      candidat = true;
			      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
			    }
			  if( !candidat || iterV_insidecurv != pts.end())
			    {
			      candidat = false;
			      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
			      if( iterV_polyvalent != iterMap->second.end())
				{
				  candidat = true;
				  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
				}
			      if( !candidat || iterV_insidecurv != pts.end())
				{
				  candidat = false;
				  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y-1));
				  if( iterV_polyvalent != iterMap->second.end())
				    {
				      candidat = true;
				      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
				    }
				  if( !candidat || iterV_insidecurv != pts.end())
				    {
				      if( Dmap >= SSmap)
					{
					  p_polyvalent.x = iterV_polyvalent->x;
					  p_polyvalent.y = iterV_polyvalent->y;
					  pts.push_back( p_polyvalent);
					}
				      else
					{
					  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
					  file << file_name << std::endl;
					  file << std::endl;
					  pts.clear();
					}
				      return;
				    }
				  else
				    {
				      p_polyvalent.x = iterV_polyvalent->x;
				      p_polyvalent.y = iterV_polyvalent->y;
				      pts.push_back( p_polyvalent);
				    }
				}
			      else
				{
				  p_polyvalent.x = iterV_polyvalent->x;
				  p_polyvalent.y = iterV_polyvalent->y;
				  pts.push_back( p_polyvalent);
				}
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	    }
	}
    };  
};



/**
   Permet d extraire une ligne continue a partir d une image precedemment filtre
   \param IplImage* : une image 
   \param erCerc    : cercle pour le debut de la recherche
   \param char **   : ensemble des variables venant de l exterieur file_name[2] doit correspondre
                      au fichier a traiter
   \param Container (template) : container des points a extraire
   \param CvRect    : Rectangle pour extraire remettre les points dans les coordoonees de l image

 */
template< typename Container>
void erExtractCurveMacroDrop( Container &pts, IplImage* simag, CvRect recROI, erCerc* cerc, char* file_name )
{
  //typedef Container typeContainer;
  typedef std::map< double, Container> erMap;
  erMap ptsMap;
  typename erMap::iterator iterMap, iterMap_border;
  typename Container::iterator iterV_construcMap, iterV_cercleDepart, iterV_insidecurv, iterV_polyvalent, iterV_border_bas, iterV_border_hau;
  
  for( iterV_construcMap = pts.begin(); iterV_construcMap != pts.end(); iterV_construcMap++)
    {
      ptsMap[ iterV_construcMap->x].push_back( *iterV_construcMap);
    }
  pts.clear();
  
  std::pair< CvPoint, int> cercle( cerc->centro, cerc->radio);
  CvPoint p_cercleDepart, p_polyvalent;
  std::vector< int> ptsDmin, ptsY0;
  std::vector< int>::iterator iterDmin;
  bool Dmin = false;
  int a = 0, b = 0, c = 0;
  iterMap = ptsMap.begin();
  for( iterV_cercleDepart = iterMap->second.begin(); iterV_cercleDepart != iterMap->second.end(); iterV_cercleDepart++)
    {
      a = abs( iterV_cercleDepart->y - cercle.first.y);
      if( a <= cercle.second)
	{
	  if( a < b || Dmin==false)
	    {
	      c = iterV_cercleDepart->y;
	      Dmin = true;
	      b = a;
	    }
	}
    }
  if( Dmin)
    {      
      p_cercleDepart.x = iterMap->first;
      p_cercleDepart.y = c;
      
      pts.push_back( p_cercleDepart);
      
    }
  else
    {
      std::ofstream file( nameGoodImagesFile( INFOFILE), std::ios_base::app );
      file << file_name << std::endl; // A proscrire
      file << std::endl;
      pts.clear();
      return; 
    }
  int SSmap = 7*(ptsMap.size())/10;
  int A=0;
  bool candidat;
  CvPoint cpt;
  int Dmap;
  iterMap++;
  iterMap_border = ptsMap.end();
  iterMap_border--;
  for( ; iterMap != iterMap_border; iterMap++)
    {       
      Dmap =  distance( ptsMap.begin(), iterMap);
      cpt = pts.back();
      //iterV_pts = pts.begin();
      candidat = false;
      if( cpt.y <= recROI.y || cpt.y >= recROI.y + recROI.height)
	{
	  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
	  file << file_name << std::endl;
	  file << std::endl;
	  pts.clear();
	  return;
	}
      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
      if( iterV_polyvalent != iterMap->second.end())
	{
	  candidat = true;
	  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
	}
      if( !candidat || iterV_insidecurv != pts.end())
	{ 
	  candidat = false;
	  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
	  if( iterV_polyvalent != iterMap->second.end())
	    {
	      candidat = true;
	      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
	    }
	  if( !candidat || iterV_insidecurv != pts.end())
	    {
	      candidat = false;
	      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
	      if( iterV_polyvalent != iterMap->second.end())
		{
		  candidat = true;
		  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
		}
	      if( !candidat || iterV_insidecurv != pts.end())
		{
		  iterMap--;
		  candidat = false;
		  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
		  if( iterV_polyvalent != iterMap->second.end())
		    {
		      candidat = true;
		      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
		    }
		  if( !candidat || iterV_insidecurv != pts.end())
		    {
		      candidat = false;
		      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y - 1));
		      if( iterV_polyvalent != iterMap->second.end())
			{
			  candidat = true;
			  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
			}
		      if( !candidat || iterV_insidecurv != pts.end())
			{
			  if( iterMap == ptsMap.begin())
			    {
			      std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
			      file << file_name << std::endl;
			      file << std::endl;
			      pts.clear();
			      return;
			    }
			  iterMap--;
			  candidat = false;
			  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y + 1));
			  if( iterV_polyvalent != iterMap->second.end())
			    {
			      candidat = true;
			      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
			    }
			  if( !candidat || iterV_insidecurv != pts.end())
			    {
			      candidat = false;
			      iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y));
			      if( iterV_polyvalent != iterMap->second.end())
				{
				  candidat = true;
				  iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
				}
			      if( !candidat || iterV_insidecurv != pts.end())
				{
				  candidat = false;
				  iterV_polyvalent = erFindCvPoint( iterMap->second.begin(), iterMap->second.end(), cvPoint( iterMap->first, cpt.y-1));
				  if( iterV_polyvalent != iterMap->second.end())
				    {
				      candidat = true;
				      iterV_insidecurv = erFindCvPoint( pts.begin(), pts.end(), *iterV_polyvalent);
				    }
				  if( !candidat || iterV_insidecurv != pts.end())
				    {
				      if( Dmap >= SSmap)
					{
					  p_polyvalent.x = iterV_polyvalent->x;
					  p_polyvalent.y = iterV_polyvalent->y;
					  pts.push_back( p_polyvalent);
					}
				      else
					{
					  std::ofstream file( nameGoodImagesFile(INFOFILE), std::ios_base::app );
					  file << file_name << std::endl;
					  file << std::endl;
					  pts.clear();
					}
				      return;
				    }
				  else
				    {
				      p_polyvalent.x = iterV_polyvalent->x;
				      p_polyvalent.y = iterV_polyvalent->y;
				      pts.push_back( p_polyvalent);
				    }
				}
			      else
				{
				  p_polyvalent.x = iterV_polyvalent->x;
				  p_polyvalent.y = iterV_polyvalent->y;
				  pts.push_back( p_polyvalent);
				}
			    }
			  else
			    {
			      p_polyvalent.x = iterV_polyvalent->x;
			      p_polyvalent.y = iterV_polyvalent->y;
			      pts.push_back( p_polyvalent);
			    }
			}
		      else
			{
			  p_polyvalent.x = iterV_polyvalent->x;
			  p_polyvalent.y = iterV_polyvalent->y;
			  pts.push_back( p_polyvalent);
			}
		    }
		  else
		    {
		      p_polyvalent.x = iterV_polyvalent->x;
		      p_polyvalent.y = iterV_polyvalent->y;
		      pts.push_back( p_polyvalent);
		    }
		}
	      else
		{
		  p_polyvalent.x = iterV_polyvalent->x;
		  p_polyvalent.y = iterV_polyvalent->y;
		  pts.push_back( p_polyvalent);
		}
	    }
	  else
	    {
	      p_polyvalent.x = iterV_polyvalent->x;
	      p_polyvalent.y = iterV_polyvalent->y;
	      pts.push_back( p_polyvalent);
	    }
	}
    };  
};




/**
   Permmet de convertir les dimensions et cordonnes des curves de pixels sur l image a valeurs reels en MKS 
   \param std::pair< double, double> : facteur de convercion pour l axe X et pour l axe Y
   \param Container                  : vecteur ou liste avec les coordones des points en pixels a convertir en MKS
   \param char*                      : nom de l image en traitement
   \param char*                      : nom de l image de sortie
*/
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




/**
   Focntion permettant d ecrir les segments du type CgalSegment du contenair pts dans un ficher
   L extention par defaul du ficher est .txt
   \param Container  : vecteur ou liste des segments du type CgalSegment
   \param char*      : nom de l image en cours de traitement
   \param char*      : nom que portera le ficher
*/
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








/**
   Fonction permettant d ecrir les points du type CvPoint du contenair pts dans un ficher
   L extention par defaul du ficher est .txt
   \param Container : vecteur ou liste des points du type CvPoint
   \param char*     : nom de l image en cours de traitement
   \param char*     : nom qui portera le ficher

 */
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
      //std::cout << "p1->y: " << p1->y << " " << "punto.y: " << punto.y << " " << "p1->x: " << p1->x << " " << "punto.x: " << punto.x << std::endl;
      if( (p1->y == punto.y) && (p1->x == punto.x))
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




