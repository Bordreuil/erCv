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
#include<CGAL/Exact_predicates_inexact_constructions_kernel.h>

/** \brief  defintion du type de noyau */
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::FT          CgFTrai;
typedef K::Point_2     CgPoint;
typedef K::Segment_2   CgSegmt;
typedef K::Triangle_2  CgTrian;

/*@}*/
#endif
