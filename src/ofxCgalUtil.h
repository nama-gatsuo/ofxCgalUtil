#pragma once

#ifdef PI
#undef PI
#endif

#include "Types.h"
#include "PolyhedronConverter.h"
#include "Triangulation3d.h"
#include "operation/CutByPlane.h"
#include "operation/BooleanOp.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif