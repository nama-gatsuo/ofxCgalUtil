// Copyright (c) 2006  GeometryFactory (France). All rights reserved.
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
// $URL: https://github.com/CGAL/cgal/blob/releases/CGAL-4.14-beta2/Surface_mesh_simplification/include/CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Count_ratio_stop_predicate.h $
// $Id: Count_ratio_stop_predicate.h f2b1e70 %aI Sébastien Loriot
// SPDX-License-Identifier: GPL-3.0+
//
// Author(s)     : Fernando Cacciola <fernando.cacciola@geometryfactory.com>
//
#ifndef CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H
#define CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H 1

#include <CGAL/license/Surface_mesh_simplification.h>


#include <CGAL/Surface_mesh_simplification/Detail/Common.h>
#include <CGAL/Surface_mesh_simplification/Policies/Edge_collapse/Edge_profile.h>

namespace CGAL {

namespace Surface_mesh_simplification 
{

//*******************************************************************************************************************
//                                -= stopping condition predicate =-
//
// Determines whether the simplification has finished.
// The arguments are (current_cost,vertex,vertex,is_edge,initial_pair_count,current_pair_count,surface) and the result is bool
//
//*******************************************************************************************************************

// 
// Stops when the ratio of initial to current vertex pairs is below some value.
//
template<class TM_>    
class Count_ratio_stop_predicate
{
public:

  typedef TM_ TM ;
  
  typedef Edge_profile<TM> Profile ;
  
  typedef typename boost::graph_traits<TM>::edge_descriptor edge_descriptor ;
  typedef typename boost::graph_traits<TM>::edges_size_type size_type ;
    
  Count_ratio_stop_predicate( double aRatio ) : mRatio(aRatio) {}
  
  template <typename F> 
  bool operator()( F const&       // aCurrentCost
                 , Profile const& // aEdgeProfile
                 , size_type         aInitialCount
                 , size_type         aCurrentCount
                 ) const 
  {
    return ( static_cast<double>(aCurrentCount) / static_cast<double>(aInitialCount) ) < mRatio ;
  }
  
private:
  
  double mRatio ;
};    

} // namespace Surface_mesh_simplification

} //namespace CGAL

#endif // CGAL_SURFACE_MESH_SIMPLIFICATION_POLICIES_EDGE_COLLAPSE_COUNT_RATIO_STOP_PREDICATE_H //
// EOF //
 
