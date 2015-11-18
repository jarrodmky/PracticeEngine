#ifndef IncludedVisuSamplerH
#define IncludedVisuSamplerH

//===========================================================================
// Filename:	Sampler.h
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


	class Sampler
	{
	public:
	enum class Filter : u32
	{
		Point,
		Linear,
		Anisotropic
	};

	enum class AddressMode
	{
		Border,
		Clamp,
		Mirror,
		Wrap
	};
		//Operations
	public:
		Sampler();
		~Sampler();
		

		//Methods
	public:
		
		void Initialize(System& p_System, Filter p_Filter, AddressMode p_AddressMode);
		void Terminate();
		
		void BindVertexShader(System& p_System, u32 p_Index);
		void BindGeometryShader(System& p_System, u32 p_Index);
		void BindPixelShader(System& p_System, u32 p_Index);

		//Attributes
	private:

	ID3D11SamplerState* m_Sampler;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuSamplerH