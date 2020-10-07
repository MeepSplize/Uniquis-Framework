#pragma once

#include "Toolkit\\Math\\Vector.h"

namespace Uniquis
{
	struct Quaternion
	{
	public:

		Vector<3> Axis;

		float Scalar;

	public:

		Quaternion();

		Quaternion(const float Pitch, const float Yaw, const float Roll);

		Quaternion(const Vector<3>& axis, const float angle, const bool toRotation = true);

		~Quaternion();

	public:

		float length();
		void  normalize();
		void  conjugate();

		void rotateVector(Vector<3>& vector);

	public:

		DirectX::XMMATRIX operator*() const;

		Quaternion operator+(const Quaternion& other) const;
		Quaternion operator*(const Quaternion& other) const;
	};
}