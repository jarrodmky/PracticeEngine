#ifndef IncludedVisuDashboardH
#define IncludedVisuDashboardH

//===========================================================================
// Filename:	Dashboard.h
// Author:		Jarrod MacKay
// Description:	Keeps track of depth stencil, rasterizer and samplers.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Sampler.h"
#include "Tester.h"
#include "Rasterizer.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class System;

	class Dashboard
	{
	//Method
	public:

		Dashboard(System& p_System);
		~Dashboard();

		void Initialize();
		void Terminate();

		void SetDepthTest(const Tester::DepthTest p_DepthTest);
		void TestDepth(const bool p_ShouldTestForDepth);

		void SetRasterization(Rasterizer::CullMode p_Culling, Rasterizer::FillMode p_Filling);
		void SetWireframe();
		void SetSolid();

		void Bind();

		//Attributes
	private:

		Tester m_DepthStencil;
		Rasterizer m_Rasterizer;

		System& m_System;
		bool m_Initialized;
	};
}

#endif // #ifndef IncludedVisuDashboardH