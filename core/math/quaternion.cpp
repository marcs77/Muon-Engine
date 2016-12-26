#include "quaternion.h"

namespace muon {
namespace math {

Quaternion::Quaternion() : w(0), x(0), y(0), z(0) {}
Quaternion::Quaternion(float w, float x, float y, float z) :  w(w), x(x), y(y), z(z) {}
Quaternion::Quaternion(const Vec4f &v) : w(v.w), x(v.x), y(v.y), z(v.z) {}
Quaternion::Quaternion(const Quaternion &q) : w(q.w), x(q.x), y(q.y), z(q.z) {}
Quaternion::Quaternion(const Vec3f& axis, float angle)
{
    float half = angle*0.5f;
    float sin = sinf(half);
    w = cosf(half);
    x = axis.x * sin;
    y = axis.y * sin;
    z = axis.z * sin;
}

Quaternion Quaternion::operator +(const Quaternion &q) const {
    return Quaternion(w+q.w, x+q.x, y+q.y, z+q.z);
}

Quaternion& Quaternion::operator +=(const Quaternion &q) {
    w += q.w;
    x += q.x;
    y += q.y;
    z += q.z;
	return *this;
}

Quaternion Quaternion::operator -(const Quaternion &q) const {
    return Quaternion(w-q.w, x-q.x, y-q.y, z-q.z);
}

Quaternion& Quaternion::operator -=(const Quaternion &q) {
    w -= q.w;
    x -= q.x;
    y -= q.y;
    z -= q.z;
    return *this;
}

Quaternion Quaternion::operator*(const Quaternion &q) const
{
    return Quaternion
    (
        q.w*w - q.x*x - q.y*y - q.z*z,
        q.w*x + q.x*w - q.y*z + q.z*y,
        q.w*y + q.x*z + q.y*w - q.z*x,
        q.w*z - q.x*y + q.y*x + q.z*w
    );
}


}
}
