#pragma once

#include "ofMesh.h"
#include "Types.h"
#include <CGAL/Polyhedron_incremental_builder_3.h>

namespace ofxCgalUtil {

	const static int scalarForNef = 1e5;

	template<class HDS>
	class Mesh_to_polyhedron : public CGAL::Modifier_base<HDS> {
	public:

		Mesh_to_polyhedron(const ofMesh& mesh) : mesh(mesh) {}

		void operator()(HDS& hds) {
			CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);

			const int nVertices = mesh.getNumVertices();
			const int nIndices = mesh.getNumIndices();
			const int nFaces = nIndices / 3;

			builder.begin_surface(nVertices, nFaces);
			{
				using Vertex = HDS::Vertex;
				using Point = Vertex::Point;

				const auto& vertices = mesh.getVertices();
				for (auto& v : vertices) {
					builder.add_vertex(Point(
						int(v.x * scalarForNef), int(v.y * scalarForNef), int(v.z * scalarForNef)
					));
				}

				if (mesh.getMode() == OF_PRIMITIVE_TRIANGLES) {
					const auto& indices = mesh.getIndices();
					for (int i = 0; i < nIndices; i += 3) {
						builder.begin_facet();
						builder.add_vertex_to_facet(indices[i + 0]);
						builder.add_vertex_to_facet(indices[i + 1]);
						builder.add_vertex_to_facet(indices[i + 2]);
						builder.end_facet();
					}
				} else {
					ofLogError("ofxCgalUtil") << "unsupported primitve type";
				}
			}
			builder.end_surface();

		}
	private:
		const ofMesh& mesh;
	};

	// Can be used to convert polyhedron from exact to inexact and vice-versa 
	template <class K0, class K1>
	class Copy_polyhedron : public CGAL::Modifier_base<typename Polyhedron<K1>::HalfedgeDS> {
	public:

		Copy_polyhedron(const Polyhedron<K0>& in_poly) : in_poly(in_poly) {}

		void operator()(typename Polyhedron<K1>::HalfedgeDS& out_hds) {
			using Output_HDS = Polyhedron<K1>::HalfedgeDS;
			using Input_HDS = Polyhedron<K0>::HalfedgeDS;

			CGAL::Polyhedron_incremental_builder_3<Output_HDS> builder(out_hds);

			using Vertex_const_iterator = Polyhedron<K0>::Vertex_const_iterator;
			using Facet_const_iterator = Polyhedron<K0>::Facet_const_iterator;
			using HFCC = Polyhedron<K0>::Halfedge_around_facet_const_circulator;
			using Index = CGAL::Inverse_index<Vertex_const_iterator>;

			builder.begin_surface(in_poly.size_of_vertices(), in_poly.size_of_facets(), in_poly.size_of_halfedges());

			// create vertex
			for (auto vi = in_poly.vertices_begin(); vi != in_poly.vertices_end(); ++vi) {
				Polyhedron<K1>::Point_3 p(
					CGAL::to_double(vi->point().x()),
					CGAL::to_double(vi->point().y()),
					CGAL::to_double(vi->point().z())
				);

				builder.add_vertex(p);
			}

			Index index(in_poly.vertices_begin(), in_poly.vertices_end());

			// create facets
			for (auto fi = in_poly.facets_begin(); fi != in_poly.facets_end(); ++fi)
			{
				HFCC hc = fi->facet_begin();
				HFCC hc_end = hc;
				builder.begin_facet();
				do {
					builder.add_vertex_to_facet(index[hc->vertex()]);
					++hc;
				} while (hc != hc_end);
				builder.end_facet();
			}
			builder.end_surface();
		} 
	private:
		const Polyhedron<K0>& in_poly;
	};
}

