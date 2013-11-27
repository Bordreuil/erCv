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
#include <erCv/graph/erShortestPaths.hpp>
#include<erCv/erCvBase.hpp>
//#include "Triangulation_delaunay_2.hpp"
// #include <iostream>


// namespace bp = boost::python;

typedef std::vector<CgalPoint> CgalPoints;
typedef std::list<CgalSegmt> CgalSegments;


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



//template<typename Graph>
// class graphIsClosed
// {
// public:
//   typedef typename  boost::graph_traits<Graph>::vertex_descriptor Vertex;
//   typedef typename  std::pair<Vertex,Vertex> Output;
//   graphIsClosed(Graph& gr)
//   {
//     _gr = gr;
//   }
//   bool is_closed()
//   {
//     typename boost::graph_traits<Graph>::edge_iterator ebeg,eend;
    
//     typename std::map<Vertex,uint> ncount;
//     boost::tie(ebeg,eend) = boost::edges(_gr);
//     for(;ebeg!=eend;ebeg++)
//       {
// 	ncount[boost::source(*ebeg,_gr)]++;
// 	ncount[boost::target(*ebeg,_gr)]++;
//       }
//     _ncount = ncount;
//     typename std::map< Vertex, uint>::iterator dede=ncount.begin();
//     while( dede != ncount.end())
//       {
// 	if( dede->second < 2) return false;
// 	dede++;
//       };
    
//     return true;
//   }
//  Output borders()
//   {
//     typename std::map< Vertex, uint>::iterator dede=_ncount.begin();
//     typename std::pair<Vertex,Vertex> borders;
//     bool first(true);
//     while( dede != _ncount.end())
//       {  //std::cout << dede->first << " " << dede->second << std::endl;
// 	if( dede->second < 2)
// 	  { 
// 	    if(first){borders.first = dede->first;first=false;}
// 	    else{borders.second = dede->first;}
// 	  }
// 	  dede++;
//       };
//     return borders;
//   };
// private:
//   Graph _gr;
//   std::map<Vertex,uint> _ncount;
// };

bp::list erShortestPathInSegments(bp::list edges,bp::list startPoint,bp::list endPoint,int radius)
{
  int nlist = boost::python::len(edges);
 
  CgalSegments segments;
  for(int i=0;i< nlist;i++)
    {
      boost::python::list edge   = boost::python::extract<boost::python::list>(edges[i]);
      boost::python::list source = boost::python::extract<boost::python::list>(edge[0]);
      boost::python::list target = boost::python::extract<boost::python::list>(edge[1]);
      double xsource = boost::python::extract<double>(source[0]);
      double ysource = boost::python::extract<double>(source[1]);
      double xtarget = boost::python::extract<double>(target[0]);
      double ytarget = boost::python::extract<double>(target[1]);

      CgalPoint psource(xsource,ysource);
      CgalPoint ptarget(xtarget,ytarget);
      CgalSegmt seg(psource,ptarget);
      segments.push_back(seg);
    };
 int xstart = boost::python::extract<int>(startPoint[0]);
 int ystart = boost::python::extract<int>(startPoint[1]);
 int xend = boost::python::extract<int>(endPoint[0]);
 int yend = boost::python::extract<int>(endPoint[1]);

 erCerc zone_debut(xstart,ystart,radius);
 erCerc zone_fin(xend,yend,radius);

 std::list<CgalPoint> polyg = erGetShortestPath(segments.begin(),segments.end(),zone_debut,zone_fin);

 std::vector<CgalPoint> polygone(polyg.begin(),polyg.end());
 bp::list pol;
 for(int i=0;i<polygone.size();i++)
   {
     bp::list pt;
     pt.append(CGAL::to_double(polygone[i].x()));
     pt.append(CGAL::to_double(polygone[i].y()));
     pol.append(pt);
   };
   
 return pol;

}

void export_erChainPoints()
{
    boost::python::numeric::array::set_module_and_type("numpy", "ndarray");
    def("erChainPoints",&erChainPoints,
	"Chaine les points suivant une methode de alpha shape");
    def("erShortestPathInSegments",&erShortestPathInSegments,
	"Extrait un polygone d'un ensemble de segments entre deux points");
 
};
