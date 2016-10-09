#include "mat4.h"

#include <math.h>
#include "mathutils.h"
#include <string.h>

namespace muon {
	namespace math {
		Mat4::Mat4() {
			memset(m, 0, 4 * 4 * sizeof(float));
		}

		Mat4::Mat4(const Mat4 & other)
		{
			memcpy(m, other.m, 4 * 4 * sizeof(float));
		}

		Mat4::Mat4(float diagonal) {
			memset(m, 0, 4 * 4 * sizeof(float));
			for (int i = 0; i < 4; i++)
				*getP(i, i) = diagonal;
		}

		float * Mat4::getP(int x, int y)
		{
			return &m[y + x*4];
		}

		float Mat4::get(int x, int y) const
		{
			return m[y + x * 4];
		}

		void Mat4::setIdentity()
		{
			memset(m, 0, 4 * 4 * sizeof(float));
			for (int i = 0; i < 4; i++) *getP(i,i) = 1;
		}

		void Mat4::multiply(const Mat4 & right)
		{
			Mat4 res = Mat4::multiply(*this, right);
			for (int i = 0; i < 16; i++) {
				m[i] = res.m[i];
			}
		}

		Mat4 Mat4::operator*(const Mat4 & right) const
		{
			return Mat4::multiply(*this, right);
		}

		Vec3f operator*(const Mat4& m,const Vec3f & v) 
		{
			return Vec3f
				(
					m.get(0, 0)*v.x + m.get(1, 0)*v.y + m.get(2, 0)*v.z + m.get(3, 0),
					m.get(0, 1)*v.x + m.get(1, 1)*v.y + m.get(2, 1)*v.z + m.get(3, 1),
					m.get(0, 2)*v.x + m.get(1, 2)*v.y + m.get(2, 2)*v.z + m.get(3, 2)
				);
		}

		Vec4f operator*(const Mat4& m, const Vec4f & v)
		{
			return Vec4f
				(
					m.get(0, 0)*v.x + m.get(1, 0)*v.y + m.get(2, 0)*v.z + m.get(3, 0)*v.w,
					m.get(0, 1)*v.x + m.get(1, 1)*v.y + m.get(2, 1)*v.z + m.get(3, 1)*v.w,
					m.get(0, 2)*v.x + m.get(1, 2)*v.y + m.get(2, 2)*v.z + m.get(3, 2)*v.w,
					m.get(0, 3)*v.x + m.get(1, 3)*v.y + m.get(2, 3)*v.z + m.get(3, 3)*v.w
				);
		}


		Mat4 & Mat4::operator*=(const Mat4 & right)
		{
			multiply(right);
			return *this;
		}

		void Mat4::translate(const Vec3f & v)
		{
			*getP(3, 0) += get(0, 0) * v.x + get(1, 0) * v.y + get(2, 0) * v.z;
			*getP(3, 1) += get(0, 1) * v.x + get(1, 1) * v.y + get(2, 1) * v.z;
			*getP(3, 2) += get(0, 2) * v.x + get(1, 2) * v.y + get(2, 2) * v.z;
			*getP(3, 3) += get(0, 3) * v.x + get(1, 3) * v.y + get(2, 3) * v.z;
		}

		void Mat4::setTranslation(const Vec3f & v)
		{
			*getP(3, 0) = v.x;
			*getP(3, 1) = v.y;
			*getP(3, 2) = v.z;
		}

		void Mat4::print(std::ostream& stream)
		{
			for (int y = 0; y < 4; y++) {
				stream << "[ ";
				for (int x = 0; x < 4; x++) {
					stream << get(x, y) << '/t';
				}
				stream << "]/n";
			}
		}

		Mat4 Mat4::identity()
		{
			return Mat4(1);
		}

		Mat4 Mat4::ortho(float left, float right, float bot, float top, float near, float far)
		{
			Mat4 ortho;
			*ortho.getP(0,0) = 2.0 / (right - left);
			*ortho.getP(1,1) = 2.0 / (top - bot);
			*ortho.getP(2,2) = - 2.0 / (far - near);
			*ortho.getP(3,3) = 1;

			*ortho.getP(3, 0) = (-right - left) / (right - left);
			*ortho.getP(3, 1) = (-top - bot) / (top - bot);
			*ortho.getP(3, 2) = (-far - near) / (far - near);

			return ortho;
		}

		Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			float radfov = TO_RAD(fov);
			float cotanfov = 1.0f / std::tan(radfov * 0.5f);
			float zm = far - near;
			float zp = far + near;
			Mat4 persp;

			*persp.getP(0, 0) = (1.0 / aspectRatio)*cotanfov;
			*persp.getP(1, 1) = cotanfov;
			*persp.getP(2, 2) = -zp / zm;
			*persp.getP(2, 3) = -1;
			*persp.getP(3, 2) = -2.0 * far * near / zm;
			*persp.getP(3, 3) = 0;

			return persp;
		}

		Mat4 Mat4::multiply(const Mat4 & l, const Mat4 & r)
		{
			Mat4 res;

			for (int x = 0; x < 4; x++) {
				for (int y = 0; y < 4; y++) {
					float sum = 0;
					for (int e = 0; e < 4; e++) {
						sum += l.m[x + e * 4] * r.m[e + y * 4];
					}
					res.m[x + y * 4] = sum;
				}
			}

			return res;
		}

		Mat4 Mat4::translation(const Vec3f & pos)
		{
			Mat4 result(1.0f);

			*result.getP(3, 0) = pos.x;
			*result.getP(3, 1) = pos.y;
			*result.getP(3, 2) = pos.z;

			return result;
		}

		Mat4 Mat4::rotation(const Vec3f& euler)
		{

			Mat4 result(1.0);

			float x = TO_RAD(euler.x);
			float y = TO_RAD(euler.y);
			float z = TO_RAD(euler.z);
			float cx = cos(x);
			float cy = cos(y);
			float cz = cos(z);
			float sx = sin(x);
			float sy = sin(y);
			float sz = sin(z);

			*result.getP(0, 0) = cy*cz;
			*result.getP(0, 1) = sx*sy*cz + cx*sz;
			*result.getP(0, 2) = -cx*sy*cz + sx*sz;

			*result.getP(1, 0) = -cy*sz;
			*result.getP(1, 1) = -sx*sy*sz + cx*cz;
			*result.getP(1, 2) = cx*sy*sz + sx*cz;

			*result.getP(2, 0) = sy;
			*result.getP(2, 1) = -sx * cy;
			*result.getP(2, 2) = cx * cy;

			return result;
		}

		Mat4 Mat4::scale(const Vec3f & scale)
		{
			Mat4 result(1.0f);

			*result.getP(0, 0) = scale.x;
			*result.getP(1, 1) = scale.y;
			*result.getP(2, 2) = scale.z;

			return result;
		}
	}
}
