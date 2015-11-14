#ifndef INCLUDED_SIEGE_CONSTANTBUFFER_H
#define INCLUDED_SIEGE_CONSTANTBUFFER_H

//====================================================================================================
// Filename:	ConstantBuffer.h
// Created by:	Peter Chan
// Description:	Class for a constant buffer.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

#include "System.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

namespace Visualization
{

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();

	void Initialize(System& gs, u32 bufferSize, const void* initData = nullptr);
	void Terminate();

	void Set(System& gs, const void* data) const;
	
	void BindVS(System& gs, u32 slot = 0) const;
	void BindGS(System& gs, u32 slot = 0) const;
	void BindPS(System& gs, u32 slot = 0) const;
	void BindCS(System& gs, u32 slot = 0) const;

private:
	ID3D11Buffer* mpBuffer;
};

//----------------------------------------------------------------------------------------------------

template <typename T>
class TypedConstantBuffer : public ConstantBuffer
{
public:
	void Initialize(System& gs)
	{
		ConstantBuffer::Initialize(gs, GetPaddedSize());
	}

	void Initialize(System& gs, const T& data)
	{
		ConstantBuffer::Initialize(gs, GetPaddedSize(), &data);
	}

	void Set(System& gs, const T& data) const
	{
		ConstantBuffer::Set(gs, &data);
	}

private:
	u32 GetPaddedSize() const
	{
		const u32 typeSize = sizeof(T);
		const u32 bufferSize = (typeSize % 16) ? ((typeSize / 16) + 1) * 16 : typeSize;
		return bufferSize;
	}
};

}

#endif // #ifndef INCLUDED_SIEGE_CONSTANTBUFFER_H