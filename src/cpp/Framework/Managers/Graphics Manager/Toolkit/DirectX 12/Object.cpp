#include "pch.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\Object.h"

Uniquis::DirectX12::Object::Object(      DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
								   const CommandList&                                           pCommandList,
								   const Device&                                                pDevice)
{
	std::vector<float> vData(11, 0.0f);

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(1, pDescriptorHeap, pDevice);
}

Uniquis::DirectX12::Object::Object(      Uniquis::Object*                                       pObject,
								         DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap,
								   const CommandList&                                           pCommandList,
								   const Device&                                                pDevice)
{
	__int8* p = reinterpret_cast<__int8*>(pObject);

	this->pModelID = reinterpret_cast<unsigned __int32*>(p);

	p += 4; 

	this->pMaterialID = reinterpret_cast<unsigned __int32*>(p);

	p += 4; 

	this->pTransformation = reinterpret_cast<Uniquis::Transformation*>(p);

	Quaternion Quaternion(this->pTransformation->Rotation.vComponents[0], this->pTransformation->Rotation.vComponents[1], this->pTransformation->Rotation.vComponents[2]);

	std::vector<float> vData(11, 0.0f);

	vData[0]  = this->pTransformation->Translation.vComponents[0];
	vData[1]  = this->pTransformation->Translation.vComponents[1];
	vData[2]  = this->pTransformation->Translation.vComponents[2];
			  
	vData[4]  = Quaternion.Axis.vComponents[0];
	vData[5]  = Quaternion.Axis.vComponents[1];
	vData[6]  = Quaternion.Axis.vComponents[2];
	vData[7]  = Quaternion.Scalar;

	vData[8]  = this->pTransformation->Scale.vComponents[0];
	vData[9]  = this->pTransformation->Scale.vComponents[1];
	vData[10] = this->pTransformation->Scale.vComponents[2];

	this->pDataBuffer = std::make_unique<ConstantBuffer>(std::move(vData), pDescriptorHeap, pCommandList, pDevice);

	this->pDataBuffer->bind(1, pDescriptorHeap, pDevice);
}

Uniquis::DirectX12::Object::~Object()
{

}

void Uniquis::DirectX12::Object::bind(Uniquis::Object* pObject)
{
	__int8* p = reinterpret_cast<__int8*>(pObject);

	this->pModelID = reinterpret_cast<unsigned __int32*>(p);

	p += 4; 

	this->pMaterialID = reinterpret_cast<unsigned __int32*>(p);

	p += 4; 

	this->pTransformation = reinterpret_cast<Uniquis::Transformation*>(p);
}

void Uniquis::DirectX12::Object::update(const CommandList& pCommandList)
{
	Quaternion Quaternion(this->pTransformation->Rotation.vComponents[0], this->pTransformation->Rotation.vComponents[1], this->pTransformation->Rotation.vComponents[2]);

	this->pDataBuffer->vData[0]  = this->pTransformation->Translation.vComponents[0];
	this->pDataBuffer->vData[1]  = this->pTransformation->Translation.vComponents[1];
	this->pDataBuffer->vData[2]  = this->pTransformation->Translation.vComponents[2];

	this->pDataBuffer->vData[4]  = Quaternion.Axis.vComponents[0];
	this->pDataBuffer->vData[5]  = Quaternion.Axis.vComponents[1];
	this->pDataBuffer->vData[6]  = Quaternion.Axis.vComponents[2];
	this->pDataBuffer->vData[7]  = Quaternion.Scalar;

	this->pDataBuffer->vData[8]  = this->pTransformation->Scale.vComponents[0];
	this->pDataBuffer->vData[9]  = this->pTransformation->Scale.vComponents[1];
	this->pDataBuffer->vData[10] = this->pTransformation->Scale.vComponents[2];

	this->pDataBuffer->update(pCommandList);
}