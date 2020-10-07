#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Vertex.h"

Uniquis::DirectX12::Vertex::Vertex()

	:           Position(),
	              Normal(),
	  TextureCoordinates()
{

}

Uniquis::DirectX12::Vertex::Vertex(const Vector<3> position, const Vector<3> normal, const Vector<2> textureCoordinates)

	:           Position(position),
	              Normal(normal),
	  TextureCoordinates(textureCoordinates)
{

}

Uniquis::DirectX12::Vertex::~Vertex()
{

}