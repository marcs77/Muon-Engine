#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"
#include "vec4.h"
#include <ostream>

/* MATRIX */
// [ 0	4	8	12 ]
// [ 1	5	9	13 ]
// [ 2	6	10	14 ]
// [ 3	7	11	15 ]

// m[y+x*4]

//row major

namespace muon {
	namespace math {
		struct Mat4 {

			union {
				float m[4 * 4];
				struct 
				{
					Vec4f columns[4];
				};
			};

			

			Mat4();
			Mat4(const Mat4& other);
			Mat4(float diagonal);

			float* getP(int x, int y);
			float get(int x, int y) const;

			void setIdentity();
			void multiply(const Mat4& right);

			Mat4 operator*(const Mat4& right) const;
			friend Vec3f operator*(const Mat4 &m, const Vec3f& v);
			friend Vec4f operator*(const Mat4 &m, const Vec4f& v);
			Mat4& operator*=(const Mat4& right);

			void translate(const Vec3f& v);
			void setTranslation(const Vec3f& v);

			void print(std::ostream& stream);

			static Mat4 identity();
			static Mat4 ortho(float left, float right, float bot, float top, float near, float far);
			static Mat4 perspective(float fov, float aspectRatio, float near, float far);

			static Mat4 multiply(const Mat4& l, const Mat4& r);

			static Mat4 translation(const Vec3f& pos);
			static Mat4 rotation(const Vec3f& euler);
			static Mat4 scale(const Vec3f& scale);
			static Mat4 lookAt(const Vec3f& camPosition, const Vec3f& target, const Vec3f& up = Vec3f(0, 1, 0));
			
		};
	}
}

#endif // !MAT4_H
