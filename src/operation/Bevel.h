#pragma once
#include "Types.h"
#include "CGAL/Polygon_mesh_processing/compute_normal.h"
//#include "CGAL/polyhedron_cut_plane_3.h"
#include "CGAL/Polygon_mesh_processing/clip.h"
//#include "CGAL/Polyhedron_3.h"
#include "CGAL/number_utils.h"

namespace ofxCgalUtil {
	
	template<class K>
	typename K::Vector_3 getFacetNormal(typename Polyhedron<K>::Facet facet) {

		auto e = facet.halfedge();

		auto p0 = e->vertex()->point();
		auto p1 = e->next()->vertex()->point();
		auto p2 = e->next()->next()->vertex()->point();

		return CGAL::cross_product(p1 - p0, p2 - p0);
	}

	template<class V>
	typename V getNormalized(V v) {
		glm::vec3 n = glm::normalize(glm::vec3(CGAL::to_double(v.x()), CGAL::to_double(v.y()), CGAL::to_double(v.z())));
		return V(n.x, n.y, n.z);
	}

	namespace PMP = CGAL::Polygon_mesh_processing;

	template<class K>
	static void bevelVertex(Polyhedron<K>& p, typename Polyhedron<K>::Vertex& v, float dist) {

		K::Vector_3 normal = PMP::compute_vertex_normal(v, p);

		K::Point_3 start = v->point() - normal * K::FT(dist * scalarForNef);
		K::Plane_3 plane = K::Plane_3(start, - normal);

		if (!CGAL::Polygon_mesh_processing::does_self_intersect(p)) {
			PMP::clip(p, plane, PMP::parameters::clip_volume(true).use_compact_clipper(true));
		} else {
			ofLogWarning("ofxCgalUtil::bevelEdge") << "polygon has self intersection.";
		}

	}

	template<class K>
	static Polyhedron<K> bevelAllVertices(Polyhedron<K>& p, float dist, bool isRegularPolyhedron = false) {
		Polyhedron<K> result(p);

		for (auto it = p.vertices_begin(); it != p.vertices_end(); ++it) {
			K::Vector_3 normal;
			if (isRegularPolyhedron) {
				auto n = getNormalized(it->point());
				normal = K::Vector_3(n.x(), n.y(), n.z());
			} else {
				normal = PMP::compute_vertex_normal(it, p);
			}

			K::Point_3 start = it->point() - normal * K::FT(dist * scalarForNef);
			K::Plane_3 plane = K::Plane_3(start, normal);

			if (!CGAL::Polygon_mesh_processing::does_self_intersect(result)) {
				PMP::clip(result, plane, PMP::parameters::clip_volume(true).use_compact_clipper(true));
			} else {
				ofLogWarning("ofxCgalUtil::bevelEdge") << "polygon has self intersection.";
			}
		}

		return result;
	}

	template<class K>
	static Polyhedron<K> bevelEdges(Polyhedron<K>& p, float dist) {

		Polyhedron<K> result(p);
		
		for (auto it = p.halfedges_begin(); it != p.halfedges_end(); ++it) {
			
			auto n0 = getNormalized(getFacetNormal<K>(*it->facet()));
			auto n1 = getNormalized(getFacetNormal<K>(*(it->opposite()->facet())));

			if (!CGAL::is_one(n0 * n1)) {
				K::Vector_3 n = (n0 + n1);
				K::Point_3 start = it->vertex()->point() - n * K::FT(dist * scalarForNef);	
				K::Plane_3 plane(start, n);
				
				PMP::clip(result, plane, PMP::parameters::clip_volume(true).use_compact_clipper(true));
			}
		}
		
		return result;
	}

}
