//====================================================================================================
// Filename:	ConstantBuffer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"
#include "ConstantBuffer.h"
#include "System.h"

using namespace Visualization;

//====================================================================================================
// Class Definitions
//====================================================================================================

ConstantBuffer::ConstantBuffer()
	: mpBuffer(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

ConstantBuffer::~ConstantBuffer()
{
	Assert(mpBuffer == nullptr, "[ConstantBuffer] Buffer not released!");
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Initialize(System& gs, u32 bufferSize, const void* initData)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof desc);
	desc.ByteWidth = bufferSize;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA subresourceData;
	D3D11_SUBRESOURCE_DATA* subresourceDataPtr = nullptr;
	if (initData != nullptr)
	{
		ZeroMemory(&subresourceData, sizeof(subresourceData));
		subresourceData.pSysMem = initData;
		subresourceDataPtr = &subresourceData;
	}

	gs.GetDevice()->CreateBuffer(&desc, subresourceDataPtr, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Terminate()
{
	ProperlyRelease(mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::Set(System& gs, const void* data) const
{
	gs.GetContext()->UpdateSubresource(mpBuffer, 0, nullptr, data, 0, 0);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindVS(System& gs, u32 slot) const
{
	gs.GetContext()->VSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindGS(System& gs, u32 slot) const
{
	gs.GetContext()->GSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindPS(System& gs, u32 slot) const
{
	gs.GetContext()->PSSetConstantBuffers(slot, 1, &mpBuffer);
}

//----------------------------------------------------------------------------------------------------

void ConstantBuffer::BindCS(System& gs, u32 slot) const
{
	gs.GetContext()->CSSetConstantBuffers(slot, 1, &mpBuffer);
}