#pragma once

#include "Toolkit\\Include\\Include.h"

#include "..\\..\\Core\\GraphicsManager.h"

#include "Transformation.h"

namespace Uniquis
{
	class Camera
	{
	public:

		Vector<3> Position;

		Transformation Transformation;

	public:

		Camera();

		~Camera();

	public:

		void bind(const GraphicsManager& pGraphicsManager);

	public:

		void operator=(const Camera&) = delete;
	};
}