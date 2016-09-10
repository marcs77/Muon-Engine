#ifndef VECTOR4_H
#define VECTOR4_H

#include <cmath>
#include <string>
#include <ostream>

namespace muon {
	namespace math {


        template <class T>
		struct Vec4 {
			T x, y, z, w;

			Vec4();
			Vec4(const Vec4& v);
			Vec4(const T& x, const T& y, const T& z, const T& w);

			Vec4 operator+(const Vec4 &v2) const;
			Vec4& operator+=(const Vec4 &v2);

			Vec4 operator-(const Vec4 &v2) const;
			Vec4& operator-=(const Vec4 &v2);

			Vec4 operator*(const Vec4 &v2) const;
			Vec4 operator*(const T &scalar) const;
			Vec4& operator*=(const Vec4 &v2);
			Vec4& operator*=(const T &scalar);

			Vec4 operator/(const Vec4 &v2) const;
			Vec4 operator/(const T &scalar) const;
			Vec4& operator/=(const Vec4 &v2);
			Vec4& operator/=(const T &scalar);

			inline T lengthSquared() const;
			inline T length() const;
			Vec4& normalize();
			Vec4 normalized() const;
			Vec4& limit(const T& max);

			inline T dot(const Vec4 &v2) const;


			inline std::string toString();


			//STATIC
			static inline T distance(const Vec4& a, const Vec4& b);
			static inline Vec4 direction(const Vec4& from, const Vec4& to);
			static inline T projection(const Vec4& a, const Vec4& b);
			static inline Vec4 projectionVector(const Vec4& a, const Vec4& b);
		};

		/* Constructors */

		template<typename T>
		inline Vec4<T>::Vec4() : x(0), y(0), z(0), w(0) { }

		template<typename T>
		inline Vec4<T>::Vec4(const Vec4 & v) : x(v.x), y(v.y), z(v.z), w(v.w) {	}

		template<typename T>
		inline Vec4<T>::Vec4(const T & x, const T & y, const T & z, const T & w) : x(x), y(y), z(z), w(w) { }


		/* Operators */

		template<typename T>
		Vec4<T> Vec4<T>::operator+(const Vec4 & v2) const
		{
			return Vec4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
		}

		template<typename T>
		Vec4<T>& Vec4<T>::operator+=(const Vec4 & v2)
		{
			x += v2.x;
			y += v2.y;
			z += v2.z;
			w += v2.w;
			return *this;
		}

		template<typename T>
		Vec4<T> Vec4<T>::operator-(const Vec4 & v2) const
		{
			return Vec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
		}

		template<typename T>
		Vec4<T>& Vec4<T>::operator-=(const Vec4 & v2)
		{
			x -= v2.x;
			y -= v2.y;
			z -= v2.z;
			w -= v2.w;
			return *this;
		}

		template<typename T>
		Vec4<T> Vec4<T>::operator*(const Vec4 & v2) const
		{
			return Vec4(x * v2.x, y * v2.y, z * v2.z, w * v2.w);
		}

		template<typename T>
		Vec4<T> Vec4<T>::operator*(const T &scalar) const
		{
			return Vec4(x * scalar, y * scalar, z * scalar, w * scalar);
		}

		template<typename T>
		Vec4<T>& Vec4<T>::operator*=(const Vec4 & v2)
		{
			x *= v2.x;
			y *= v2.y;
			z *= v2.z;
			w *= v2.w;
			return *this;
		}

		template<typename T>
		inline Vec4<T> & Vec4<T>::operator*=(const T & scalar)
		{
			x *= scalar;
			y *= scalar;
			z *= scalar;
			w *= scalar;
			return *this;
		}

		template<typename T>
		Vec4<T> Vec4<T>::operator/(const Vec4 & v2) const
		{
			return Vec4(x / v2.x, y / v2.y, z / v2.z, w / v2.w);
		}

		template<typename T>
		Vec4<T> Vec4<T>::operator/(const T &scalar) const
		{
			T inv = 1.0 / scalar;
			return Vec4(x * inv, y * inv, z * inv, w * inv);
		}

		template<typename T>
		Vec4<T>& Vec4<T>::operator/=(const Vec4 & v2)
		{
			x /= v2.x;
			y /= v2.y;
			z /= v2.z;
			w /= v2.w;
			return *this;
		}

		template<typename T>
		inline Vec4<T> & Vec4<T>::operator/=(const T & scalar)
		{
			T inv = 1.0 / scalar;
			x *= inv;
			y *= inv;
			z *= inv;
			w *= inv;
			return *this;
		}

		/* Methods */

		template<typename T>
		inline T Vec4<T>::lengthSquared() const
		{
			return x*x + y*y + z*z + w*w;
		}

		template<typename T>
		inline T Vec4<T>::length() const
		{
            return (T)sqrt(lengthSquared());
		}

		template<typename T>
		inline Vec4<T>& Vec4<T>::normalize()
		{
			if (x != 0 || y != 0 || z != 0 || w != 0) {
				(*this) *= 1.0 / length();
			}
			return *this;
		}

		template<typename T>
		inline Vec4<T> Vec4<T>::normalized() const
		{
			if (x != 0 || y != 0 || z != 0 || w != 0) {
				return (*this) / length();
			}
			return Vec4<T>();
		}

		template<typename T>
		inline Vec4<T> & Vec4<T>::limit(const T& max)
		{
			if (lengthSquared > max*max) {
				normalize();
				(*this) *= max;
			}
		}

		template<typename T>
		inline T Vec4<T>::dot(const Vec4 & v2) const
		{
			return x*v2.x + y*v2.y + z*v2.z + w*v2.w;
		}




		template<typename T>
		inline std::string Vec4<T>::toString()
		{
			return "Vec4: (" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + ")";
		}


		/* Static */
		template<typename T>
		inline T Vec4<T>::distance(const Vec4<T> & a, const Vec4<T> & b)
		{
			return (b - a).length();
		}

		template<typename T>
		inline Vec4<T> Vec4<T>::direction(const Vec4 & from, const Vec4 & to)
		{
			return (to - from).normalize();
		}

		template<typename T>
		inline T Vec4<T>::projection(const Vec4 & a, const Vec4 & b)
		{
			return a.dot(b) / b.length();
		}

		template<typename T>
		inline Vec4<T> Vec4<T>::projectionVector(const Vec4 & a, const Vec4 & b)
		{
			return b.normalized() * projection(a, b);
		}

		template <typename T>
		std::ostream& operator<<(std::ostream& stream, const Vec4<T>& vector)
		{
			stream << "Vec4: (" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << ")";
			return stream;
		}


		typedef Vec4<float> Vec4f;
		typedef Vec4<double> Vec4d;
		typedef Vec4<int> Vec4i;

	}

}

#endif // !VECTOR4_H

