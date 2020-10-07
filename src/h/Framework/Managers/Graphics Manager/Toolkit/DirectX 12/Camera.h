#pragma once

#include "Toolkit\\Math\\Quaternion.h"
#include "Toolkit\\Math\\Vector.h"

#include "..\\General\\Transformation.h"

namespace Uniquis::DirectX12
{
	class Camera
	{
	public:

		float Width;
		float Height;

		float FoV;
		float NearZ;
		float FarZ;

		float Pitch;
		float Yaw;
		float Roll;

		float TravelSpeed;
		float RotationSpeed;

		Vector<3>  Position;
		Quaternion Rotation;
		
		float PerspectiveProjectionData[4];

	public:

		Camera(const __int16 width, const __int16 height);

		~Camera();

	public:

		void update();
		void move(Vector<3> translation);
		void rotate(float pitch, float yaw, float roll);
	};
}