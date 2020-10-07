#include "pch.h"

#include "Toolkit\\Math\\Quaternion.h"

Uniquis::Quaternion::Quaternion()

	:   Axis(),
	  Scalar()
{

}

Uniquis::Quaternion::Quaternion(const float pitch, const float yaw, const float roll)

	:   Axis(),
	  Scalar()
{
	float DegreesToRadians = (Pi / 180);

	float HalfPitchInRadians = ((pitch * DegreesToRadians) / 2);
	float HalfYawInRadians   = ((yaw * DegreesToRadians) / 2);
	float HalfRollInRadians  = ((roll * DegreesToRadians) / 2);

	float Sin1 = sinf(HalfPitchInRadians);
	float Sin2 = sinf(HalfYawInRadians);
	float Sin3 = sinf(HalfRollInRadians);
	
	float Cos1 = cosf(HalfPitchInRadians);
	float Cos2 = cosf(HalfYawInRadians);
	float Cos3 = cosf(HalfRollInRadians);
	
	this->Axis.vComponents[0] = ((Sin2 * Sin3 * Cos1) + (Cos2 * Cos3 * Sin1));
	this->Axis.vComponents[1] = ((Sin2 * Cos3 * Cos1) + (Cos2 * Sin3 * Sin1));
	this->Axis.vComponents[2] = ((Cos2 * Sin3 * Cos1) - (Sin2 * Cos3 * Sin1));
	this->Scalar              = ((Cos2 * Cos3 * Cos1) - (Sin2 * Sin3 * Sin1));
}

Uniquis::Quaternion::Quaternion(const Vector<3>& axis, const float angle, const bool toRotation)

	:   Axis(axis),
	  Scalar(angle)
{
	if (!(toRotation))
	{
		this->normalize();
	}
	else
	{
		const float Radians = ((angle * Pi) / 180);
	
		this->Axis.vComponents[0] = (axis.vComponents[0] * sinf(Radians / 2));
		this->Axis.vComponents[1] = (axis.vComponents[1] * sinf(Radians / 2));
		this->Axis.vComponents[2] = (axis.vComponents[2] * sinf(Radians / 2));
		
		this->Scalar = cosf(Radians / 2);
	}
}

Uniquis::Quaternion::~Quaternion()
{

}

float Uniquis::Quaternion::length()
{
	return sqrtf((this->Axis.vComponents[0] * this->Axis.vComponents[0]) + 
				 (this->Axis.vComponents[1] * this->Axis.vComponents[1]) + 
				 (this->Axis.vComponents[2] * this->Axis.vComponents[2]) + 

				 (this->Scalar * this->Scalar));
}

void Uniquis::Quaternion::normalize()
{
	const float Length = this->length();

	this->Axis /= Length;

	this->Scalar /= Length;
}

void Uniquis::Quaternion::conjugate()
{
	this->Axis.vComponents[0] = -(this->Axis.vComponents[0]);
	this->Axis.vComponents[1] = -(this->Axis.vComponents[1]);
	this->Axis.vComponents[2] = -(this->Axis.vComponents[2]);
}

DirectX::XMMATRIX Uniquis::Quaternion::operator*() const
{
	DirectX::XMMATRIX Matrix((1 - 2 * this->Axis.vComponents[1] * this->Axis.vComponents[1] - 2 * this->Axis.vComponents[2] * this->Axis.vComponents[2]), (2 * this->Axis.vComponents[0] * this->Axis.vComponents[1] - 2 * this->Scalar * this->Axis.vComponents[2]),                 (2 * this->Axis.vComponents[0] * this->Axis.vComponents[2] + 2 * this->Scalar * this->Axis.vComponents[1]),                 0,
							 (2 * this->Axis.vComponents[0] * this->Axis.vComponents[1] + 2 * this->Scalar * this->Axis.vComponents[2]),                 (1 - 2 * this->Axis.vComponents[0] * this->Axis.vComponents[0] - 2 * this->Axis.vComponents[2] * this->Axis.vComponents[2]), (2 * this->Axis.vComponents[1] * this->Axis.vComponents[2] + 2 * this->Scalar * this->Axis.vComponents[0]),                 0,
							 (2 * this->Axis.vComponents[0] * this->Axis.vComponents[2] - 2 * this->Scalar * this->Axis.vComponents[1]),                 (2 * this->Axis.vComponents[1] * this->Axis.vComponents[2] - 2 * this->Scalar * this->Axis.vComponents[0]),                 (1 - 2 * this->Axis.vComponents[0] * this->Axis.vComponents[0] - 2 * this->Axis.vComponents[1] * this->Axis.vComponents[1]), 0,
							 0, 0, 0, 1);

	return std::move(Matrix);
}

Uniquis::Quaternion Uniquis::Quaternion::operator+(const Quaternion& other) const
{
	return Quaternion((this->Axis + other.Axis), (this->Scalar + other.Scalar), false);
}

Uniquis::Quaternion Uniquis::Quaternion::operator*(const Quaternion& other) const
{
	float Array[3];

	Array[0] =  ((this->Axis.vComponents[0] * other.Scalar) + (this->Axis.vComponents[1] * other.Axis.vComponents[2]) - (this->Axis.vComponents[2] * other.Axis.vComponents[1]) + (this->Scalar * other.Axis.vComponents[0]));
	Array[1] = -((this->Axis.vComponents[0] * other.Axis.vComponents[2]) + (this->Axis.vComponents[1] * other.Scalar) + (this->Axis.vComponents[2] * other.Axis.vComponents[0]) + (this->Scalar * other.Axis.vComponents[1]));
	Array[2] =  ((this->Axis.vComponents[0] * other.Axis.vComponents[1]) - (this->Axis.vComponents[1] * other.Axis.vComponents[0]) + (this->Axis.vComponents[2] * other.Scalar) + (this->Scalar * other.Axis.vComponents[2]));
	
	const float Scalar = -((this->Axis.vComponents[0] * other.Axis.vComponents[0]) - (this->Axis.vComponents[1] * other.Axis.vComponents[1]) - (this->Axis.vComponents[2] * other.Axis.vComponents[2]) + (this->Scalar * other.Scalar));

	return Quaternion(std::move(Vector<3>(Array)), Scalar, false);
}

void Uniquis::Quaternion::rotateVector(Vector<3>& vector)
{
	vector = (this->Axis * (2.0f * this->Axis.dot(vector))) + (vector * ((this->Scalar * this->Scalar) - this->Axis.dot(this->Axis))) + (this->Axis.cross(vector) * (2.0f * this->Scalar));
}