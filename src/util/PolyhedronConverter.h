#pragma once
#include "PolyhedronBuilder.h"
#include "CGAL/Polyhedron_3.h"
#include "CGAL/Polygon_mesh_processing/merge_border_vertices.h"

namespace ofxCgalUtil {
	
	// convert mesh -> polyhedron
	template<class K>
	static Polyhedron<K> getPolyFromMesh(const ofMesh& mesh) {
		Polyhedron<K> polyhedron;
		Mesh_to_polyhedron<typename Polyhedron<K>::HalfedgeDS> builder(mesh);
		polyhedron.delegate(builder);
		// CGAL::Polygon_mesh_processing::merge_duplicated_vertices_in_boundary_cycles(polyhedron);
		return polyhedron;
	}

	// convert polyhedron -> mesh
	template<class K>
	static ofMesh getMeshFromPoly(const Polyhedron<K>& poly) {
		using P = K::Point_3;
		
		ofMesh mesh;
		std::map<P, int> pointIndices;
		int count = 0;

		for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it) {
			const P& p = it->point();
			mesh.addVertex(toVec(p));
			pointIndices[p] = count++;
		}

		for (auto it = poly.facets_begin(); it != poly.facets_end(); ++it) {
			int triNum = it->size() - 2;
			int count = 0;
			auto start = it->halfedge()->prev();
			auto he = start->next();
			// triangulate by fan
			do {
				mesh.addIndex(pointIndices[start->vertex()->point()]);
				mesh.addIndex(pointIndices[he->vertex()->point()]);
				mesh.addIndex(pointIndices[he->next()->vertex()->point()]);
				he = he->next();
				count++;
			} while (count < triNum);
		}

		return mesh;
	}
	
	// convert mesh -> nef polyhedron
	static NefPolyhedron getNefPolyFromMesh(const ofMesh& mesh) {
		return getPolyFromMesh<HEI>(mesh);
	}

	// convert nef polyhedron -> mesh
	static ofMesh getMeshFromNefPoly(const NefPolyhedron& np) {
		Polyhedron<HEI> poly;
		np.convert_to_polyhedron(poly);
		return getMeshFromPoly(poly);
	}

	// convert polyhedron to polyhedron of different kernel
	template <class K0, class K1>
	static Polyhedron<K1> poly_cast(const Polyhedron<K0>& poly_src) {
		Polyhedron<K1> poly_dst;
		Copy_polyhedron<K0, K1> modifier(poly_src);
		poly_dst.delegate(modifier);
		return poly_dst;
	}
	
	
};
