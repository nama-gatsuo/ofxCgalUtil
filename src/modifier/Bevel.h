#pragma once
#include "Types.h"
#include "CGAL/Polygon_mesh_processing/compute_normal.h"
#include "CGAL/polyhedron_cut_plane_3.h"
#include "CGAL/Polyhedron_3.h"

namespace ofxCgalUtil {
	
	template<class K>
	static void bevelEdge(Polyhedron<K>& p, Polyhedron<K>::Vertex_handle v, float dist) {

		
		K::Vector_3 normal = CGAL::Polygon_mesh_processing::compute_vertex_normal(v, p);
		K::Point_3 start = v->point() - normal * dist;

		K::Plane_3 plane = K::Plane_3(start, normal);
		CGAL::polyhedron_cut_plane_3(p, p.halfedges_begin(), plane);
	}




	
}
