#ifndef IncludedVisuShadersH
#define IncludedVisuShadersH

//===========================================================================
// Filename:	Shaders.h
// Author:		Jarrod MacKay
// Description:	Used to import api-agnostic shaders
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "System.h"
#include "MeshUtil.h"

namespace Visualization
{

//===========================================================================
// Classes
//===========================================================================

	template <typename t_VertexType>
	class VertexShader
	{
	//Attributes
	private:

		System& m_System;
		ID3D11InputLayout* m_InputLayout;
		ID3D11VertexShader* m_ShaderPointer;

	//Operations
	public:

		VertexShader(System& p_System);

		~VertexShader();

	private:

		NonCopyable(VertexShader);

	//Methods
	public:

		void Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel);

		void Release();

		void Bind() const;
	};

	class GeometryShader
	{
	//Attributes
	private:

		System& m_System;
		ID3D11GeometryShader* m_ShaderPointer;

	//Operations
	public:

		GeometryShader(System& p_System);

		~GeometryShader();

	private:

		NonCopyable(GeometryShader);

	//Methods
	public:

		void Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel);

		void Release();

		void Bind() const;

		void Unbind() const;
	};
	
	class PixelShader
	{
	//Attributes
	private:
		
		System& m_System;
		ID3D11PixelShader* m_ShaderPointer;

	//Operations
	public:

		PixelShader(System& p_System);

		~PixelShader();

	private:

		NonCopyable(PixelShader);

	//Methods
	public:

		void Compile(LPCWSTR p_FileName, LPCSTR p_EntryName, LPCSTR p_ShaderLevel);

		void Release();

		void Bind() const;
	};

}

#include "Shaders.inl"

#endif // #ifndef IncludedVisuShadersH