#include <erCv/utilities/erFileUtilities.hpp>

bool erFileExists(char* name_file)
{   bool exist=true;
    FILE * file    = fopen(name_file,"r");
    if(file==NULL)
      {
	std::cout << "...Le fichier\t:" << name_file << "\t n existe pas\n";
	exist=false;
      }
    
    return exist;

}
