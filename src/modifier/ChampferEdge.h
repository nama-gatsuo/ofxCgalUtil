#pragma once
#include "Types.h"
#include "CGAL/Polyhedron_3.h"

class ChampferEdge {
public:
	
	Polyhedron operator()(Polyhedron& polyhedron) {
		
		for (auto he = polyhedron.halfedges_begin(); he != polyhedron.halfedges_end(); ++he) {
			
			bool isConvex = true;
			
			
		}

	}

};