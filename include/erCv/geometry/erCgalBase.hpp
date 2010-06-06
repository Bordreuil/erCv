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

typedef K::FT          CgalFTrai;
typedef K::Point_2     CgalPoint;
typedef K::Line_2      CgalLine;
typedef K::Segment_2   CgalSegmt;
typedef K::Triangle_2  CgalTrian;
typedef K::Vector_2    CgalVect;
/*@}*/
#endif
