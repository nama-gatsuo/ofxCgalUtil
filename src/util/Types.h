#pragma once
#include "CGAL/Exact_predicates_inexact_constructions_kernel.h"
#include "CGAL/Exact_predicates_exact_constructions_kernel.h"
#include "CGAL/Polyhedron_3.h"

#include "CGAL/Exact_integer.h"
#include "CGAL/Homogeneous.h"
#include "CGAL/Nef_polyhedron_3.h"

using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
using Polyhedron = CGAL::Polyhedron_3<Kernel>;
using Point	= Kernel::Point_3;

//using Kernel_NT	= CGAL::Homogeneous<CGAL::Exact_integer>;
using Kernel_NT	= CGAL::Exact_predicates_exact_constructions_kernel;
using Polyhedron_NT = CGAL::Polyhedron_3<Kernel_NT>;
using Nef_Polyhedron = CGAL::Nef_polyhedron_3<Kernel_NT>;