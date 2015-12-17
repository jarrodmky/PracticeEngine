#ifndef IncludedVisuBlendH
#define IncludedVisuBlendH

//===========================================================================
// Filename:	Blend.h
// Author:		Jarrod MacKay
// Description:	Allows control of blending between render targets.
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


	class Blend
	{
	public:
	enum class BlendMethod
	{
		Default,
		Additive
	};

	//Operations
	public:
		Blend();
		~Blend();
		

	//Methods
	public:
		
		void Initialize(System& p_System, BlendMethod p_BlendMethod);
		void Terminate();
		
		void BindToOutput(System& p_System, u32 p_Index);

	//Attributes
	private:

		ID3D11BlendState* m_Blend;
	};

} // namespace Visualization

#endif //#ifndef IncludedVisuBlendH