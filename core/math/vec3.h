#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include <string>
#include "vec2.h"

namespace muon {
	namespace math {


        template <class T>
		struct Vec3 {
			T x, y, z;

			Vec3();
			Vec3(const Vec3& v);
			Vec3(const T& x, const T& y, const T& z);

			Vec3 operator+(const Vec3 &v2) const;
			Vec3& operator+=(const Vec3 &v2);

			Vec3 operator-(const Vec3 &v2) const;
			Vec3& operator-=(const Vec3 &v2);

			Vec3 operator*(const Vec3 &v2) const;
			Vec3 operator*(const T &scalar) const;
			Vec3& operator*=(const Vec3 &v2);
			Vec3& operator*=(const T &scalar);

			Vec3 operator/(const Vec3 &v2) const;
			Vec3 operator/(const T &scalar) const;
			Vec3& operator/=(const Vec3 &v2);
			Vec3& operator/=(const T &scalar);

			inline T lengthSquared() const;
			inline T length() const;
			Vec3& normalize();
			Vec3 normalized() const;
			Vec3& limit(const T& max);

			inline T dot(const Vec3 &v2) const;
			inline Vec3<T> cross(const Vec3 &v2) const;


			inline std::string toString();


			void set(const Vec3& v);
			void set(const T& x, const T& y, const T& z);

			//STATIC
			static inline T distance(const Vec3& a, const Vec3& b);
			static inline Vec3 direction(const Vec3& from, const Vec3& to);
			static inline T projection(const Vec3& a, const Vec3& b);
			static inline Vec3 projectionVector(const Vec3& a, const Vec3& b);
		};

		/* Constructors */

		template<typename T>
		inline Vec3<T>::Vec3() : x(0), y(0), z(0) { }

		template<typename T>
		inline Vec3<T>::Vec3(const Vec3 & v) : x(v.x), y(v.y), z(v.z) {	}

		template<typename T>
		inline Vec3<T>::Vec3(const T & x, const T & y, const T & z) : x(x), y(y), z(z) { }

		/* Operators */

		template<typename T>
		Vec3<T> Vec3<T>::operator+(const Vec3 & v2) const
		{
			return Vec3(x + v2.x, y + v2.y, z + v2.z);
		}

		template<typename T>
		Vec3<T>& Vec3<T>::operator+=(const Vec3 & v2)
		{
			x += v2.x;
			y += v2.y;
			z += v2.z;
			return *this;
		}

		template<typename T>
		Vec3<T> Vec3<T>::operator-(const Vec3 & v2) const
		{
			return Vec3(x - v2.x, y - v2.y, z - v2.z);
		}

		template<typename T>
		Vec3<T>& Vec3<T>::operator-=(const Vec3 & v2)
		{
			x -= v2.x;
			y -= v2.y;
			z -= v2.z;
			return *this;
		}

		template<typename T>
		Vec3<T> Vec3<T>::operator*(const Vec3 & v2) const
		{
			return Vec3(x * v2.x, y * v2.y, z * v2.z);
		}

		template<typename T>
		Vec3<T> Vec3<T>::operator*(const T &scalar) const
		{
			return Vec3(x * scalar, y * scalar, z * scalar);
		}

		template<typename T>
		Vec3<T>& Vec3<T>::operator*=(const Vec3 & v2)
		{
			x *= v2.x;
			y *= v2.y;
			z *= v2.z;
			return *this;
		}

		template<typename T>
		inline Vec3<T> & Vec3<T>::operator*=(const T & scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			return *this;
		}

		template<typename T>
		Vec3<T> Vec3<T>::operator/(const Vec3 & v2) const
		{
			return Vec3(x / v2.x, y / v2.y, z / v2.z);
		}

		template<typename T>
		Vec3<T> Vec3<T>::operator/(const T &scalar) const
		{
			T inv = 1.0 / scalar;
			return Vec3(x * inv, y * inv, z * inv);
		}

		template<typename T>
		Vec3<T>& Vec3<T>::operator/=(const Vec3 & v2)
		{
			x /= v2.x;
			y /= v2.y;
			z /= v2.z;
			return *this;
		}

		template<typename T>
		inline Vec3<T> & Vec3<T>::operator/=(const T & scalar)
		{
			T inv = 1.0 / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			return *this;
		}

		/* Methods */

		template<typename T>
		inline T Vec3<T>::lengthSquared() const
		{
			return x*x + y*y + z*z;
		}

		template<typename T>
		inline T Vec3<T>::length() const
		{
            return (T) sqrt(lengthSquared());
		}

		template<typename T>
		inline Vec3<T>& Vec3<T>::normalize()
		{
			if (x != 0 || y != 0 || z != 0) {
				(*this) *= 1.0 / length();
			}
			return *this;
		}

		template<typename T>
		inline Vec3<T> Vec3<T>::normalized() const
		{
			if (x != 0 || y != 0 || z != 0) {
				return (*this) / length();
			}
			return Vec3<T>();
		}

		template<typename T>
		inline Vec3<T> & Vec3<T>::limit(const T& max)
		{
			if (lengthSquared > max*max) {
				normalize();
				(*this) *= max;
			}
		}

		template<typename T>
		inline T Vec3<T>::dot(const Vec3 & v2) const
		{
			return x*v2.x + y*v2.y + z*v2.z;
		}

		template<typename T>
		inline Vec3<T> Vec3<T>::cross(const Vec3 & v2) const
		{
			return Vec3<T>(
				y * v2.z - z * v2.y,
				z * v2.x - x * v2.z,
				x * v2.y - y * v2.x
				);
		}




		template<typename T>
		inline std::string Vec3<T>::toString()
		{
			return "Vec3: (" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
		}

		template<typename T>
		inline void Vec3<T>::set(const Vec3 & v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		template<typename T>
		inline void Vec3<T>::set(const T & x, const T & y, const T & z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}


		/* Static */
		template<typename T>
		inline T Vec3<T>::distance(const Vec3<T> & a, const Vec3<T> & b)
		{
			return (b - a).length();
		}

		template<typename T>
		inline Vec3<T> Vec3<T>::direction(const Vec3 & from, const Vec3 & to)
		{
			return (to - from).normalize();
		}

		template<typename T>
		inline T Vec3<T>::projection(const Vec3 & a, const Vec3 & b)
		{
			return a.dot(b) / b.length();
		}

		template<typename T>
		inline Vec3<T> Vec3<T>::projectionVector(const Vec3 & a, const Vec3 & b)
		{
			return b.normalized() * projection(a, b);
		}

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const Vec3<T>& vector)
		{
			stream << "Vec3: (" << vector.x << ", " << vector.y << ", " << vector.z << ")";
			return stream;
		}


		typedef Vec3<float> Vec3f;
		typedef Vec3<double> Vec3d;
		typedef Vec3<int> Vec3i;

	}

}

#endif // !VECTOR3_H
