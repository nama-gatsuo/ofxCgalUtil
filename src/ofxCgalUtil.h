#pragma once

#ifdef PI
#undef PI
#endif

#include "util/Types.h"
#include "util/Utilities.h"
#include "util/PolyhedronConverter.h"
#include "util/Triangulation3d.h"
#include "operation/BooleanOp.h"
#include "operation/Bevel.h"
#include "PlatonicSolidBuilder.h"

#ifndef PI
#define PI 3.14159265358979323846
#endif