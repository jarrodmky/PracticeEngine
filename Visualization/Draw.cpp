//===========================================================================
// Filename:	LinearColour.cpp
// Author:		Jarrod MacKay
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"
#include "Draw.h"
#include "System.h"
#include "Vertices.h"
#include "Shaders.h"
#include "Camera.h"

using namespace Mathematics;
using namespace Visualization;
using namespace Draw;


struct SimpleDrawBuffer
{
	Matrix44 transform;
};

//===========================================================================
// Implementation Declarations
//===========================================================================

namespace
{

class DrawImplementation
{
//Operators
public:

	DrawImplementation(::System& p_System);

	~DrawImplementation();

//Functions
public:
	void Initialize(u32 p_MaxVertices = 10000);
	void Terminate();

	//world space rendering
	void AddLineBetweenPoints(const Mathematics::Vector3& p_FirstPosition
						   , const Mathematics::Vector3& p_SecondPosition
						   , const Mathematics::LinearColour& p_Colour);

	void Render(const Camera& p_Camera);

private:

	::System& m_System;

	VertexShader<FlatVertex> m_VertexShader;

	PixelShader m_PixelShader;

	ConstantBuffer<SimpleDrawBuffer> m_ConstantBuffer;

	//ID3D11Buffer* m_VertexBuffer3D;

	//ID3D11Buffer* m_VertexBuffer2D;

	//FlatVertex* m_Vertices3D;

	//FlatVertex* m_Vertices2D;

	u32 m_MaxVertices;

	//u32 m_NumVertices3D;

	//u32 m_NumVertices2D;

	DynamicVertexBuffer<FlatVertex> m_VertexBuffer3D;

	DynamicVertexBuffer<FlatVertex> m_VertexBuffer2D;

	bool m_Initialized;
};

std::unique_ptr<DrawImplementation> m_Implementation;

//===========================================================================
// Implementation Definitions
//===========================================================================

DrawImplementation::DrawImplementation(::System& p_System)
	: m_System(p_System)
	, m_VertexShader(p_System)
	, m_PixelShader(p_System)
	, m_ConstantBuffer(p_System)
	, m_VertexBuffer3D(p_System)
	, m_VertexBuffer2D(p_System)
	, m_MaxVertices(0)
	, m_Initialized(false)
{}

DrawImplementation::~DrawImplementation()
{
	Assert(m_VertexBuffer3D.GetCapacity() == 0 && m_VertexBuffer2D.GetCapacity() == 0, "Simple drawing not terminated!");
}

void DrawImplementation::Initialize(u32 p_MaxVertices)
{
	Assert(!m_Initialized, "Already initialized!");

	m_VertexShader.Compile(L"../Data/Shaders/Draw.fx", "VS", "vs_4_0");
	m_PixelShader.Compile(L"../Data/Shaders/Draw.fx", "PS", "ps_4_0");
	m_ConstantBuffer.Allocate();

	//create line buffers
	m_VertexBuffer3D.Allocate(p_MaxVertices);
	m_VertexBuffer2D.Allocate(p_MaxVertices);

	m_MaxVertices = p_MaxVertices;

	m_Initialized = true;
}

void DrawImplementation::Terminate()
{
	Assert(m_Initialized, "Not initialized!");

	m_VertexBuffer2D.Free();
	m_VertexBuffer3D.Free();

	m_ConstantBuffer.Free();
	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Initialized = false;
}

void DrawImplementation::AddLineBetweenPoints(const Mathematics::Vector3& p_FirstPosition
					   , const Mathematics::Vector3& p_SecondPosition
					   , const Mathematics::LinearColour& p_Colour)
{
	Assert(m_VertexBuffer3D.GetNumberOfVertices() + 2 < m_MaxVertices, "No room for vertices!");

	if(m_VertexBuffer3D.GetNumberOfVertices() + 2 < m_MaxVertices)
	{
		m_VertexBuffer3D.Add(FlatVertex(p_FirstPosition, p_Colour));
		m_VertexBuffer3D.Add(FlatVertex(p_SecondPosition, p_Colour));
	}
}

void DrawImplementation::Render(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");
	
	Matrix44 invScreenSpace(ScreenToNDC(m_System.GetHeight(), m_System.GetWidth()).Transposition());
	
	SimpleDrawBuffer d;
	d.transform = (p_Camera.GetPerspectiveTransform() * p_Camera.GetWorldToViewTransform()).Transposition();
	m_ConstantBuffer.Set(&d);
	m_ConstantBuffer.BindToVertexShader(0);

	//set shaders
	m_VertexShader.Bind();
	m_PixelShader.Bind();

	//set buffers
	m_VertexBuffer2D.Bind();
	m_VertexBuffer3D.Bind();

	m_System.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_System.GetContext()->Draw(m_VertexBuffer3D.GetNumberOfVertices(), 0);

	m_VertexBuffer2D.Clear();
	m_VertexBuffer3D.Clear();
}

}

//===========================================================================
// Interface
//===========================================================================

void Visualization::Draw::Initialize(System& p_System, u32 p_MaxVertices)
{
	Assert(m_Implementation == nullptr, "Already initialized!");

	m_Implementation = std::make_unique<DrawImplementation>(p_System);

	m_Implementation->Initialize(p_MaxVertices);
}

void Visualization::Draw::Terminate()
{
	Assert(m_Implementation != nullptr, "Already terminated!");

	m_Implementation->Terminate();

	m_Implementation.reset();
}

//world space rendering
void Visualization::Draw::AddVector(const Mathematics::Vector3& p_Vector
	, const Mathematics::Vector3& p_Position
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddLineBetweenPoints(p_Position
										, p_Position + p_Vector
										, p_Colour);
}

void Visualization::Draw::AddVector(const Mathematics::Vector3& p_Vector
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddLineBetweenPoints(Zero3(), p_Vector, p_Colour);
}

void Visualization::Draw::AddSimplex(const Mathematics::Edge& p_Edge
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddLineBetweenPoints(p_Edge.First, p_Edge.Second, p_Colour);
}

void Visualization::Draw::AddFrame(const Mathematics::Frame& p_Frame, f32 p_Length)
{
	using namespace ColourPallet;
	AddVector(p_Frame.GetRight() * p_Length, p_Frame.GetPosition(), Red);
	AddVector(p_Frame.GetUp() * p_Length, p_Frame.GetPosition(), Green);
	AddVector(p_Frame.GetForward() * p_Length, p_Frame.GetPosition(), Blue);
}

void Visualization::Draw::AddCoordinateAxes()
{
	using namespace ColourPallet;
	m_Implementation->AddLineBetweenPoints(MakeVector(Maximum, Zero, Zero), MakeVector(Minimum, Zero, Zero), Red);
	m_Implementation->AddLineBetweenPoints(MakeVector(Zero, Maximum, Zero), MakeVector(Zero, Minimum, Zero), Green);
	m_Implementation->AddLineBetweenPoints(MakeVector(Zero, Zero, Maximum), MakeVector(Zero, Zero, Minimum), Blue);
}

void Visualization::Draw::Render(const Camera& p_Camera)
{
	m_Implementation->Render(p_Camera);
}