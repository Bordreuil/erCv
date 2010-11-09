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
#include<erCv/erCvFiltersParams.hpp>

erSmootP::erSmootP():size(7),type(BLUR){};
erSmootP::erSmootP(SmoothType st,int si):size(si),type(st){};

erCannyP::erCannyP():trh1(150),trh2(150){};
erCannyP::erCannyP(int t1,int t2):trh1(t1),trh2(t2){};

erDilatP::erDilatP():iter(1){};
erDilatP::erDilatP( int it):iter(it){};

erErodeP::erErodeP():iter(1){};
erErodeP::erErodeP( int itr):iter(itr){};

erThresP::erThresP():type(THRESH_BINARY_),trh1(150),trh2(255){};
erThresP::erThresP( ThresholdType tt, int th1, int th2):type(tt), trh1(th1), trh2(th2){};

erAdThrP::erAdThrP():type(THRESH_BINARY),adpt(AM_MEAN),trhP(10),neig(7),trh0(51){};
erAdThrP::erAdThrP(AdaptiveThresholdType tt,AdaptiveMethodType mt ,int thrp,int neig,int thr0):
  type(tt),adpt(mt),trhP(thrp),neig(neig),trh0(thr0){};



std::ostream& operator << (std::ostream& o,const erSmootP es)
{
  o << "** Begin Smooth Parameter : \n";
  o << "\tSize\t:\t" << es.size << std::endl;
  o << "\tType\t:\t" << es.type << std::endl;
  o << "** End Smooth Parameter------\n";
  return o;
};

std::ostream& operator << (std::ostream& o,const erCannyP ec)
{
  o << "** Begin Canny Parameter : \n";
  o << "\tThreshold 1\t:\t" << ec.trh1 << std::endl;
  o << "\tThreshold 2\t:\t" << ec.trh2 << std::endl;
  o << "** End Canny Parameter------\n";

  return o;
};


std::ostream& operator << (std::ostream& o,const erAdThrP ea)
{
  o << "** Begin Adaptive Threshold Parameter : \n";
  o << "\tAdaptive Threshold Type\t:\t" << ea.type << std::endl;
  o << "\tAdaptive Method Type\t:\t"    << ea.adpt<< std::endl;
  o << "\tThreshold Parameter\t:\t" << ea.trhP << std::endl;
  o << "\tNeighbour\t\t:\t"    << ea.neig<< std::endl;
  o << "\tThreshold\t\t:\t"    << ea.trh0<< std::endl;
  o << "** End Adaptive Threshold Parameter------\n";
  
  return o;
};
