#pragma once
#include "PolyhedronBuilder.h"
#include "CGAL/Polyhedron_3.h"

namespace Converter {

	template<class Kernel>
	static CGAL::Polyhedron_3<Kernel> mesh_to_poly(const ofMesh& mesh) {
		CGAL::Polyhedron_3<Kernel> polyhedron;
		Mesh_to_polyhedron<CGAL::Polyhedron_3<Kernel>::HalfedgeDS> builder(mesh);
		polyhedron.delegate(builder);
		return polyhedron;
	}

	template<class Kernel>
	static ofMesh poly_to_mesh(const CGAL::Polyhedron_3<Kernel>& poly) {
		using P = Kernel::Point_3;

		ofMesh mesh;
		std::map<P, int> pointIndices;
		int count = 0;

		for (auto it = poly.vertices_begin(); it != poly.vertices_end(); ++it) {
			P& p = it->point();
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

	template <class Poly_dst, class Poly_src>
	static Poly_dst poly_cast(const Poly_src& poly_a) {
		Poly_dst p;
		Copy_polyhedron<Poly_src, Poly_dst> modifier(poly_a);
		p.delegate(modifier);
		return p;
	}


};
