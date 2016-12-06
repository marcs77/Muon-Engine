#ifndef MATHUTILS_H
#define MATHUTILS_H

#define PI 3.14159265359

#define TO_RAD(deg) deg * PI / 180.0
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)
#define CLAMP(val, min, max) MIN(MAX(val, min), max)
#define CLAMP01(val) CLAMP(val, 0, 1)
#define ABS(x) (x < 0 ? -x : x)

#endif // !MATHUTILS_H
