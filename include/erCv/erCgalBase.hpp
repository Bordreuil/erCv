#ifndef _erCgalBase_hpp_
#define _erCgalBase_hpp_

/**
   \brief Le type de noyau pour la construction geometrique est defini
   des objets 2d
*/
/** \defgroup cgal CGAL */
/**  Aide de cgal http://www.cgal.org */
/**\addtogroup cgal */
/*@{*/
#include<CGAL/exact_predicates_exact_constructions_kernel.h>

/** \brief  defintion du type de noyau */
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef K::Point_2    Point_2;
typedef K::Triangle_2 Triangle_2;

/*@}*/
#endif
