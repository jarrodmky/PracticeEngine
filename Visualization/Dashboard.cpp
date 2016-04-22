//===========================================================================
// Filename:	Dashboard.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include <Mathematics.h>
#include "Dashboard.h"

using namespace Mathematics;
using namespace Visualization;

//===========================================================================
// Definitions
//===========================================================================

Dashboard::Dashboard(System& p_System)
: m_DepthStencil()
, m_Rasterizer()
, m_System(p_System)
, m_Initialized(false)
{}

Dashboard::~Dashboard()
{
	Assert(!m_Initialized, "Still initialized!");
}

void Dashboard::Initialize()
{
	Assert(!m_Initialized, "Already initialized!");

	m_DepthStencil.Initialize(m_System, Tester::DepthTest::Default);

	m_Rasterizer.Initialize(m_System, Rasterizer::CullMode::CounterClockwise, Rasterizer::FillMode::Solid);

	m_Initialized = true;
}

void Dashboard::Terminate()
{
	Assert(m_Initialized, "Not initialized!");

	m_Initialized = false;

	m_Rasterizer.Terminate();
	m_DepthStencil.Terminate();
}

void Dashboard::SetDepthTest(const Tester::DepthTest p_DepthTest)
{
	Assert(m_Initialized, "Not initialized!");
	Time("SetDepthTest");
	m_DepthStencil.Terminate();
	m_DepthStencil.Initialize(m_System, p_DepthTest);
}

void Dashboard::TestDepth(const bool p_ShouldTestForDepth)
{
	if (p_ShouldTestForDepth)
	{
		SetDepthTest(Tester::DepthTest::Default);
	}
	else
	{
		SetDepthTest(Tester::DepthTest::None);
	}
}

void Dashboard::SetRasterization(Rasterizer::CullMode p_Culling, Rasterizer::FillMode p_Filling)
{
	Assert(m_Initialized, "Not initialized!");
	Time("SetRasterization");
	m_Rasterizer.Terminate();
	m_Rasterizer.Initialize(m_System, p_Culling, p_Filling);
}

void Dashboard::SetWireframe()
{
	SetRasterization(Rasterizer::CullMode::CounterClockwise, Rasterizer::FillMode::Wireframe);
}

void Dashboard::SetSolid()
{
	SetRasterization(Rasterizer::CullMode::CounterClockwise, Rasterizer::FillMode::Solid);
}

void Dashboard::Bind()
{
	Assert(m_Initialized, "Not initialized!");
	m_Rasterizer.Bind(m_System);
	m_DepthStencil.BindToOutput(m_System);
}