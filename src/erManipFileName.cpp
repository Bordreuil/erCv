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
#include <erCv/utilities/erManipFileName.hpp>
#include<string>
#include<boost/lexical_cast.hpp>
#include<iostream>


std::pair<bool,const char*>   erGetNumberInFileName(char* file_name)
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




char* erConcatenateFileName( char* base, char* added, char* num, char* extension)
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
