// Copyright (c) 1997  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14-beta2/Polyhedron/include/CGAL/Polyhedron_copy_3.h $
// $Id: Polyhedron_copy_3.h ee57fc2 %aI Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>)

#ifndef CGAL_POLYHEDRON_COPY_3_H
#define CGAL_POLYHEDRON_COPY_3_H 1

#include <CGAL/license/Polyhedron.h>


#include <CGAL/basic.h>
#include <CGAL/Modifier_base.h>
#include <CGAL/Inverse_index.h>
#include <CGAL/Polyhedron_incremental_builder_3.h>
#include <CGAL/Cartesian_converter.h>
#include <CGAL/Kernel_traits.h>

namespace CGAL {

template < class Poly, class HDS, bool clear_target_before = true >
class Polyhedron_copy_3 : public Modifier_base<HDS> {
protected:
    const Poly& source;
public:
    typedef Poly Polyhedron;
    typedef HDS  Halfedge_data_structure;
    Polyhedron_copy_3( const Polyhedron& poly) : source(poly) {}
        // creates the copy modifier and stores the `source' in its
        // internal state.
    void operator()( HDS& target);
        // copies the `source' known from creation time into the `target'.
        // Postcondition: the `target' is a valid polyhedral surface.
};

template < class Poly, class HDS, bool clear_target_before>
void
Polyhedron_copy_3<Poly,HDS,clear_target_before>::operator()(HDS& target) {
    typedef typename Poly::Vertex_const_iterator  Vertex_const_iterator;
    typedef typename Poly::Facet_const_iterator   Facet_const_iterator;
    typedef Inverse_index< Vertex_const_iterator> Index;
  
    Cartesian_converter< 
      typename Kernel_traits<typename Poly::Vertex::Point>::Kernel,
      typename Kernel_traits<typename HDS::Vertex::Point>::Kernel
    > convert;

    if ( clear_target_before )
      target.clear();

    Polyhedron_incremental_builder_3<HDS> B( target);
    B.begin_surface( source.size_of_vertices(),
                     source.size_of_facets(),
                     source.size_of_halfedges());
    for ( Vertex_const_iterator vi = source.vertices_begin();
          vi != source.vertices_end();
          ++vi) {
        B.add_vertex( convert( vi->point()));
    }
    Index index( source.vertices_begin(), source.vertices_end());

    for ( Facet_const_iterator fi = source.facets_begin();
          fi != source.facets_end();
          ++fi) {
        B.begin_facet();
        typedef typename Poly::Halfedge_around_facet_const_circulator
            Halfedge_around_facet_const_circulator;
        Halfedge_around_facet_const_circulator hc = fi->facet_begin();
        Halfedge_around_facet_const_circulator hc_end = hc;
        CGAL_assertion( hc != NULL);
        do {
            B.add_vertex_to_facet( index[ hc->vertex()]);
            ++hc;
        } while( hc != hc_end);
        B.end_facet();
    }
    B.end_surface();
    target.normalize_border();
}

} //namespace CGAL
#endif // CGAL_POLYHEDRON_COPY_3_H //
// EOF //
