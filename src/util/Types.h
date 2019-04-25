#pragma once
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
#include "CGAL/Polyhedron_3.h"
#include "CGAL/Nef_polyhedron_3.h"

namespace ofxCgalUtil {
	using EPIC = CGAL::Exact_predicates_inexact_constructions_kernel;
	using EPEC = CGAL::Exact_predicates_exact_constructions_kernel;

	template<class K>
	using Polyhedron = CGAL::Polyhedron_3<K>;
	
	using NefPolyhedron = CGAL::Nef_polyhedron_3<EPEC>;
}

