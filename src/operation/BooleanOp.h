#pragma once
#include "Types.h"
#include "PolyhedronConverter.h"

namespace ofxCgalUtil {
	enum BoolOpType {
		BOOL_OP_UNION = 0,
		BOOL_OP_DIFFERENCE = 1,
		BOOL_OP_INTERSECTION = 2,
		BOOL_OP_COMPLEMENT = 3,
		BOOL_OP_SYMMETRIC_DIFFERENCE = 4
	};

	static NefPolyhedron booleanOperation(const NefPolyhedron& p0, const NefPolyhedron& p1, BoolOpType type) {
		NefPolyhedron result;

		switch (type) {
		case BOOL_OP_UNION: result = p0 + p1; break;
		case BOOL_OP_DIFFERENCE: result = p0 - p1; break;
		case BOOL_OP_INTERSECTION: result = p0 * p1; break;
		case BOOL_OP_COMPLEMENT: result = p0 * !p1; break;
		case BOOL_OP_SYMMETRIC_DIFFERENCE: result = p0 ^ p1; break;
		default: break;
		}

		return result;
	}

	static ofMesh booleanOperation(const ofMesh& mesh0, const ofMesh& mesh1, BoolOpType type) {
		NefPolyhedron result(booleanOperation(getPolyFromMesh<EPEC>(mesh0), getPolyFromMesh<EPEC>(mesh1), type));
		
		Polyhedron<EPEC> poly;
		result.convert_to_polyhedron(poly);

		return getMeshFromPoly(poly);
	}

}
