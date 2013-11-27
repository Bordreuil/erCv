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
#include <erCv/utilities/erPredicates.hpp>

CriteriaFunctor::CriteriaFunctor():__value(0){};
CriteriaFunctor::CriteriaFunctor(int value):__value(value){};
CriteriaFunctor::~CriteriaFunctor(){};
void CriteriaFunctor::set_value(int value){__value=value;};
int CriteriaFunctor::get_value(){return __value;};

IsEqualTo::IsEqualTo(int val):CriteriaFunctor(val){};
bool IsEqualTo::operator()(int val)
{
  return val == get_value();
};

IsGreaterThan::IsGreaterThan(int val):CriteriaFunctor(val){};
bool IsGreaterThan::operator()(int val)
{
  return val > get_value();
};

IsGreaterEqual::IsGreaterEqual(int val):CriteriaFunctor(val){};
bool IsGreaterEqual::operator()(int val)
{
  return val>= get_value();
};

IsLessThan::IsLessThan(int val):CriteriaFunctor(val){};
bool IsLessThan::operator()(int val)
{
  return val < get_value();
};

IsLessEqual::IsLessEqual(int val):CriteriaFunctor(val){};
bool IsLessEqual::operator()(int val)
{
  return val <=get_value();
};

IsBetween::IsBetween(int lower_bound,int upper_bound):__lower_value(lower_bound),
						      __upper_value(upper_bound){};
void IsBetween::set_upper_value(int val){__upper_value = val;};
bool IsBetween::operator()(int val)
{
  return ((val>__lower_value) && (val<__upper_value));
};


bool erCompareXPoint::operator()( CvPoint2D32f p1, CvPoint2D32f p2)
{
  return( p1.x < p2.x);
};
  
