#ifndef _ER_CV_EXTRACT_HPP_
#define _ER_CV_EXTRACT_HPP_
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
void erExtractPoints( IplImage *im, Container &pts, Criteria crit)
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
	      p.x = x;
	      p.y = y;
	      pts.push_back(p); 

	    }
	}
    }
};
//int* ptr = (int*)(im->imageData + y*im->widthStep ); (linea de commando alternativa, va entre los for)



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
/*@}*/
#endif
