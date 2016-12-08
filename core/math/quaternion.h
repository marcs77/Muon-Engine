#ifndef QUATERNION_H
#define QUATERNION_H
#include "vec4.h"

namespace muon {
namespace math {

    struct Quaternion {
        float w, x, y, z;

        Quaternion();
        Quaternion(const Vec4f& v);
        Quaternion(const Quaternion& v);
        Quaternion(float w, float x, float y, float z);

        Quaternion operator+(const Quaternion &q) const;
        Quaternion& operator+=(const Quaternion &q);

        Quaternion operator-(const Quaternion &q) const;
        Quaternion& operator-=(const Quaternion &q);

        Quaternion operator*(const Quaternion &q) const;

        inline std::string toString() { return "Quat("+std::to_string(w)+","+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+")"; }

    };

}
}

#endif // QUATERNION_H
