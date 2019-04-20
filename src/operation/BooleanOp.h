#pragma once
#include "Types.h"
#include "ofLog.h"

class BoolOp {
public:
	enum BoolOpType {
		BOOL_OP_UNION = 0,
		BOOL_OP_DIFFERENCE = 1,
		BOOL_OP_INTERSECTION = 2,
		BOOL_OP_COMPLEMENT = 3,
		BOOL_OP_SYMMETRIC_DIFFERENCE = 4
	};

	Nef_Polyhedron run(const Nef_Polyhedron& p0, const Nef_Polyhedron& p1, BoolOpType type) {

		Nef_Polyhedron result;

		switch (type) {
		case BoolOp::BOOL_OP_UNION: result = p0 + p1; break;
		case BoolOp::BOOL_OP_DIFFERENCE: result = p0 - p1; break;
		case BoolOp::BOOL_OP_INTERSECTION: result = p0 * p1; break;
		case BoolOp::BOOL_OP_COMPLEMENT: result = p0 *! p1; break;
		case BoolOp::BOOL_OP_SYMMETRIC_DIFFERENCE: result = p0 ^ p1; break;
		default: break;
		}

		return result;
	}


private:


};
