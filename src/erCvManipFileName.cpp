#include <erCv/utilities/erManipFileName.hpp>
#include<string>
#include<boost/lexical_cast.hpp>
#include<iostream>
std::pair<bool,const char*>   get_number_in_file_name(char* file_name)
{ 
  bool good_format = true;
  std::string name( file_name);
  size_t ext_pos  = name.find_last_of( '_' );
  size_t ext_pos1 = name.find_last_of( '.');
  std::string name3;
  if( ext_pos != std::string::npos && ext_pos1 != std::string::npos )
    {
      std::string ext2 = name.substr( ext_pos + 1);
      std::string name2 = ext2.substr( 0,  ext_pos1 - (ext_pos + 1));
      //num = boost::lexical_cast<int>( name2);
      //name3 = boost::lexical_cast<std::string>(num);
      while(name2.size()>name3.size())
	{
	  name3.insert( 0, "0" );
	};
    }
  else
    { 
      good_format = false;
      std::cout << "Attention le nom de fichier doit contenir un numero de fichier\n";
      std::cout << "    encadre par _ et l extension du fichier.\n";
    };
  return std::make_pair(good_format,name3.c_str());
};
char* concatenate_file_name(char* base,char* added,char* num,char* extension)
{

      std::string name4(base);
      name4+= added;
      name4+= num;
      name4+= extension;
      char* new_name = new char[ name4.size() + 1];
      std::copy( name4.begin(), name4.end(), new_name);
      new_name[ name4.size()] = '\0';
      return new_name;
};
