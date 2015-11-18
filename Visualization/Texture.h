#ifndef IncludedVisuTextureH
#define IncludedVisuTextureH

//===========================================================================
// Filename:	Solid.h
// Author:		Jarrod MacKay
// Description:	Describes a mesh that is assumed to remain "stiff" but can
//				still undergo linear transformations
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

	class Texture
	{
		//Operations
	public:
		Texture();
		~Texture();
		

		//Methodsqq
	public:
		
		void Initialize(System& p_System, const wchar_t* p_Filename);
		void Terminate();
		
		void BindVertexShader(System& p_System, u32 p_Index);
		void BindPixelShader(System& p_System, u32 p_Index);

		//Attributes
	private:

	ID3D11ShaderResourceView* m_Texture;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuTextureH