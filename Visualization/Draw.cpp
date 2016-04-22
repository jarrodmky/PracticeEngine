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
#include "GraphicBasic.h"
#include "Renderer.h"

using namespace Mathematics;
using namespace Visualization;
using namespace Draw;

//===========================================================================
// Implementation Declarations
//===========================================================================

namespace
{

const u32 gridGraduations = 30;


class DrawImplementation
{
//Operators
public:

	DrawImplementation(::System& p_System);

	~DrawImplementation();

//Functions
public:
	void Initialize(u32 p_MaxVertices = 100000);
	void Terminate();

	//world space rendering
	void AddEdge(const Mathematics::Vector3& p_FirstPosition
						   , const Mathematics::Vector3& p_SecondPosition
						   , const Mathematics::LinearColour& p_Colour);

	void AddLine(const Mathematics::Vector3& p_Direction
		, const Mathematics::LinearColour& p_Colour);

	void AddCube(const Mathematics::Vector3& p_Centre
		, const Mathematics::Quaternion& p_Rotation
		, const Mathematics::scalar p_Width
		, const Mathematics::LinearColour& p_Colour);

	void Render(const Camera& p_Camera);

private:

	::System& m_System;

	FlatVertexRenderer m_Renderer3D;

	u32 m_MaxVertices;

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
	, m_Renderer3D(p_System)
	, m_VertexBuffer3D(p_System)
	, m_VertexBuffer2D(p_System)
	, m_MaxVertices(0)
	, m_Initialized(false)
{}

DrawImplementation::~DrawImplementation()
{}

void DrawImplementation::Initialize(u32 p_MaxVertices)
{
	Assert(!m_Initialized, "Already initialized!");

	m_Renderer3D.Initialize();

	//create line buffers
	m_VertexBuffer3D.Allocate(nullptr, p_MaxVertices);
	m_VertexBuffer2D.Allocate(nullptr, p_MaxVertices);

	m_MaxVertices = p_MaxVertices;

	m_Initialized = true;
}

void DrawImplementation::Terminate()
{
	Assert(m_Initialized, "Not initialized!");

	m_VertexBuffer2D.Free();
	m_VertexBuffer3D.Free();

	m_Renderer3D.Terminate();

	m_Initialized = false;
}

void DrawImplementation::AddEdge(const Mathematics::Vector3& p_FirstPosition
	, const Mathematics::Vector3& p_SecondPosition
	, const Mathematics::LinearColour& p_Colour)
{
	m_VertexBuffer3D.Add(FlatVertex(p_FirstPosition, p_Colour));
	m_VertexBuffer3D.Add(FlatVertex(p_SecondPosition, p_Colour));
}

void DrawImplementation::AddLine(const Mathematics::Vector3& p_Direction
	, const Mathematics::LinearColour& p_Colour)
{
	Vector4 dir = MakeAffineVector(p_Direction);
	m_VertexBuffer3D.Add(FlatVertex(dir, p_Colour));
	m_VertexBuffer3D.Add(FlatVertex(-dir, p_Colour));
}

void DrawImplementation::AddCube(const Mathematics::Vector3& p_Centre
	, const Mathematics::Quaternion& p_Rotation
	, const Mathematics::scalar p_Width
	, const Mathematics::LinearColour& p_Colour)
{
	//init positions
	Abstracts::Array<Vector3, 2, 2, 2> cube;
	const scalar halfWidth = p_Width * 0.5f;

	cube(0, 0, 0) = -halfWidth * Ones3();
	cube(1, 1, 1) = halfWidth * Ones3();

	cube(1, 0, 0) = -halfWidth * Ones3() + p_Width * I();
	cube(0, 1, 1) = halfWidth * Ones3() - p_Width * I();

	cube(0, 1, 0) = -halfWidth * Ones3() + p_Width * J();
	cube(1, 0, 1) = halfWidth * Ones3() - p_Width * J();

	cube(0, 0, 1) = -halfWidth * Ones3() + p_Width * K();
	cube(1, 1, 0) = halfWidth * Ones3() - p_Width * K();

	p_Rotation.Rotate(cube(0, 0, 0));
	p_Rotation.Rotate(cube(0, 0, 1));
	p_Rotation.Rotate(cube(0, 1, 0));
	p_Rotation.Rotate(cube(0, 1, 1));
	p_Rotation.Rotate(cube(1, 0, 0));
	p_Rotation.Rotate(cube(1, 0, 1));
	p_Rotation.Rotate(cube(1, 1, 0));
	p_Rotation.Rotate(cube(1, 1, 1));

	cube(0, 0, 0) += p_Centre;
	cube(0, 0, 1) += p_Centre;
	cube(0, 1, 0) += p_Centre;
	cube(0, 1, 1) += p_Centre;
	cube(1, 0, 0) += p_Centre;
	cube(1, 0, 1) += p_Centre;
	cube(1, 1, 0) += p_Centre;
	cube(1, 1, 1) += p_Centre;

	//draw edges
	AddEdge(cube(0, 0, 0), cube(0, 0, 1), p_Colour);
	AddEdge(cube(0, 0, 1), cube(0, 1, 1), p_Colour);
	AddEdge(cube(0, 1, 1), cube(0, 1, 0), p_Colour);
	AddEdge(cube(0, 1, 0), cube(0, 0, 0), p_Colour);

	AddEdge(cube(1, 0, 0), cube(1, 0, 1), p_Colour);
	AddEdge(cube(1, 0, 1), cube(1, 1, 1), p_Colour);
	AddEdge(cube(1, 1, 1), cube(1, 1, 0), p_Colour);
	AddEdge(cube(1, 1, 0), cube(1, 0, 0), p_Colour);

	AddEdge(cube(0, 0, 0), cube(1, 0, 0), p_Colour);
	AddEdge(cube(0, 0, 1), cube(1, 0, 1), p_Colour);
	AddEdge(cube(0, 1, 0), cube(1, 1, 0), p_Colour);
	AddEdge(cube(0, 1, 1), cube(1, 1, 1), p_Colour);
}

void DrawImplementation::Render(const Camera& p_Camera)
{
	Assert(m_Initialized, "Not initialized!");
	Assert(m_VertexBuffer3D.Size() % 2 == 0, "LineList cant have uneven amount of vertices!")
		Time("SimpleDrawRender");

	Matrix44 invScreenSpace(MakeNormalizedProjection(m_System.GetHeight(), m_System.GetWidth()).Transposition());
	
	//3d draw
	m_VertexBuffer3D.Update();
	m_Renderer3D.StartRendering(p_Camera);
	m_Renderer3D.Render(m_VertexBuffer3D, TopologyIndexing::LineList);
	m_Renderer3D.StopRendering();
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

	m_Implementation.reset(nullptr);
}

//world space rendering
void Visualization::Draw::AddVector(const Mathematics::Vector3& p_Vector
	, const Mathematics::Vector3& p_Position
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddEdge(p_Position, p_Position + p_Vector, p_Colour);
}

void Visualization::Draw::AddVector(const Mathematics::Vector3& p_Vector
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddEdge(Zero3(), p_Vector, p_Colour);
}

void Visualization::Draw::AddSimplex(const Mathematics::Edge3& p_Edge
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddEdge(p_Edge.First(), p_Edge.Second(), p_Colour);
}

void  Visualization::Draw::AddCube(const Mathematics::Vector3& p_Centre
	, const Mathematics::Quaternion& p_Rotation
	, const Mathematics::scalar p_Width
	, const Mathematics::LinearColour& p_Colour)
{
	m_Implementation->AddCube(p_Centre, p_Rotation, p_Width, p_Colour);
}

void Visualization::Draw::AddBox(const Mathematics::AABB3& p_Box
			, const Mathematics::LinearColour& p_Colour)
{
	Vector3 mXmYmZ(p_Box.Centre + p_Box.Extents * MakeVector(-Unity, -Unity, -Unity));
	Vector3 mXmYMZ(p_Box.Centre + p_Box.Extents * MakeVector(-Unity, -Unity, Unity));
	Vector3 mXMYmZ(p_Box.Centre + p_Box.Extents * MakeVector(-Unity, Unity, -Unity));
	Vector3 mXMYMZ(p_Box.Centre + p_Box.Extents * MakeVector(-Unity, Unity, Unity));
	Vector3 MXmYmZ(p_Box.Centre + p_Box.Extents * MakeVector(Unity, -Unity, -Unity));
	Vector3 MXmYMZ(p_Box.Centre + p_Box.Extents * MakeVector(Unity, -Unity, Unity));
	Vector3 MXMYmZ(p_Box.Centre + p_Box.Extents * MakeVector(Unity, Unity, -Unity));
	Vector3 MXMYMZ(p_Box.Centre + p_Box.Extents * MakeVector(Unity, Unity, Unity));

	//min corner
	m_Implementation->AddEdge(mXmYmZ, mXmYMZ, p_Colour);
	m_Implementation->AddEdge(mXmYmZ, mXMYmZ, p_Colour);
	m_Implementation->AddEdge(mXmYmZ, MXmYmZ, p_Colour);

	//maxXmaxY
	//m_Implementation->AddLineBetweenPoints(MXMYmZ, mXmYmZ, p_Colour);
	//m_Implementation->AddLineBetweenPoints(MXMYmZ, mXmYmZ, p_Colour);
	//m_Implementation->AddLineBetweenPoints(MXMYmZ, mXmYmZ, p_Colour);
	//
	////maxXmaxY
	//m_Implementation->AddLineBetweenPoints(mXmYmZ, mXmYMZ, p_Colour);
	//m_Implementation->AddLineBetweenPoints(mXmYmZ, mXmYMZ, p_Colour);
	//m_Implementation->AddLineBetweenPoints(mXmYmZ, mXmYMZ, p_Colour);

	//max corner
	m_Implementation->AddEdge(MXMYMZ, MXMYmZ, p_Colour);
	m_Implementation->AddEdge(MXMYMZ, MXmYMZ, p_Colour);
	m_Implementation->AddEdge(MXMYMZ, mXMYMZ, p_Colour);
}

void Visualization::Draw::AddFrame(const Mathematics::Frame& p_Frame, f32 p_Length)
{
	using namespace ColourPallet;
	AddVector(p_Frame.GetRight() * p_Length, p_Frame.GetPosition(), Red);
	AddVector(p_Frame.GetUp() * p_Length, p_Frame.GetPosition(), Green);
	//AddVector(p_Frame.GetForward() * p_Length, p_Frame.GetPosition(), Blue); //openGL neg Z is forward
	AddVector(-p_Frame.GetForward() * p_Length, p_Frame.GetPosition(), Blue); //Direct3D pos Z is forward
}

void Visualization::Draw::AddLine(const Mathematics::Line3& p_Line, const Mathematics::LinearColour& p_Colour)
{
	using namespace ColourPallet;
	m_Implementation->AddLine(p_Line.Direction(), p_Colour);
}

void Visualization::Draw::AddCoordinateAxes()
{
	using namespace Mathematics;
	using namespace ColourPallet;
	m_Implementation->AddLine(I(), Red);
	m_Implementation->AddLine(J(), Green);
	m_Implementation->AddLine(K(), Blue);
}
		
void Visualization::Draw::AddCoordinatePlaneXZ()
{
	Halt("Too slow!");

	using namespace Mathematics;
	using namespace ColourPallet;

	const scalar dGrad = 10.0f / static_cast<scalar>(gridGraduations);
	Vector3 posCursor = Zero3();
	Vector3 negCursor = Zero3();

	//draw Z graduations
	for(u32 i = 0; i < gridGraduations; ++i)
	{
		AddLine(Line3(posCursor += dGrad*I(), K()), Blue);
		AddLine(Line3(negCursor -= dGrad*I(), K()), Blue);
	}

	//draw X graduations
	posCursor = Zero3();
	negCursor = Zero3();
	for(u32 i = 0; i < gridGraduations; ++i)
	{
		AddLine(Line3(posCursor += dGrad*K(), I()), Red);
		AddLine(Line3(negCursor -= dGrad*K(), I()), Red);
	}
}

void Visualization::Draw::AddCircle(const Mathematics::Vector3& p_Centre
									, const Mathematics::Vector3& p_Normal
									, const Mathematics::scalar p_Radius
									, const Mathematics::LinearColour& p_Colour)
{
	Halt("Unimplemanted!");
}

void Visualization::Draw::Render(const Camera& p_Camera)
{
	m_Implementation->Render(p_Camera);
}