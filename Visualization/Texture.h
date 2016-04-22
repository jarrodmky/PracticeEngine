#ifndef IncludedVisuTextureH
#define IncludedVisuTextureH

//===========================================================================
// Filename:	Texture.h
// Author:		Jarrod MacKay
// Description:	API texture
//===========================================================================

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class System;

	class Spriter;
	class Texture
	{
		//Operations
	public:

		Texture();
		~Texture();

		//Methods
	public:

		void Initialize(System& p_System, const wchar_t* p_Filename);
		void Terminate();

		void BindVertexShader(System& p_System, u32 p_Index) const;
		void BindPixelShader(System& p_System, u32 p_Index) const;

		void UnbindVertexShader(System& p_System, u32 p_Index) const;
		void UnbindPixelShader(System& p_System, u32 p_Index) const;

		//Attributes
	private:

		friend Spriter;

		ID3D11ShaderResourceView* m_Texture;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuTextureH