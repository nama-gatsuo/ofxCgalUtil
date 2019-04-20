#pragma once
#include "Types.h"
#include "CGAL/polyhedron_cut_plane_3.h"
class CutByPlane {
public:
	Polyhedron operator() (const Polyhedron& p, const Kernel::Plane_3& plane) {
		Polyhedron result(p);

		CGAL::polyhedron_cut_plane_3(result, result.halfedges_begin(), plane);
		return result;
	}

};