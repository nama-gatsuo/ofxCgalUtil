#pragma once

#include "ofMesh.h"
#include <CGAL/Polyhedron_incremental_builder_3.h>

template<class HDS>
class PolyhedronBuilder : public CGAL::Modifier_base<HDS> {
public:

	PolyhedronBuilder(const ofMesh& mesh) : mesh(mesh) {}

	void operator()(HDS& hds) {
		CGAL::Polyhedron_incremental_builder_3<HDS> B(hds, true);

		const int nVertices = mesh.getNumVertices();
		const int nIndices = mesh.getNumIndices();
		const int nFaces = nIndices / 3;

		B.begin_surface(nVertices, nFaces);
		{
			using Vertex = HDS::Vertex;
			using Point = Vertex::Point;

			const auto& vertices = mesh.getVertices();
			for (auto& v : vertices) {
				B.add_vertex(Point(
					v.x, v.y, v.z * 100000)
				));
			}

			if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
				const auto& indices = mesh.getIndices();
				for (int i = 0; i < nIndices; i += 3) {
					B.begin_facet();
					B.add_vertex_to_facet(indices[i + 0]);
					B.add_vertex_to_facet(indices[i + 1]);
					B.add_vertex_to_facet(indices[i + 2]);
					B.end_facet();
				}
			} else {
				ofLogError("ofxCgalUtil") << "unsupported primitve type";
			}
		}
		B.end_surface();

	}
private:
	const ofMesh& mesh;
};

