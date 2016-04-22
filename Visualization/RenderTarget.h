#ifndef IncludedVisuRenderTargetH
#define IncludedVisuRenderTargetH

//===========================================================================
// Filename:	RenderTarget.h
// Author:		Jarrod MacKay
// Description:	Describes a representation of the back buffer.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "System.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{

	class RenderTarget
	{
	//Definitions
	public:

		enum class Format
		{
			R_F16,
			RGBA_U8,
			RGBA_F16
		};

	//Operations
	public:

		RenderTarget(System& p_System);
		~RenderTarget();
		

	//Methods
	public:
		void Initialize(const u32 p_Width, const u32 p_Height, const Format p_Format);
		void Terminate();

		void BeginRender();
		void EndRender();

		void BindTexture(u32 p_Index);
		void UnbindTexture(u32 p_Index);

	//Attributes
	private:

		System& m_System;
		ID3D11ShaderResourceView* m_Texture;
		ID3D11RenderTargetView* m_Target;
		ID3D11DepthStencilView* m_Stencil;
		D3D11_VIEWPORT m_Viewport;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuTextureH