#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>
#include <string>
#include <ostream>

namespace muon { namespace math {

	
    template <class T>
	struct Vec2 {
		T x, y;

		Vec2();
		Vec2(const Vec2& v);
		Vec2(const T& x, const T& y);

		Vec2 operator+(const Vec2 &v2) const;
		Vec2& operator+=(const Vec2 &v2);

		Vec2 operator-(const Vec2 &v2) const;
		Vec2& operator-=(const Vec2 &v2);

		Vec2 operator*(const Vec2 &v2) const;
		Vec2 operator*(const T &scalar) const;
		Vec2& operator*=(const Vec2 &v2);
		Vec2& operator*=(const T &scalar);

		Vec2 operator/(const Vec2 &v2) const;
		Vec2 operator/(const T &scalar) const;
		Vec2& operator/=(const Vec2 &v2);
		Vec2& operator/=(const T &scalar);

		inline T lengthSquared() const;
		inline T length() const;
		Vec2& normalize();
		Vec2 normalized() const;
		Vec2& limit(const T& max);

		inline T dot(const Vec2 &v2) const;


		inline std::string toString();


		//STATIC
		static inline T distance(const Vec2& a, const Vec2& b);
		static inline Vec2 direction(const Vec2& from, const Vec2& to);
		static inline T projection(const Vec2& a, const Vec2& b);
		static inline Vec2 projectionVector(const Vec2& a, const Vec2& b);
	};

	/* Constructors */

	template<typename T>
	inline Vec2<T>::Vec2() : x(0), y(0) { }

	template<typename T>
	inline Vec2<T>::Vec2(const Vec2 & v) : x(v.x), y(v.y) {	}

	template<typename T>
	inline Vec2<T>::Vec2(const T & x, const T & y): x(x), y(y) { }


	/* Operators */

	template<typename T>
	Vec2<T> Vec2<T>::operator+(const Vec2 & v2) const
	{
		return Vec2(x+v2.x, y+v2.y);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator+=(const Vec2 & v2) 
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator-(const Vec2 & v2) const
	{
		return Vec2(x - v2.x, y - v2.y);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator-=(const Vec2 & v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator*(const Vec2 & v2) const
	{
		return Vec2(x * v2.x, y * v2.y);
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator*(const T &scalar) const
	{
		return Vec2(x * scalar, y * scalar);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator*=(const Vec2 & v2)
	{
		x *= v2.x;
		y *= v2.y;
		return *this;
	}

	template<typename T>
	inline Vec2<T> & Vec2<T>::operator*=(const T & scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator/(const Vec2 & v2) const
	{
		return Vec2(x / v2.x, y / v2.y);
	}

	template<typename T>
	Vec2<T> Vec2<T>::operator/(const T &scalar) const
	{
		T inv = 1.0 / scalar;
		return Vec2(x * inv, y * inv);
	}

	template<typename T>
	Vec2<T>& Vec2<T>::operator/=(const Vec2 & v2)
	{
		x /= v2.x;
		y /= v2.y;
		return *this;
	}

	template<typename T>
	inline Vec2<T> & Vec2<T>::operator/=(const T & scalar)
	{
		T inv = 1.0 / scalar;
		x *= inv;
		y *= inv;
		return *this;
	}

	/* Methods */

	template<typename T>
	inline T Vec2<T>::lengthSquared() const
	{
		return x*x + y*y;
	}

	template<typename T>
	inline T Vec2<T>::length() const
	{
        return (T) sqrt(x*x + y*y);
	}

	template<typename T>
	inline Vec2<T>& Vec2<T>::normalize()
	{
		if (x != 0 || y != 0) {
			(*this) *= 1.0 / length();
		}
		return *this;
	}

	template<typename T>
	inline Vec2<T> Vec2<T>::normalized() const
	{
		if (x != 0 || y != 0) {
			return (*this) / length();
		}
		return Vec2<T>();
	}

	template<typename T>
	inline Vec2<T> & Vec2<T>::limit(const T& max)
	{
		if (lengthSquared > max*max) {
			normalize();
			(*this) *= max;
		}
	}

	template<typename T>
	inline T Vec2<T>::dot(const Vec2 & v2) const
	{
		return x*v2.x+y*v2.y;
	}




	template<typename T>
	inline std::string Vec2<T>::toString()
	{
		return "Vec2: (" + std::to_string(x) + "," + std::to_string(y) + ")";
	}


	/* Static */
	template<typename T>
	inline T Vec2<T>::distance(const Vec2<T> & a, const Vec2<T> & b)
	{
		return (b - a).length();
	}

	template<typename T>
	inline Vec2<T> Vec2<T>::direction(const Vec2 & from, const Vec2 & to)
	{
		return (to - from).normalize();
	}

	template<typename T>
	inline T Vec2<T>::projection(const Vec2 & a, const Vec2 & b)
	{
		return a.dot(b) / b.length();
	}

	template<typename T>
	inline Vec2<T> Vec2<T>::projectionVector(const Vec2 & a, const Vec2 & b)
	{
		return b.normalized() * projection(a, b);
	}

	template <typename T>
	std::ostream& operator<<(std::ostream& stream, const Vec2<T>& vector)
	{
		stream << "Vec2: (" << vector.x << ", " << vector.y << ")";
		return stream;
	}


	typedef Vec2<float> Vec2f;
	typedef Vec2<double> Vec2d;
	typedef Vec2<int> Vec2i;

}

}

#endif // !VECTOR2_H
