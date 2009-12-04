#ifndef _ERCV_CONNECTED_SEGMENTS_HPP_
#define _ERCV_CONNECTED_SEGMENTS_HPP_

#include <boost/config.hpp>
#include <iostream>
#include <vector>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <erCv/geometry/erCgalBase.hpp>

template<typename Iter>
bool segments_set_is_closed(Iter debut,Iter fin)
{
  std::map<Point_2,uint> ncompt;
  for(;debut!=fin;debut++)
    {
      ncompt[debut->source()]++;
      ncompt[debut->target()]++;
    };
  std::map<Point_2,uint>::iterator dede=ncompt.begin();
  while(dede!=ncompt.end())
    {
      if( dede->second < 2) return false;
      dede++;
    };
  return true;

};

typedef boost::adjacency_list < boost::vecS, 
				boost::vecS, 
				boost::undirectedS, 
				boost::property<boost::vertex_name_t,Point_2> > Graph;

typedef boost::property_map<Graph,boost::vertex_name_t>::type Points_graph_map_t;

typedef boost::graph_traits < Graph >::vertex_descriptor      Vertex;
typedef std::map<Point_2,Vertex>                              PointVertexMap;

template<typename Iterator>
std::list<Segment_2>  get_connected_segments(Iterator debut,Iterator fin)
{ 
  Graph graph;
  PointVertexMap points;
  bool inserted1,inserted2;
  typedef PointVertexMap::iterator MapIterator;
  Points_graph_map_t points_graph = boost::get(boost::vertex_name,graph);
 
  MapIterator    ip1,ip2;
  Vertex u,v;
  uint id_vertex=0;
  for(;debut!=fin;debut++)
    { uint id1,id2;

      boost::tie(ip1,inserted1) = points.insert(std::make_pair(debut->source(),Vertex()));
      boost::tie(ip2,inserted2) = points.insert(std::make_pair(debut->target(),Vertex()));

      if(inserted1)
	{
	  u= boost::add_vertex(graph);
	  ip1->second = u;
	  points_graph[u] = debut->source();
	}
      else{u=ip1->second;};
      
      if(inserted2)
	{
	  v= boost::add_vertex(graph);
	  ip2->second = v;
	  points_graph[v] = debut->target();
	}
      else{v=ip2->second;};
      boost::add_edge(u,v,graph);
    };

  std::vector<int> connect(boost::num_vertices(graph));
  
  int num = boost::connected_components
    (graph, boost::make_iterator_property_map(connect.begin(), boost::get(boost::vertex_index, graph), connect[0]));

  std::cout << "Nombre de sommet du graphe:" << boost::num_vertices(graph) << std::endl;
  std::cout << "Nombre de domaine connecte:" << num  << std::endl; 

  boost::graph_traits<Graph>::edge_iterator     ei,ei_end;
  typedef  std::map<uint,std::list<Segment_2> > MapOfSegments;
  MapOfSegments map_of_connected;

  for(boost::tie(ei,ei_end)=boost::edges(graph);ei!=ei_end;ei++)
    {
      Vertex uv = boost::source(*ei,graph);
      Vertex vu = boost::target(*ei,graph);

      map_of_connected[connect[uv]].push_back(Segment_2(points_graph[uv],points_graph[vu]));

    };

  MapOfSegments::iterator deb,fi;
  std::list<Segment_2>  output;
  uint nmax=0;
  uint current=0;
  for(deb=map_of_connected.begin();deb!=map_of_connected.end();deb++)
    {
      if(segments_set_is_closed(deb->second.begin(),deb->second.end()))
      {
	//output.push_back(deb->second);
	  if(deb->second.size() > nmax)
	    {
	      nmax=deb->second.size();
	      output = deb->second;
	    };
      };
	
    };
  
  return output;
};


#endif
