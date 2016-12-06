#include "quaternion.h"

namespace muon {
namespace math {

Quaternion::Quaternion() : x(0), y(0), z(0), w(0) {}
Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
Quaternion::Quaternion(const Vec4f &v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
Quaternion::Quaternion(const Quaternion &q) : x(q.x), y(q.y), z(q.z), w(q.w) {}

Quaternion Quaternion::operator +(const Quaternion &q) const {
    return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w);
}

Quaternion& Quaternion::operator +=(const Quaternion &q) {
    x += q.x;
    y += q.y;
    z += q.z;
    w += q.w;
	return *this;
}

Quaternion Quaternion::operator -(const Quaternion &q) const {
    return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w);
}

Quaternion& Quaternion::operator -=(const Quaternion &q) {
    x -= q.x;
    y -= q.y;
    z -= q.z;
    w -= q.w;
	return *this;
}


}
}
