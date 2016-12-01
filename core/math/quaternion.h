#ifndef QUATERNION_H
#define QUATERNION_H
#include "vec4.h"

namespace muon {
namespace math {

    struct Quaternion {
        float x, y, z, w;

        Quaternion();
        Quaternion(const Vec4f& v);
        Quaternion(const Quaternion& v);
        Quaternion(float x, float y, float z, float w);

        Quaternion operator+(const Quaternion &q) const;
        Quaternion& operator+=(const Quaternion &q);

        Quaternion operator-(const Quaternion &q) const;
        Quaternion& operator-=(const Quaternion &q);

        inline std::string toString() { return "Quat("+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+","+std::to_string(w)+")"; }

    };

}
}

#endif // QUATERNION_H
