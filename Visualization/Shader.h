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
#include "Vertex.h"
#include "Util.h"

namespace Visualization
{

//===========================================================================
// Classes
//===========================================================================
	

	//==========
	// Shader
	//==========

	class Shader
	{
	//Attributes
	protected:

		System& m_System;
		std::string m_EntryName;
		std::string m_ShaderLevel;
		std::wstring m_FileName;

	//Operations
	public:

		Shader(System& p_System, const LPCSTR p_EntryName, const LPCSTR p_ShaderLevel, const LPCWSTR p_FileName);

		virtual ~Shader();

	private:

		NonCopyable(Shader);
		
	//Methods
	public:
		
		void Compile();

		virtual void Release() = 0;

		virtual void Bind() const = 0;

		virtual void Unbind() const = 0;

	private:

		virtual void SetSpecificShader(ID3DBlob* p_Blob) = 0;
	};

	
	//==========
	// Vertex Shader
	//==========

	template <typename t_VertexType>
	class VertexShader : public Shader
	{
	//Attributes
	private:

		ID3D11InputLayout* m_InputLayout;
		ID3D11VertexShader* m_ShaderPointer;

	//Operations
	public:

		VertexShader(System& p_System, const LPCWSTR p_FileName);

		virtual ~VertexShader();

	//Methods
	public:

		virtual void Release() override;

		virtual void Bind() const override;

		virtual void Unbind() const override;

	private:

		virtual void SetSpecificShader(ID3DBlob* p_Blob) override;
	};


	//==========
	// Geometry Shader
	//==========

	class GeometryShader : public Shader
	{
	//Attributes
	private:

		ID3D11GeometryShader* m_ShaderPointer;

	//Operations
	public:

		GeometryShader(System& p_System, const LPCWSTR p_FileName);

		virtual ~GeometryShader();

	//Methods
	public:

		virtual void Release() override;

		virtual void Bind() const override;

		virtual void Unbind() const override;

	private:

		virtual void SetSpecificShader(ID3DBlob* p_Blob) override;
	};


	//==========
	// Pixel Shader
	//==========
	
	class PixelShader : public Shader
	{
	//Attributes
	private:
		
		ID3D11PixelShader* m_ShaderPointer;

	//Operations
	public:

		PixelShader(System& p_System, const LPCWSTR p_FileName);

		virtual ~PixelShader();

	//Methods
	public:

		virtual void Release() override;

		virtual void Bind() const override;

		virtual void Unbind() const override;

	private:

		virtual void SetSpecificShader(ID3DBlob* p_Blob) override;
	};

#include "Shader.inl"
#include "SpecificShader.inl"
}

#endif // #ifndef IncludedVisuShadersH