#ifndef _ERCV_MANIP_FILE_NAME_HPP_
#define _ERCV_MANIP_FILE_NAME_HPP_

#include<utility>
/**
   Fonctions utilitaires permettant de recuperer un nom de
   fichier et de concatener des chaines de charactere et des entiers
   pour ecrire un nouveau fichier
 */

std::pair< bool, const char* > erGetNumberInFileName( char*);

char* erConcatenateFileName( char*, char*, int, char*);



#endif 
