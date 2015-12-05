#ifndef IncludedVisuDepthStencilH
#define IncludedVisuDepthStencilH

//===========================================================================
// Filename:	DepthStencil.h
// Author:		Jarrod MacKay
// Description:	Allows control of depth testing.
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


	class DepthStencil
	{
	public:
	enum class DepthTest
	{
		None,
		Default,
		Read
	};

	//Operations
	public:
		DepthStencil();
		~DepthStencil();
		

	//Methods
	public:
		
		void Initialize(System& p_System, DepthTest p_DepthTest);
		void Terminate();
		
		void BindToOutput(System& p_System, u32 p_Index);

	//Attributes
	private:

	ID3D11DepthStencilState* m_DepthStencil;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuDepthStencilH