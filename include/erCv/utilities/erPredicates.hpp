#ifndef _ER_PREDICATES_HPP_
#define  _ER_PREDICATES_HPP_

/** @file erPredicates.hpp 
  \brief Fichier 
  \defgroup utilities Utilities
  Contient quelques utilitaires tel que des criteres, des fonctions d ouvertures de fichier
*/

/** \addtogroup utilities */
/*@{*/
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

/*@}*/
#endif
