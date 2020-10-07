#include "pch.h"

#include "Framework/Managers/Device Manager/Core/DeviceManager.h"

#include "Framework\\Managers\\Graphics Manager\\Toolkit\\DirectX 12\\RenderQueue.h"

Uniquis::DirectX12::RenderQueue::RenderQueue(std::vector<PipelineState<PipelineStateType::Rasterisation>>& pvPipelineStates, DescriptorHeap<DescriptorHeapType::CommonDescriptors>& pDescriptorHeap, ModelHeap& pModelHeap)

	: pModelHeap(&(pModelHeap)), pDescriptorHeap(&(pDescriptorHeap)), pvPipelineStates(&(pvPipelineStates))
{

}

Uniquis::DirectX12::RenderQueue::~RenderQueue()
{

}

void Uniquis::DirectX12::RenderQueue::bind(Object& pObject)
{
	this->vpObjects.emplace_back(&(pObject));

	unsigned __int16 ModelID = *(pObject.pModelID);
	
	bool bModelStored = false;

	for (unsigned __int16 i = 0; i < this->pModelHeap->vModelIDs.size(); i++)
	{
		if (this->pModelHeap->vModelIDs[i] == ModelID)
		{
			this->viAppropriateBuffers.push_back(this->pModelHeap->vModelIDs[i]);

			bModelStored = true;
		}
	}

	if (!(bModelStored))
	{
		
	}
}

void Uniquis::DirectX12::RenderQueue::bind(Text& pText)
{
	this->vpTexts.emplace_back(&(pText));
}

void Uniquis::DirectX12::RenderQueue::render(const CommandList& pCommandList)
{
	for (unsigned __int16 i = 0; i < this->vpObjects.size(); i++)
	{
		pCommandList->SetGraphicsRootDescriptorTable(2, this->pDescriptorHeap->getGPUHandleToDescriptor(this->pDescriptorHeap->vPartitionDescriptors[1].Begin + i));    // Constant Buffer

		pCommandList->SetGraphicsRootDescriptorTable(3, this->pDescriptorHeap->getGPUHandleToDescriptor(/*this->pDescriptorHeap->vPartitionDescriptors[2].Begin + i*/ 190));    // Texture

		pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pCommandList->IASetIndexBuffer(&(this->pModelHeap->vpIndexBuffers[this->viAppropriateBuffers[i]]->Descriptor));

		pCommandList->IASetVertexBuffers(0, 1, &(this->pModelHeap->vpVertexBuffers[this->viAppropriateBuffers[i]]->Descriptor));

		pCommandList->DrawIndexedInstanced(this->pModelHeap->vpIndexBuffers[this->viAppropriateBuffers[i]]->vIndices.size(), 1, 0, 0, 0);
	}

	for (unsigned __int16 i = 0; i < this->vpTexts.size(); i++)
	{
		pCommandList->SetPipelineState(*((*(this->pvPipelineStates))[1]));

		pCommandList->SetGraphicsRootDescriptorTable(3, this->pDescriptorHeap->getGPUHandleToDescriptor(/*this->pDescriptorHeap->vPartitionDescriptors[2].Begin + i*/ 190));




		pCommandList->SetGraphicsRootDescriptorTable(2, this->pDescriptorHeap->getGPUHandleToDescriptor(this->pDescriptorHeap->vPartitionDescriptors[1].Begin));

		pCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pCommandList->IASetIndexBuffer(&(this->pModelHeap->vpIndexBuffers[this->pModelHeap->vpIndexBuffers.size() - 1]->Descriptor));

		pCommandList->IASetVertexBuffers(0, 1, &(this->pModelHeap->vpVertexBuffers[this->pModelHeap->vpIndexBuffers.size() - 1]->Descriptor));

		pCommandList->DrawIndexedInstanced(this->pModelHeap->vpIndexBuffers[this->pModelHeap->vpIndexBuffers.size() - 1]->vIndices.size(), 1, 0, 0, 0);
	}
}