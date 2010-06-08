#ifndef _ERCV_CONSTRAINED_TRIANGULATION_2_HPP_
#define _ERCV_CONSTRAINED_TRIANGULATION_2_HPP_

#include<erCv/geometry/erCgalBase.hpp>
// Recopier direct de CGAL demo/Triangulation_2/Constrained_Triangulation_2.cpp

#include <CGAL/Constrained_triangulation_2.h>



typedef K::Iso_rectangle_2 Iso_rectangle_2;
typedef CGAL::Triangulation_vertex_base_2<K>  Vertex_base;
typedef CGAL::Constrained_triangulation_face_base_2<K> Face_base;

template <class Gt,
          class Fb >
class Enriched_face_base_2 : public Fb {
public:
  typedef Gt Geom_traits;
  typedef typename Fb::Vertex_handle Vertex_handle;
  typedef typename Fb::Face_handle Face_handle;

  template < typename TDS2 >
  struct Rebind_TDS {
    typedef typename Fb::template Rebind_TDS<TDS2>::Other Fb2;
    typedef Enriched_face_base_2<Gt,Fb2> Other;
  };

protected:
  int status;

public:
  Enriched_face_base_2(): Fb(), status(-1) {};

  Enriched_face_base_2(Vertex_handle v0, 
		       Vertex_handle v1, 
		       Vertex_handle v2)
    : Fb(v0,v1,v2), status(-1) {};

  Enriched_face_base_2(Vertex_handle v0, 
		       Vertex_handle v1, 
		       Vertex_handle v2,
		       Face_handle n0, 
		       Face_handle n1, 
		       Face_handle n2)
    : Fb(v0,v1,v2,n0,n1,n2), status(-1) {};

  inline
  bool is_in_domain() const { return (status%2 == 1); };

  inline
  void set_in_domain(const bool b) { status = (b ? 1 : 0); };

  inline 
  void set_counter(int i) { status = i; };

  inline 
  int counter() const { return status; };

  inline 
  int& counter() { return status; };
}; // end class Enriched_face_base_2

typedef Enriched_face_base_2<K, Face_base> Fc;
typedef CGAL::Triangulation_data_structure_2<Vertex_base, Fc>  TDS;
typedef CGAL::Exact_predicates_tag              Itag;
typedef CGAL::Constrained_triangulation_2<K, TDS, Itag> CDT;

typedef CDT::Vertex_handle Vertex_handle;
typedef CDT::Face_handle Face_handle;
typedef CDT::All_faces_iterator All_faces_iterator;


void
initializeID(const CDT& ct)
{
  for(All_faces_iterator it = ct.all_faces_begin(); it != ct.all_faces_end(); ++it){
    it->set_counter(-1);
  }
}
void 
discoverComponent(const CDT & ct, 
		  Face_handle start, 
		  int index, 
		  std::list<CDT::Edge>& border )
{
  if(start->counter() != -1){
    return;
  }
  std::list<Face_handle> queue;
  queue.push_back(start);

  while(! queue.empty()){
    Face_handle fh = queue.front();
    queue.pop_front();
    if(fh->counter() == -1){
      fh->counter() = index;
      fh->set_in_domain(index%2 == 1);
      for(int i = 0; i < 3; i++){
	CDT::Edge e(fh,i);
	Face_handle n = fh->neighbor(i);
	if(n->counter() == -1){
	  if(ct.is_constrained(e)){
	    border.push_back(e);
	  } else {
	    queue.push_back(n);
	  }
	}
	
      }
    }
  }
}

void 
discoverComponents(const CDT & ct)
{
  int index = 0;
  std::list<CDT::Edge> border;
  discoverComponent(ct, ct.infinite_face(), index++, border);
  while(! border.empty()){
    CDT::Edge e = border.front();
    border.pop_front();
    Face_handle n = e.first->neighbor(e.second);
    if(n->counter() == -1){
      discoverComponent(ct, n, e.first->counter()+1, border);
    }
  }
} 



#endif
