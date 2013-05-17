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
#ifndef _ERCV_GRAPH_HPP_
#define _ERCV_GRAPH_HPP_

#include <boost/config.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <erCv/geometry/erCgalBase.hpp>

/** 
    Definition des types pour la gestion des graphes
*/
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, 
				     boost::undirectedS>::vertex_descriptor Vertex;

typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS, 
				boost::property< boost::vertex_name_t, CgalPoint,
						 boost::property<boost::vertex_index_t,int,
						 boost::property<boost::vertex_distance_t, int,
						 boost::property<boost::vertex_predecessor_t,Vertex> > > >,
				boost::property<boost::edge_weight_t, int> > Graph;

typedef boost::property_map< Graph, boost::vertex_name_t>::type                  Points_graph_map_t;
typedef boost::graph_traits< Graph>::vertex_descriptor                           Vertex;
typedef boost::graph_traits<Graph>::adjacency_iterator                           NeighbourVertexIterator;

class ComparePoint
{
public :
bool operator()(CgalPoint pt1,CgalPoint pt)
{
  if(CGAL::squared_distance(pt1,pt) < 1.e-8) return false;
  return CGAL::lexicographically_xy_smaller(pt1,pt);

};
};
typedef std::map< CgalPoint, Vertex,ComparePoint>            PointVertexMap;


//typedef std::map< CgalPoint, Vertex>                                             PointVertexMap;

template<typename Iterator>
std::pair<Graph,PointVertexMap> constructGraphFromSegments(Iterator debut,Iterator fin)
{
  Graph graph;
  PointVertexMap points;
  bool inserted1,inserted2;
  typedef PointVertexMap::iterator MapIterator;
  Points_graph_map_t points_graph = boost::get( boost::vertex_name, graph);
  
  MapIterator    ip1,ip2;
  Vertex u,v;
  uint id_vertex = 0;
  for( ;debut != fin;debut++)
    { uint id1,id2;

      boost::tie( ip1,inserted1) = points.insert( std::make_pair( debut->source(), Vertex()));
      boost::tie( ip2,inserted2) = points.insert( std::make_pair( debut->target(), Vertex()));
      
      if( inserted1)
	{
	  u= boost::add_vertex( graph);
	  ip1->second = u;
	  points_graph[ u] = debut->source();
	}
      else
	{ 
	  u=ip1->second;
	}
      
      if( inserted2)
	{
	  v= boost::add_vertex( graph);
	  ip2->second = v;
	  points_graph[ v] = debut->target();
	}
      else
	{
	  v=ip2->second;
	}
      boost::add_edge( u, v, graph);
    };
  return std::make_pair(graph,points);
};

std::list<CgalPoint> erLinkedListOfVertex(Graph& graph)
{
      std::list<CgalPoint> linkedPoints;
      typedef boost::property_map<Graph,boost::vertex_name_t>::type VertexName;
      Vertex depart             = boost::vertex(0,graph);
 
      std::list<Vertex>           visitedVertices;
      std::list<Vertex>::iterator iterg,iterd;
      NeighbourVertexIterator     gauche,droite;

      visitedVertices.push_back(depart);
      boost::tie(gauche,droite) = boost::adjacent_vertices(depart,graph);

      visitedVertices.push_back(*gauche);
      depart = *gauche;
      int num_loop=0;
      while(visitedVertices.size() < boost::num_vertices(graph) && num_loop < 10000)
	{
	  num_loop++;
	  boost::tie(gauche,droite) = boost::adjacent_vertices(depart,graph);
	  iterg = std::find(visitedVertices.begin(),visitedVertices.end(),*gauche);
	  iterd = std::find(visitedVertices.begin(),visitedVertices.end(),*(--droite));
	  if (iterg != visitedVertices.end() and iterd == visitedVertices.end())
	    {

	      depart = *(droite);
	      visitedVertices.push_back(depart);
	    }
	  if (iterg == visitedVertices.end() and iterd != visitedVertices.end())
	    {
	      visitedVertices.push_back(*gauche);
	      depart = *gauche;
	    }
       
     
	}
      for(iterg=visitedVertices.begin();iterg!=visitedVertices.end();iterg++)
	{ CgalPoint pt = boost::get(boost::vertex_name,graph,*iterg);
	  linkedPoints.push_back(pt);
	}
      return linkedPoints;
};

#endif
