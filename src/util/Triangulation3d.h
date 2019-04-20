#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include "ofVectorMath.h"


class Triangulation3d {
public:
	static std::vector<std::vector<glm::vec3>> getTetras(const std::vector<glm::vec3>& points) {
		
		using Triangulation = CGAL::Triangulation_3<CGAL::Exact_predicates_inexact_constructions_kernel>;
		using CellHandle = Triangulation::Cell_handle;
		using VertexHandle = Triangulation::Vertex_handle;
		using LocateType = Triangulation::Locate_type;
		using P = Triangulation::Point;
		
		std::vector<P> ps;
		for (auto& p : points) {
			ps.push_back(P(p.x, p.y, p.z));
		}
		
		Triangulation triangulation(ps.begin(), ps.end());

		Triangulation::size_type n = triangulation.number_of_vertices();
		if (triangulation.is_valid()) {
			ofLogError("ofxCgalUtil") << "tr";
		}

		std::vector<std::vector<glm::vec3>> result(n, std::vector<glm::vec3>(4));

		int ti = 0;
		for (
			auto cell = triangulation.finite_cells_begin();
			cell != triangulation.finite_cells_end(); ++cell
			) {

			for (int i = 0; i < 4; i++) {
				P p = cell->vertex(i)->point();
				
				result[ti][i] = glm::vec3(p.x(), p.y(), p.z());
			}
			ti++;
		
		}
		
		return result;

	}

};