#ifndef IncludedVisuFont
#define IncludedVisuFont

//====================================================================================================
// Filename:	Font.h
// Created by:	Peter Chan
// Modified by: Jarrod MacKay
// Description:	Class for a 2D font.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace DirectX
{
	class SpriteFont;
}
namespace Visualization
{
	class Spriter;
	class System;
}

//====================================================================================================
// Namespace
//====================================================================================================

namespace Visualization
{
//====================================================================================================
// Class Declarations
//====================================================================================================

class Font
{
public:
	Font();
	~Font();

	void Initialize(System& p_System, const char* p_Filename);
	void Terminate();
	
	void QueueRender(const char* p_String, const Mathematics::Vector2& p_Position);
	void QueueRender(const wchar_t* p_String, const Mathematics::Vector2& p_Position);

	void Render(Spriter& p_Spriter);
	
private:
	NonCopyable(Font);

	typedef std::pair<std::wstring, Mathematics::Vector2> TextMarker;

	DirectX::SpriteFont* m_SpriteFont;

	std::vector<TextMarker> m_RenderQueue;
};

} // namespace Visualization

#endif // #ifndef IncludedVisuFont