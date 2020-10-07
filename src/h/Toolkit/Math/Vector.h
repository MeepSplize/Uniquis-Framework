#pragma once

namespace Uniquis
{
	#ifdef __AVX2__

	template<unsigned __int8 Dimension>
	class Vector
	{
	public:

		std::array<float, Dimension> vComponents;

	public:

		Vector();

		Vector(const Vector<Dimension>& other);

		Vector(const Vector<Dimension>&& other);

		Vector(const float* pComponents);

		Vector(const std::initializer_list<float> components);

	public:

		~Vector();

	public:

		const float length() const;

		void normalize();

		void scale(const float scalar);

		float dot(const Vector<Dimension>& other) const;

		Vector<3> cross(const Vector<Dimension>& other) const;

		void clear();

	public:

		void operator=(const Vector<Dimension>& other);

		Vector<Dimension> operator*(const float scalar) const;
		Vector<Dimension> operator/(const float scalar) const;

		void operator*=(const float scalar);
		void operator/=(const float scalar);

		Vector<Dimension> operator+(const Vector<Dimension>& other) const;
		Vector<Dimension> operator-(const Vector<Dimension>& other) const;
		Vector<Dimension> operator*(const Vector<Dimension>& other) const;
		Vector<Dimension> operator/(const Vector<Dimension>& other) const;

		void operator+=(const Vector<Dimension>& other);
		void operator-=(const Vector<Dimension>& other);
		void operator*=(const Vector<Dimension>& other);
		void operator/=(const Vector<Dimension>& other);
	};

	template<unsigned __int8 Dimension>
	Vector<Dimension> operator*(const float scalar, const Vector<Dimension>& pVector);

	template<unsigned __int8 Dimension>
	Vector<Dimension> operator/(const float scalar, const Vector<Dimension>& pVector);

	#elif __AVX__

	class Vector
	{

	};

	#endif
}