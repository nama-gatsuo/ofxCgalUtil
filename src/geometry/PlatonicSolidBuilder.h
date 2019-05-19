#pragma once
#include "Types.h"
#include "ofMesh.h"
#include "ofGraphics.h"
#include "PolyhedronConverter.h"
namespace ofxCgalUtil {

	template<class HDS>
	class BoxBuilder : public CGAL::Modifier_base<HDS> {
	public:

		BoxBuilder() {}

		void operator()(HDS& hds) {
			using Vertex = HDS::Vertex;
			using Point = Vertex::Point;
			
			CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);

			float s = scalarForNef / 2.;

			const std::vector<Point> points{
				Point(-s, s, -s), Point(s, s, -s), Point(s, s, s), Point(-s, s, s),
				Point(-s, -s, -s), Point(-s, -s, s), Point(s, -s, s), Point(s, -s, -s)
			};

			const std::vector<std::vector<int>> indices{
				{ 0, 3, 2, 1 }, { 0, 1, 7, 4 },
				{ 1, 2, 6, 7 }, { 2, 3, 5, 6 },
				{ 3, 0, 4, 5 }, { 4, 7, 6, 5 }
			};

			builder.begin_surface(points.size(), indices.size());
			for (auto& p : points) {
				builder.add_vertex(p);
			}
			for (auto& f : indices) {
				builder.begin_facet();
				for (auto& i : f) {
					builder.add_vertex_to_facet(i);
				}
				builder.end_facet();
			}
			builder.end_surface();

		}


	};

	class HalfedgeMesh {
	public:
		HalfedgeMesh() {
			BoxBuilder<Polyhedron<EPEC>::HalfedgeDS> builder;
			polyhedron.delegate(builder);
		}
		void updateMesh() {
			mesh = getMeshFromPoly(polyhedron);
		}
		void drawEdges() {
			for (auto it = polyhedron.halfedges_begin(); it != polyhedron.halfedges_end(); ++it) {
				auto p0 = it->vertex()->point();
				auto p1 = it->prev()->vertex()->point();
				glm::vec3 v0(CGAL::to_double(p0.x()), CGAL::to_double(p0.y()), CGAL::to_double(p0.z()));
				glm::vec3 v1(CGAL::to_double(p1.x()), CGAL::to_double(p1.y()), CGAL::to_double(p1.z()));
				v0 /= scalarForNef;
				v1 /= scalarForNef;
				ofDrawLine(v0, v1);
			}
		}

		Polyhedron<EPEC>& getPoly() { return polyhedron; }
		ofMesh& getMesh() { return mesh; }

	private:
		Polyhedron<EPEC> polyhedron;
		ofMesh mesh;
	};

};