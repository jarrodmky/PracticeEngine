#ifndef IncludedVisuDepthMapH
#define IncludedVisuDepthMapH

//===========================================================================
// Filename:	DepthMap.h
// Author:		Jarrod MacKay
// Description:	Describes a representation of the depth buffer
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

	class DepthMap
	{
	//Operations
	public:

		DepthMap(System& p_System);
		~DepthMap();
		

	//Methods
	public:
		void Initialize(const u32 p_Width, const u32 p_Height);
		void Terminate();

		void BeginRender();
		void EndRender();

		void BindPixelShader(u32 p_Index);
		void UnbindPixelShader(u32 p_Index);

	//Attributes
	private:

		System& m_System;
		ID3D11ShaderResourceView* m_ShaderResourceView;
		ID3D11DepthStencilView* m_DepthStencilViewer;
		D3D11_VIEWPORT m_Viewport;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuTextureH