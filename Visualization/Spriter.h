#ifndef IncludedVisuSpriterH
#define IncludedVisuSpriterH

//===========================================================================
// Filename:	Spriter.h
// Author:		Jarrod MacKay
// Description:	Renders sprites and 2D images
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

//===========================================================================
// Classes
//===========================================================================

namespace DirectX
{
	class SpriteBatch;
}

namespace Visualization
{
	class Texture;
	class System;

	class Spriter
	{
	public:
		Spriter();
		~Spriter();

		void Initialize(System& p_System);
		void Terminate();

		void BeginRender();
		void EndRender();

		void Draw(const Texture& p_Texture, const Mathematics::Vector2& p_Position);

	private:

		NonCopyable(Spriter);

		friend class Font;

		DirectX::SpriteBatch* m_SpriteBatch;
	};
}

#endif // #ifndef IncludedVisuSpriterH