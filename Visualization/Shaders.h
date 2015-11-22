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

		ID3D11InputLayout* m_InputLayout;
		ID3D11VertexShader* m_ShaderPointer;

	//Operations
	public:

		VertexShader()
			: m_InputLayout(nullptr)
			, m_ShaderPointer(nullptr)
		{}

		~VertexShader()
		{
			Assert(nullptr == m_ShaderPointer && nullptr == m_InputLayout, "Not released!");
		}

	private:

		NonCopyable(VertexShader);

	//Methods
	public:

		void Compile(LPCWSTR p_FileName, ID3D11Device* p_Device);

		void Release();

		void Bind(ID3D11DeviceContext* p_Context) const;

	private:

		static void CompileFileIntoShader(ID3DBlob*& p_ShaderBlob, LPCWSTR p_FileName, LPCSTR p_EntryPoint, LPCSTR p_Target);
	};


	
	class PixelShader
	{
	//Attributes
	private:

		ID3D11PixelShader* m_ShaderPointer;

	//Operations
	public:

		PixelShader()
			: m_ShaderPointer(nullptr)
		{}

		~PixelShader()
		{
			Assert(nullptr == m_ShaderPointer, "Not released!");
		}

	private:

		NonCopyable(PixelShader);

	//Methods
	public:

		void Compile(LPCWSTR p_FileName, ID3D11Device* p_Device);

		void Release();

		void Bind(ID3D11DeviceContext* p_Context) const;

	private:

		static void CompileFileIntoShader(ID3DBlob*& p_ShaderBlob, LPCWSTR p_FileName, LPCSTR p_EntryPoint, LPCSTR p_Target);
	};

}

#include "Shaders.inl"

#endif // #ifndef IncludedVisuShadersH