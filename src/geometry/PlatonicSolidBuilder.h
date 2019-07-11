#pragma once
#include "Types.h"
#include "ofMesh.h"
#include "ofGraphics.h"
#include "PolyhedronConverter.h"
namespace ofxCgalUtil {

	struct PolyhedronData {
		enum Type {
			TETRAHEDRON = 0, BOX, OCTAHEDRON, DODECAHEDRON, ICOSAHEDRON
		};
		std::vector<std::vector<int>> indices;
		std::vector<std::vector<float>> points;
	};

	namespace D {
		const float T = (1. + std::sqrt(5.)) * 0.5;
		const float R = 1. / T;
	}

	const static std::vector<PolyhedronData> polyData{
		{
			{
				{2, 1, 0}, {0, 3, 2}, {1, 3, 0}, {2, 3, 1}
			},
			{
				{1, 1, 1}, {-1, -1, 1}, {-1, 1, -1}, {1, -1, -1}
			}
		},
		{
			{
				{ 0, 3, 2, 1 }, { 0, 1, 7, 4 },
				{ 1, 2, 6, 7 }, { 2, 3, 5, 6 },
				{ 3, 0, 4, 5 }, { 4, 7, 6, 5 }
			},
			{
				{ -1, 1, -1 }, { 1, 1, -1 }, { 1, 1, 1 }, { -1, 1, 1 },
				{-1, -1, -1 }, { -1, -1, 1 }, { 1, -1, 1 }, { 1, -1, -1 }
			}
		},
		{
			{
				{0, 2, 4},	{0, 4, 3},	{0, 3, 5},
				{0, 5, 2},	{1, 2, 5},	{1, 5, 3},
				{1, 3, 4},	{1, 4, 2}
			},
			{
				{1, 0, 0 }, {-1, 0, 0},	{0, 1, 0 },
				{0, -1, 0}, {0, 0, 1 },	{0, 0, -1}
			}
		},
		{
			{
				{ 3, 11, 7, 15, 13 }, { 7, 19, 17, 6, 15 },
				{ 17, 4, 8, 10, 6 }, { 8, 0, 16, 2, 10 },
				{ 0, 12, 1, 18, 16 }, { 6, 10, 2, 13, 15 },
				{ 2, 16, 18, 3, 13 }, { 18, 1, 9, 11, 3 },
				{ 4, 14, 12, 0, 8 }, { 11, 9, 5, 19, 7 },
				{ 19, 5, 14, 4, 17 }, { 1, 12, 14, 5, 9 }
			},
			{
				{ -1, -1, -1}, { -1, -1, 1 }, { -1, 1, -1}, {-1, 1, 1},
				{ 1, -1, -1}, { 1, -1, 1}, { 1, 1, -1}, { 1, 1, 1},
				{ 0, -D::R, -D::T}, {0, -D::R, D::T}, { 0, D::R, -D::T }, { 0, D::R, D::T },
				{ -D::R, -D::T, 0}, {-D::R, D::T, 0}, { D::R, -D::T, 0},  { D::R, D::T, 0},
				{ -D::T, 0, -D::R}, { D::T, 0, -D::R}, { -D::T, 0, D::R}, {D::T, 0, D::R}
			}
		},
		{
			{
				{0, 11, 5}, {0, 5, 1}, 	{0, 1, 7}, 	{0, 7, 10}, {0, 10, 11},
				{ 1, 5, 9}, {5, 11, 4},	{11, 10, 2},{10, 7, 6},	{7, 1, 8},
				{ 3, 9, 4}, {3, 4, 2},	{3, 2, 6},	{3, 6, 8},	{3, 8, 9},
				{ 4, 9, 5}, {2, 4, 11},	{6, 2, 10},	{8, 6, 7},	{9, 8, 1}
			},
			{
				{-1, D::T, 0}, {1, D::T, 0}, {-1, -D::T, 0}, {1, -D::T, 0},
				{0, -1, D::T}, {0, 1, D::T}, {0, -1, -D::T}, {0, 1, -D::T},
				{D::T, 0, -1}, {D::T, 0, 1}, {-D::T, 0, -1}, {-D::T, 0, 1}
			}
		}
		
	};

	template<class HDS>
	class PlatonicSolidBuilder : public CGAL::Modifier_base<HDS> {
	public:
		PlatonicSolidBuilder(PolyhedronData::Type type, float size) : 
			size(size), points(polyData[type].points), indices(polyData[type].indices)
		{}

		void operator()(HDS& hds) {
			using Vertex = HDS::Vertex;
			using Point = Vertex::Point;
			
			CGAL::Polyhedron_incremental_builder_3<HDS> builder(hds, true);
			float s = size * scalarForNef / 2.;

			builder.begin_surface(points.size(), indices.size());
			for (auto& p : points) {
				builder.add_vertex(Point(p[0] * s, p[1] * s, p[2] * s));
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

	private:
		const float size;
		const std::vector<std::vector<float>> points;
		const std::vector<std::vector<int>> indices;
	};

	template<class K>
	Polyhedron<K> getPlatonicSolid(PolyhedronData::Type type, float size) {
		Polyhedron<K> poly;
		PlatonicSolidBuilder<Polyhedron<K>::HalfedgeDS> builder(type, size);
		poly.delegate(builder);
		return poly;
	}

};