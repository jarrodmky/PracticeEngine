#ifndef IncludedVisuTesterH
#define IncludedVisuTesterH

//===========================================================================
// Filename:	Tester.h
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

	class Tester
	{
	public:
	enum class DepthTest
	{
		None,
		Default,
		AdditiveBlend
	};

	//Operations
	public:
		Tester();
		~Tester();
		

	//Methods
	public:
		
		void Initialize(System& p_System, DepthTest p_DepthTest);
		void Terminate();
		
		void BindToOutput(System& p_System);

	//Attributes
	private:

	ID3D11DepthStencilState* m_DepthStencilState;

	};

} // namespace Visualization

#endif //#ifndef IncludedVisuTesterH