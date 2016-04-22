#ifndef IncludedVisuRasterizerH
#define IncludedVisuRasterizerH

//===========================================================================
// Filename:	Rasterizer.h
// Author:		Jarrod MacKay
// Description:	Allows control of depth testing.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class System;

	class Rasterizer
	{
	public:
	enum class CullMode
	{
		None,
		Clockwise,
		CounterClockwise
	};

	enum class FillMode
	{
		Wireframe,
		Solid
	};

	//Operations
	public:
		Rasterizer();
		~Rasterizer();
		

	//Methods
	public:
		
		void Initialize(System& p_System, CullMode p_CullMode, FillMode p_FillMode);
		void Terminate();
		
		void Bind(System& p_System);

	//Attributes
	private:

		ID3D11RasterizerState* m_RasterizerState;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuRasterizerH