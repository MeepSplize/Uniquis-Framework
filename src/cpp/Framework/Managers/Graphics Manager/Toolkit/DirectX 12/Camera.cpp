#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Camera.h"

Uniquis::DirectX12::Camera::Camera(const __int16 width, const __int16 height)

	:                   Width(width),
					   Height(height),
	                      FoV(90.0f),
	                    NearZ(0.0001f),
	                     FarZ(1000.0f),
						Pitch(0.0f),
	                      Yaw(0.0f),
						 Roll(0.0f),
	              TravelSpeed(0.05f),
	            RotationSpeed(2.0f)
{
	this->PerspectiveProjectionData[1] = (cosf(this->FoV * 0.5f) / sinf(this->FoV * 0.5f));
	this->PerspectiveProjectionData[0] = (this->PerspectiveProjectionData[1] / (static_cast<float>(width) / static_cast<float>(height)));
	this->PerspectiveProjectionData[2] = (this->FarZ / (this->FarZ - this->NearZ));
	this->PerspectiveProjectionData[3] = -(this->NearZ);
}

Uniquis::DirectX12::Camera::~Camera()
{

}

void Uniquis::DirectX12::Camera::update()
{
	this->Rotation = std::move(Quaternion(this->Pitch, this->Yaw, this->Roll));
}

void Uniquis::DirectX12::Camera::move(Vector<3> translation)
{
	translation *= this->TravelSpeed;

	Quaternion PlaneRotation(std::move(Vector<3>( { 0.0f, 1.0f, 0.0f } )), this->Yaw);
	
	PlaneRotation.rotateVector(translation);

	this->Position += translation;
}

void Uniquis::DirectX12::Camera::rotate(float pitch, float yaw, float roll)
{
	this->Pitch = std::clamp(this->Pitch + (pitch * this->RotationSpeed), -(90.0f), 90.0f);
	
	this->Yaw += (yaw * this->RotationSpeed);

	this->Roll = std::clamp(this->Roll + (roll * this->RotationSpeed), -(180.0f), 180.0f);
	
	     if (Yaw < -180.0f) (this->Yaw += 360.0f);
	else if (Yaw >  180.0f) (this->Yaw -= 360.0f);
}