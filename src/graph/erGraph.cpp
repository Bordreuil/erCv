#include<erCv/graph/erGraph.hpp>

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
