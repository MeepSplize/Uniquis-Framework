#include "pch.h"

#include "Toolkit\\Math\\Vector.h"

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::Vector()

	: vComponents()
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] = 0;
	}
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::Vector(const Vector<Dimension>& other)

	: vComponents(other.vComponents)
{

}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::Vector(const Vector<Dimension>&& other)

	: vComponents(std::move(other.vComponents))
{

}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::Vector(const float* pComponents)

	: vComponents()
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		vComponents[i] = pComponents[i];
	}
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::Vector(const std::initializer_list<float> components)

	: vComponents()
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		vComponents[i] = components.begin()[i];
	}
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension>::~Vector()
{

}

template<unsigned __int8 Dimension>
const float Uniquis::Vector<Dimension>::length() const
{
	float Sum = 0;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Sum += (this->vComponents[i] * this->vComponents[i]);
	}

	return std::move(sqrtf(Sum));
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::normalize()
{
	const float Length = this->length();

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] /= Length;
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::scale(const float scalar)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] *= scalar;
	}
}

template<unsigned __int8 Dimension>
float Uniquis::Vector<Dimension>::dot(const Vector<Dimension>& other) const
{
	float Product = 0;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Product += (this->vComponents[i] * other.vComponents[i]);
	}

	return std::move(Product);
}

template<unsigned __int8 Dimension>
Uniquis::Vector<3> Uniquis::Vector<Dimension>::cross(const Vector<Dimension>& other) const
{
	std::array<float, 3> vTemporaryStorage;

	vTemporaryStorage[0] = ((this->vComponents[1] * other.vComponents[2]) - (this->vComponents[2] * other.vComponents[1]));
	vTemporaryStorage[1] = ((this->vComponents[2] * other.vComponents[0]) - (this->vComponents[0] * other.vComponents[2]));
	vTemporaryStorage[2] = ((this->vComponents[0] * other.vComponents[1]) - (this->vComponents[1] * other.vComponents[0]));

	return std::move(Vector<3>(vTemporaryStorage.data()));
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::clear()
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] = 0.0f;
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator=(const Vector<Dimension>& other)
{
	this->vComponents = other.vComponents;
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator*(const float scalar) const
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (scalar * this->vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator/(const float scalar) const
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (this->vComponents[i] / scalar);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator*=(const float scalar)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] *= scalar;
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator/=(const float scalar)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] /= scalar;
	}
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator+(const Vector<Dimension>& other) const
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (this->vComponents[i] + other.vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator-(const Vector<Dimension>& other) const
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (this->vComponents[i] - other.vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator*(const Vector<Dimension>& other) const
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (other.vComponents[i] * this->vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::Vector<Dimension>::operator/(const Vector<Dimension>& other) const
{
	std::array<float, (Dimension + 1)> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (this->vComponents[i] / other.vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator+=(const Vector<Dimension>& other)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] += other.vComponents[i];
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator-=(const Vector<Dimension>& other)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] -= other.vComponents[i];
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator*=(const Vector<Dimension>& other)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] *= other.vComponents[i];
	}
}

template<unsigned __int8 Dimension>
void Uniquis::Vector<Dimension>::operator/=(const Vector<Dimension>& other)
{
	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		this->vComponents[i] /= other.vComponents[i];
	}
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::operator*(const float scalar, const Vector<Dimension>& pVector)
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (scalar * pVector.vComponents[i]);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template<unsigned __int8 Dimension>
Uniquis::Vector<Dimension> Uniquis::operator/(const float scalar, const Vector<Dimension>& pVector)
{
	std::array<float, Dimension> Array;

	for (unsigned __int8 i = 0; i < Dimension; i++)
	{
		Array[i] = (pVector.vComponents[i] / scalar);
	}

	return std::move(Vector<Dimension>(Array.data()));
}

template class Uniquis::Vector<2>;
template class Uniquis::Vector<3>;
template class Uniquis::Vector<4>;

template Uniquis::Vector<2> Uniquis::operator*(const float scalar, const Vector<2>& pVector);
template Uniquis::Vector<3> Uniquis::operator*(const float scalar, const Vector<3>& pVector);
template Uniquis::Vector<4> Uniquis::operator*(const float scalar, const Vector<4>& pVector);

template Uniquis::Vector<2> Uniquis::operator/(const float scalar, const Vector<2>& pVector);
template Uniquis::Vector<3> Uniquis::operator/(const float scalar, const Vector<3>& pVector);
template Uniquis::Vector<4> Uniquis::operator/(const float scalar, const Vector<4>& pVector);