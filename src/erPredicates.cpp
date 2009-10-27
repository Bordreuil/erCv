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
  
