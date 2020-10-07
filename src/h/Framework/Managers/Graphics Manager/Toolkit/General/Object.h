#pragma once

#include "..\\..\\Core\\GraphicsManager.h"

#include "Transformation.h"

namespace Uniquis
{
	class Object
	{
	private:

		unsigned __int32 ModelID;
		unsigned __int32 MaterialID;

		Transformation Transformation;

	public:

		Object();

		Object(const unsigned __int32 modelID);

		Object(const unsigned __int32 modelID, const unsigned __int32 materialID);

		~Object();

	public:

		void bind(GraphicsManager& pGraphicsManager);

		void setModel(unsigned __int32 modelID) noexcept;

		void setTransformation(const Uniquis::Transformation& pTransformation) noexcept;

		void move(const Vector<3>& pTranslation) noexcept;
		void rotate(const Vector<3>& pRotation)  noexcept;
		void scale(const Vector<3>& pScale)      noexcept;
	};
}