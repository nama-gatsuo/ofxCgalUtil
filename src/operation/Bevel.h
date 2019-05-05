#pragma once
#include "Types.h"
#include "CGAL/Polygon_mesh_processing/compute_normal.h"
#include "CGAL/polyhedron_cut_plane_3.h"
#include "CGAL/Polygon_mesh_processing/clip.h"
#include "CGAL/Polyhedron_3.h"


namespace ofxCgalUtil {
	
	namespace PMP = CGAL::Polygon_mesh_processing;
	
	template<class K>
	static void bevelEdge(Polyhedron<K>& p, typename Polyhedron<K>::Vertex_handle v, float dist) {
		
		K::Vector_3 normal = PMP::compute_vertex_normal(v, p);
		K::Point_3 start = v->point() + normal * K::FT(dist * scalarForNef);
		K::Plane_3 plane = K::Plane_3(start, - normal);
		
		if (!CGAL::Polygon_mesh_processing::does_self_intersect(p)) {
			PMP::clip(p, plane, PMP::parameters::clip_volume(true).use_compact_clipper(true));
		} else {
			ofLogWarning("ofxCgalUtil::bevelEdge") << "polygon has self intersection.";
		}
		
	}

	template<class K>
	static Polyhedron<K> bevelAllEdges(Polyhedron<K>& p, float dist) {
		Polyhedron<K> result(p);

		for (auto it = p.vertices_begin(); it != p.vertices_end(); ++it) {
			bevelEdge(result, it, dist);
		}
		
		return result;
	}

}
