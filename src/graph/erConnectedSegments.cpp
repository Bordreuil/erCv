
#include <erCv/graph/erConnectedSegments.hpp>

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
