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
#include "ConstantBuffer.h"
#include "Camera.h"

using namespace Mathematics;
using namespace Visualization;
using namespace Draw;


struct SimpleDrawBuffer
{
	Matrix transform;
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
	void AddLineBetweenPoints(const Mathematics::Vector& p_FirstPosition
						   , const Mathematics::Vector& p_SecondPosition
						   , const Mathematics::LinearColour& p_Colour);

	void Render(const Camera& p_Camera);

private:

	::System& m_System;

	VertexShader<FlatVertex> m_VertexShader;

	PixelShader m_PixelShader;

	TypedConstantBuffer<SimpleDrawBuffer> m_ConstantBuffer;

	ID3D11Buffer* m_VertexBuffer3D;

	ID3D11Buffer* m_VertexBuffer2D;

	FlatVertex* m_Vertices3D;

	FlatVertex* m_Vertices2D;

	u32 m_MaxVertices;

	u32 m_NumVertices3D;

	u32 m_NumVertices2D;

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
	, m_ConstantBuffer()
	, m_VertexBuffer3D(nullptr)
	, m_VertexBuffer2D(nullptr)
	, m_Vertices3D(nullptr)
	, m_Vertices2D(nullptr)
	, m_MaxVertices(0)
	, m_NumVertices3D(0)
	, m_NumVertices2D(0)
	, m_Initialized(false)
{}

DrawImplementation::~DrawImplementation()
{
	Assert(m_Vertices2D == nullptr && m_Vertices3D == nullptr, "Simple drawing not terminated!");
}

void DrawImplementation::Initialize(u32 p_MaxVertices)
{
	Assert(!m_Initialized, "Already initialized!");

	m_VertexShader.Compile(L"../Data/Shaders/Draw.fx", "VS", "vs_4_0");
	m_PixelShader.Compile(L"../Data/Shaders/Draw.fx", "PS", "ps_4_0");
	m_ConstantBuffer.Initialize(m_System);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = p_MaxVertices * sizeof(FlatVertex);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bd.MiscFlags = 0;

	//vertex buffer for 2/3d lines
	m_System.GetDevice()->CreateBuffer(&bd, nullptr, &m_VertexBuffer3D);
	m_System.GetDevice()->CreateBuffer(&bd, nullptr, &m_VertexBuffer2D);

	//create line buffers
	m_Vertices3D = new FlatVertex[p_MaxVertices];
	m_Vertices2D = new FlatVertex[p_MaxVertices];

	m_MaxVertices = p_MaxVertices;

	m_NumVertices3D = 0;

	m_NumVertices2D = 0;

	m_Initialized = true;
}

void DrawImplementation::Terminate()
{
	Assert(m_Initialized, "Not initialized!");

	ProperlyDeleteArray(m_Vertices2D);
	ProperlyDeleteArray(m_Vertices3D);

	ProperlyRelease(m_VertexBuffer2D);
	ProperlyRelease(m_VertexBuffer3D);

	m_ConstantBuffer.Terminate();
	m_PixelShader.Release();
	m_VertexShader.Release();

	m_Initialized = false;
}

void DrawImplementation::AddLineBetweenPoints(const Mathematics::Vector& p_FirstPosition
					   , const Mathematics::Vector& p_SecondPosition
					   , const Mathematics::LinearColour& p_Colour)
{
	Assert(m_NumVertices3D + 2 < m_MaxVertices, "No room for vertices!");

	if(m_NumVertices3D + 2 < m_MaxVertices)
	{
		m_Vertices3D[m_NumVertices3D++] = FlatVertex(p_FirstPosition, p_Colour);
		m_Vertices3D[m_NumVertices3D++] = FlatVertex(p_SecondPosition, p_Colour);
	}
}

void DrawImplementation::Render(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");

	u32 stride = sizeof(FlatVertex);
	u32 offset = 0;

	//draw 3d lines
	D3D11_MAPPED_SUBRESOURCE mappedRes;
	m_System.GetContext()->Map(m_VertexBuffer3D, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedRes);
	memcpy(mappedRes.pData, m_Vertices3D, m_NumVertices3D * stride);
	m_System.GetContext()->Unmap(m_VertexBuffer3D, 0);

	Matrix invScreenSpace(ScreenToNDC(m_System.GetHeight(), m_System.GetWidth()).Transposition());
	
	SimpleDrawBuffer d;
	d.transform = (p_Camera.GetPerspectiveTransform(m_System) * p_Camera.GetWorldToViewTransform()).Transposition();
	m_ConstantBuffer.Set(m_System, d);
	m_ConstantBuffer.BindVS(m_System, 0);

	//set shaders
	m_VertexShader.Bind();
	m_PixelShader.Bind();

	m_System.GetContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer3D, &stride, &offset);
	m_System.GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
	m_System.GetContext()->Draw(m_NumVertices3D, 0);

	m_NumVertices3D = 0;

	//draw 2D lines
	m_NumVertices2D = 0;
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
void Visualization::Draw::AddVector(const Mathematics::Vector& p_Vector
	, const Mathematics::Point& p_Position
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddLineBetweenPoints(p_Position.PositionVector()
										, (p_Position + p_Vector).PositionVector()
										, p_Colour);
}

void Visualization::Draw::AddVector(const Mathematics::Vector& p_Vector
	, const Mathematics::LinearColour& p_Colour)
{
	using namespace ConstantVectors;
	m_Implementation->AddLineBetweenPoints(Zero, p_Vector, p_Colour);
}

void Visualization::Draw::AddSimplex(const Mathematics::Edge& p_Edge
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddLineBetweenPoints(p_Edge.First.PositionVector(), p_Edge.Second.PositionVector(), p_Colour);
}

void Visualization::Draw::AddFrame(const Mathematics::Frame& p_Frame, f32 p_Length)
{
	using namespace ConstantColours;
	AddVector(p_Frame.GetLeft() * p_Length, p_Frame.GetPosition(), Red);
	AddVector(p_Frame.GetUp() * p_Length, p_Frame.GetPosition(), Green);
	AddVector(p_Frame.GetForward() * p_Length, p_Frame.GetPosition(), Blue);
}

void Visualization::Draw::AddCoordinateAxes()
{
	using namespace ConstantScalars;
	using namespace ConstantColours;
	m_Implementation->AddLineBetweenPoints(Vector(Maximum, Zero, Zero), Vector(Minimum, Zero, Zero), Red);
	m_Implementation->AddLineBetweenPoints(Vector(Zero, Maximum, Zero), Vector(Zero, Minimum, Zero), Green);
	m_Implementation->AddLineBetweenPoints(Vector(Zero, Zero, Maximum), Vector(Zero, Zero, Minimum), Blue);
}

void Visualization::Draw::Render(const Camera& p_Camera)
{
	m_Implementation->Render(p_Camera);
}