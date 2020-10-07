#pragma once

#include "Toolkit\\Math\\Vector.h"

namespace Uniquis
{
	class Transformation
	{
	public:

		Vector<3> Translation;
		Vector<3> Rotation;
		Vector<3> Scale;

	public:

		Transformation();

		Transformation(const Transformation&) = delete;

		Transformation(const Transformation&&) = delete;

		Transformation(const Vector<3>& pTranslation, const Vector<3>& pRotation, const Vector<3>& pScale);

		~Transformation();

	public:

		void operator=(const Transformation& other) noexcept;
	};
}