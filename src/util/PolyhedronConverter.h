#pragma once
#include "PolyhedronBuilder.h"
#include "CGAL/Polyhedron_3.h"
#include "CGAL/Polygon_mesh_processing/merge_border_vertices.h"

namespace ofxCgalUtil {
	
	template<class K>
	static Polyhedron<K> getPolyFromMesh(const ofMesh& mesh) {
		Polyhedron<K> polyhedron;
		Mesh_to_polyhedron<typename Polyhedron<K>::HalfedgeDS> builder(mesh);
		polyhedron.delegate(builder);
		//CGAL::Polygon_mesh_processing::merge_duplicated_vertices_in_boundary_cycles(polyhedron);
		return polyhedron;
	}

	template<class K>
	static ofMesh getMeshFromPoly(const Polyhedron<K>& poly) {
		using P = K::Point_3;

		ofMesh mesh;
		std::map<P, int> pointIndices;
		int count = 0;

		for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it) {
			const P& p = it->point();
			float x = CGAL::to_double(p.x());
			float y = CGAL::to_double(p.y());
			float z = CGAL::to_double(p.z());

			mesh.addVertex(glm::vec3(x, y, z));
			pointIndices[p] = count++;
		}

		for (auto it = poly.facets_begin(); it != poly.facets_end(); ++it) {
			mesh.addIndex(pointIndices[it->halfedge()->vertex()->point()]);
			mesh.addIndex(pointIndices[it->halfedge()->next()->vertex()->point()]);
			mesh.addIndex(pointIndices[it->halfedge()->prev()->vertex()->point()]);
		}

		return mesh;
	}

	template <class K0, class K1>
	static Polyhedron<K1> poly_cast(const Polyhedron<K0>& poly_src) {
		Polyhedron<K1> poly_dst;
		Copy_polyhedron<K0, K1> modifier(poly_src);
		poly_dst.delegate(modifier);
		return poly_dst;
	}
	
	
};
