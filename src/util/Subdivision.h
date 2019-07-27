#pragma once
#include "CGAL/subdivision_method_3.h"
#include "Types.h"
namespace ofxCgalUtil {

	enum SubdivisionType { CATMULL_CLARK, DOOSABIN, SQRT3 };

	template<class K>
	static void subdivide(Polyhedron<K>& poly, SubdivisionType type, int depth) {
		switch (type) {
		case ofxCgalUtil::CATMULL_CLARK:
			CGAL::Subdivision_method_3::CatmullClark_subdivision(poly, CGAL::parameters::number_of_iterations(depth));
			break;
		case ofxCgalUtil::DOOSABIN:
			CGAL::Subdivision_method_3::DooSabin_subdivision(poly, CGAL::parameters::number_of_iterations(depth));
			break;
		case ofxCgalUtil::SQRT3:
			CGAL::Subdivision_method_3::Sqrt3_subdivision(poly, CGAL::parameters::number_of_iterations(depth));
			break;
		default:
			break;
		}
	}

};

