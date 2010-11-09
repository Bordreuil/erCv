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
#ifndef _ER_PREDICATES_HPP_
#define  _ER_PREDICATES_HPP_

/** @file erPredicates.hpp 
  \brief Fichier 
  \defgroup utilities Utilities
  Contient quelques utilitaires tel que des criteres, des fonctions d ouvertures de fichier
*/

/** \addtogroup utilities */
/*@{*/

#include "highgui.h"

class CriteriaFunctor /** < Classe interface permettant 
			  d avoir des tests sur les entiers
		      */
{
public:
  CriteriaFunctor();
  CriteriaFunctor(int);
  ~CriteriaFunctor();
  void set_value(int);   /** < On peut modifier la valeur de comparaison avec cette methode */
  int  get_value();     /** < Permet de visualiser la valeur de comparaison  */
  virtual bool operator()(int) = 0;
private:
  int __value;

};

class IsEqualTo:public CriteriaFunctor /** < Functor pour comparer un entier a une valeur */
{
public:
  IsEqualTo(int);
  bool operator()(int);
};

class IsGreaterThan:public CriteriaFunctor /** < Functor pour comparer plus grand que la valeur */
{
public:
  IsGreaterThan(int);
  bool operator()(int);
};

class IsGreaterEqual:public CriteriaFunctor /** < Functor pour comparer plus grand ou egale que la valeur */
{
public:
  IsGreaterEqual(int);
  bool operator()(int);
};

class IsLessThan:public CriteriaFunctor  /** < Functor pour comparer plus petit  que la valeur */
{
public:
  IsLessThan(int);
  bool operator()(int);
};
class IsLessEqual:public CriteriaFunctor  /** < Functor pour comparer plus petit egual  que la valeur */
{
public:
  IsLessEqual(int);
  bool operator()(int);
};

class IsBetween:public CriteriaFunctor  /** < Functor pour comparer entre deux valeurs */
{
public:
  IsBetween(int,int);
  void set_upper_value(int);
  bool operator()(int);
private:
  int __upper_value,__lower_value;
};

// template< typename Point>
// bool erCompareXPoint( Point p1, Point p2)
// {
//   return p1.x < p2.x;
// };
class erCompareXPoint
{
public:
  bool operator()( CvPoint2D32f p1, CvPoint2D32f p2);
};


/*@}*/
#endif
