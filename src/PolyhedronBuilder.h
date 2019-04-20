#pragma once

#include "ofMesh.h"
#include <CGAL/Gmpz.h>
#include <CGAL/Homogeneous.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Nef_polyhedron_3.h>

static const int kPointScale = 100000;

template<class HDS>
class PolyhedronBuilder : public CGAL::Modifier_base<HDS> {
public:
	const ofMesh& mesh;

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
					int(v.x * kPointScale), int(v.y * kPointScale), int(v.z * kPointScale)
				);
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
			}
			else {
				ofLogError("unsupported primitve type");
			}
		}
		B.end_surface();

	}

private:
	
};