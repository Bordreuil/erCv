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
#ifndef _ERCV_CONNECTED_SEGMENTS_HPP_
#define _ERCV_CONNECTED_SEGMENTS_HPP_


#include <iostream>
#include <vector>
#include <boost/graph/connected_components.hpp>
#include "erGraph.hpp"


/** Definition de qq typedef 

 */
typedef  std::list< CgalSegmt>                 BgraphSegmt;
typedef  std::map< uint, BgraphSegmt>          BgraphSegmtMap;



/** 
    Un critere pour detecte si la liste ou le vecteur de segments est bien ferme
*/
class SegmentsSetIsClosed
{
public:
  SegmentsSetIsClosed(){};
  template< typename Iter>
  bool operator ()( Iter debut, Iter fin)
  {
    
    
    Iter it;
    _ncompt.clear();
    for( it = debut; it!=fin; it++)
      { 
	_ncompt[ it->source()]++;
	_ncompt[ it->target()]++;
      };
   
    std::map< CgalPoint, uint>::iterator dede=_ncompt.begin();
    while( dede != _ncompt.end())
      {
	
	if( dede->second < 2) {return false;};
	dede++;
      };
    return true;
    
  };
  std::pair<CgalPoint,CgalPoint> borders()
  {
    std::map< CgalPoint, uint>::iterator dede=_ncompt.begin();
    std::pair<CgalPoint,CgalPoint> borders;
    bool first(true);
    while( dede != _ncompt.end())
      {
	if( dede->second < 2)
	  {
	    if(first){borders.first = dede->first;first=false;}
	    else{borders.second = dede->first;}
	  }
	  dede++;
      };
    return borders;
  };
private:
  std::map<CgalPoint,uint> _ncompt;
};


/**
   Interface avec boost::graph pour trouver les segments connectes entre eux
   La sortie est une map ou chaque numero repere un ensemble connecte
*/
template< typename Iterator>
BgraphSegmtMap  getConnectedSegments( Iterator debut, Iterator fin)
{ 
  Graph graph;
  PointVertexMap points;
  boost::tie(graph,points) = constructGraphFromSegments(debut,fin);

  Points_graph_map_t points_graph = boost::get( boost::vertex_name, graph);
  
  std::vector< int> connect( boost::num_vertices( graph));
  
  int num = boost::connected_components
    ( graph, boost::make_iterator_property_map( connect.begin(),boost::get( boost::vertex_index, graph), connect[0]));
  
  boost::graph_traits< Graph>::edge_iterator     ei,ei_end;
  BgraphSegmtMap map_of_connected;
  
  for( boost::tie( ei, ei_end) = boost::edges( graph);ei != ei_end; ei++)
    {
      Vertex uv = boost::source( *ei,graph);
      Vertex vu = boost::target( *ei,graph);
      
      map_of_connected[ connect[ uv]].push_back( CgalSegmt( points_graph[uv], points_graph[ vu]));
      
    };
  return map_of_connected;
  
};


/**
   Ensuite il faut appliquer un critere sur les ensembles connectes
   
*/
template< typename Criteria>
BgraphSegmt filterMapOfSegments( BgraphSegmtMap& map_of_connected, Criteria& crit)
{
  BgraphSegmtMap::iterator deb,fi;
  BgraphSegmt output;
  uint nmax    = 0;
  uint current = 0;
  
  for( deb = map_of_connected.begin(); deb != map_of_connected.end(); deb++)
    
    { 
      bool Criterio = crit( deb->second.begin(), deb->second.end());
 
      if( crit( deb->second.begin(), deb->second.end()))
      	{	  
	  if(deb->second.size() > nmax)
	    {
	      nmax   = deb->second.size();
	      output = deb->second;
	      
	    };
	  	};
      
    };
  
  return output;
};

template< typename Criteria>
BgraphSegmtMap filterMapOfSegmentsWithCriteria( BgraphSegmtMap& map_of_connected, Criteria& crit)
{
  BgraphSegmtMap::iterator deb,fi;
  BgraphSegmtMap output;
  uint nmax    = 0;
  uint current = 0;
  
  for( deb = map_of_connected.begin(); deb != map_of_connected.end(); deb++)
    
    { 
      bool Criterio = crit( deb->second.begin(), deb->second.end());
 
      if( crit( deb->second.begin(), deb->second.end()))
      	{	  
	  output[deb->first] = deb->second;
	};
      
    };
  
  return output;
};

BgraphSegmt filterLargestMapOfSegments( BgraphSegmtMap& map_of_connected)
{
  BgraphSegmtMap::iterator deb,fi;
  BgraphSegmt output;
  uint nmax=0;
  uint current=0;
  
  for( deb = map_of_connected.begin(); deb != map_of_connected.end(); deb++)
    {  
 
	  if(deb->second.size() > nmax)
	    {
	      nmax   = deb->second.size();
	      output = deb->second;
	      
	    };
	
      
    };
  
  return output;
};



template< class Container, class Container2>
void erLargestClosedPolygon( Container cgalSegmts, Container2& bgraphSegmts)
{
  BgraphSegmtMap c_segment = getConnectedSegments( cgalSegmts.begin(), cgalSegmts.end());
  //std::cout << "Nombre de graphe connecte:",c_segment.size() << std::endl;
  SegmentsSetIsClosed criteria;
  bgraphSegmts = filterMapOfSegments( c_segment, criteria);
};

template< class Container, class Container2>
void erLargestPolygon( Container cgalSegmts, Container2& bgraphSegmts)
{
  BgraphSegmtMap c_segment = getConnectedSegments( cgalSegmts.begin(), cgalSegmts.end());
  
  bgraphSegmts = filterLargestMapOfSegments( c_segment);
};
template< class Container>
void erConnectedSegments( Container cgalSegmts, BgraphSegmtMap& c_segments)
{
  BgraphSegmtMap c_segment = getConnectedSegments( cgalSegmts.begin(), cgalSegmts.end());
  SegmentsSetIsClosed criteria;
  c_segments = filterMapOfSegmentsWithCriteria( c_segment, criteria);
  //std::cout << "Nbre de contours connectes:" << c_segments.size() << std::endl;
  
};
#endif
