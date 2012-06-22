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
#ifndef _ERCV_SHORTEST_PATHS_HPP_
#define _ERCV_SHORTEST_PATHS_HPP_

#include<list>
#include<boost/graph/dijkstra_shortest_paths.hpp>
#include<erCv/erCvBase.hpp>
#include "erGraph.hpp"
#include "erGraphTools.hpp"


template<typename Iterator>
std::list<CgalPoint> erGetShortestPath(Iterator debut,Iterator fin,erCerc zone_debut,erCerc zone_fin)
{
  std::list<CgalPoint> cgal_wire_points;
  Graph                graph;
  PointVertexMap       points;
  
  boost::tie(graph,points) = constructGraphFromSegments(debut,fin);

  bool   find_begin  ,find_end  ;
  Vertex begin_vertex,end_vertex;

  boost::tie(find_begin,begin_vertex) = findVertexInCerc(points,zone_debut);
  boost::tie(find_end  ,end_vertex  ) = findVertexInCerc(points,zone_fin);
  
  if(find_begin && find_end)
    {
      boost::property_map<Graph, boost::vertex_name_t>::type  cgp      = boost::get(boost::vertex_name, graph);
      boost::property_map<Graph, boost::vertex_index_t>::type indexmap = boost::get(boost::vertex_index, graph);
     
      boost::graph_traits<Graph>::vertex_iterator ibeg,iend;

      boost::property_map<Graph, boost::vertex_distance_t>::type    d         = boost::get(boost::vertex_distance, graph);
      boost::property_map<Graph, boost::vertex_predecessor_t>::type p         = boost::get(boost::vertex_predecessor, graph);
      boost::property_map<Graph, boost::edge_weight_t>::type        weightmap = boost::get(boost::edge_weight, graph);
      
      boost::dijkstra_shortest_paths(graph,begin_vertex, p, d, weightmap, indexmap, 
			      std::less<int>(), boost::closed_plus<int>(), 
                          (std::numeric_limits<int>::max)(), 0,
			  boost::default_dijkstra_visitor());

      Vertex current = end_vertex;
      while(current != begin_vertex)
	{
	  cgal_wire_points.push_back(cgp[current]);
	  current = p[current];
	};
      cgal_wire_points.reverse();
    }
  else
    {
      if (! find_begin)
	{
	  std::cout << "Warning: Begin Vertex not found\n";
	}
      if(! find_end)
	{
	  std::cout << "Warning: End Vertex not found\n";
	}
    };

  return cgal_wire_points;
  
};


#endif
