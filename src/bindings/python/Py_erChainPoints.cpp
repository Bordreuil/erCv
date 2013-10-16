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

#include<erCv/geometry/erCgalBase.hpp>
#include<erCv/geometry/erCgalAlphaShape2.hpp>
#include <erCv/graph/erConnectedSegments.hpp>
#include<boost/python.hpp>



namespace bp = boost::python;

bp::list erChainPoints(boost::python::list pts,double alphaShapeParam)
{
  int lpts              = bp::len(pts);
  std::list< CgalPoint> cgalPts;
  std::list< CgalSegmt> cgalSegs;
  
  for(int i=0;i<lpts;i++)
    {
      bp::list coord = bp::extract<bp::list>(pts[i]);
      double x = bp::extract<double>(coord[0]);
      double y = bp::extract<double>(coord[1]);
      cgalPts.push_back(CgalPoint(x,y));
    }
   erAlphaP param_alpha_shape(alphaShapeParam);
   erAlphaEdges( cgalPts, cgalSegs, &param_alpha_shape);
   BgraphSegmtMap  connectedSegments = getConnectedSegments( cgalSegs.begin(), cgalSegs.end());
   bp::list output;
   BgraphSegmtMap::iterator debut,fin;
   fin= connectedSegments.end();
   for(debut=connectedSegments.begin();debut!=fin;debut++)
     {
       BgraphSegmt          sgs = debut->second;
       BgraphSegmt::iterator ds,fs;
       ds=sgs.begin();
       fs=sgs.end();
       bp::list conn_seg;
       for(;ds!=fs;ds++)
	 {
	   CgalPoint src = ds->source();
	   CgalPoint tar = ds->target();
	   bp::list  psrc,ptar;
	   psrc.append(src.x());psrc.append(src.y());
	   ptar.append(tar.x());ptar.append(tar.y());
	   bp::list seg;
	   seg.append(psrc);seg.append(ptar);
	   conn_seg.append(seg);
	 };
       output.append(conn_seg);
     }
   return output;
};
void export_erChainPoints()
{
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    def("erChainPoints",&erChainPoints,
	"Chaine les points suivant une methode de alpha shape");
 
};
