#pragma once

#include "Toolkit\\Math\\Vector.h"

namespace Uniquis::DirectX12
{
	class Vertex
	{
	public:

		Vector<3> Position;
		Vector<3> Normal;
		Vector<2> TextureCoordinates;

	public:

		Vertex();

		Vertex(const Vector<3> position, const Vector<3> normal, const Vector<2> textureCoordinates);

	public:

		~Vertex();
	};
}
