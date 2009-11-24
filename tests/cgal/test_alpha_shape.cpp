#include <erCv/erCv.hpp>
#include <erCv/erCvFilters.hpp>
#include <erCv/utilities/erPredicates.hpp>
#include <erCv/erCvExtract.hpp>
#include <erCv/erCvToCgal.hpp>
#include <erCv/geometry/erCgalAlphaShape2.hpp>
#include<list>
#include<fstream>
#include<iterator>
#include<boost/utility.hpp>
//std::string INFOFILE;

int main(int HOLA, char** file_name){
  /* Chargement et visualisation de l image de base */
 
//   /* Ecriture des points extraits dans le fichier 'points_cv_filters_cv.dat' */
//   /* Definition du conteneur de points CGAL */
   std::list<Point_2> cgalPts;
   std::ifstream in("peo12_data_009603.txt");
   double x,y;
   while(!in.eof())
     {
       in >> x >> y;
       Point_2 p(x,y);
       cgalPts.push_back(p);
     }
//   /* Construction de l alpha shape a partir des points CGAL */
   Alpha_shape_2 as2(cgalPts.begin(),cgalPts.end(),FT(30.));
   std::list<Segment_2> segments;
   alpha_edges( as2, std::back_inserter(segments));
//   /* Ecriture des cotes dans le fichier "edges_cv_filters.dat" */
   std::ofstream ot("results/edges_cv_filters.dat");
   std::list<Segment_2>::iterator  is;
   for(is=segments.begin();is!=segments.end();is++)
     {
       ot << *is << std::endl;
     };

  return 0;
};
