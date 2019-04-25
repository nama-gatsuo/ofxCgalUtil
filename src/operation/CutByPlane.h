#pragma once
#include "Types.h"
#include "CGAL/polyhedron_cut_plane_3.h"

namespace ofxCgalUtil {
	template<class K>
	Polyhedron<K> cutByPlane(const Polyhedron<K>& p, const typename K::Plane_3& plane) {
		Polyhedron<K> result(p);
		CGAL::polyhedron_cut_plane_3(result, result.halfedges_begin(), plane);
		return result;
	}
}