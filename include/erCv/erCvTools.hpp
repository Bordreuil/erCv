#ifndef _erCv_Tools_HPP_
#define  _erCv_Tools_HPP_

/** \addgroup tools Tools */
/** \addtogroup tools */
/*@{*/

// Classe permettant 
class erImageIncrement
{
public:
  erImageIncrement();
  erImageIncrement(int,int,int);
  int inc();
 
private:
  int base;   /** <   increment normal de base*/ 
  int delta; /** <   increment extraordinaire*/ 
  int every; /** <   tous les every images*/ 
  int current; 
};
/*@}*/
#endif
