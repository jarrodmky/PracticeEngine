#ifndef IncludedGameH
#define IncludedGameH

//===========================================================================
// Filename:	Game.h
// Author:		Jarrod MacKay
// Description:	Entry functions into the game loop.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include <Abstracts.h>
#include <Mathematics.h>
#include <Algorithms.h>
#include <Utilization.h>
#include <Visualization.h>
#include <Synchronization.h>

//===========================================================================
// Classes
//===========================================================================

class Game : public Synchronization::WindowedApp
{

//Operators
public:

	Game();

	virtual ~Game();

//Methods
private:

	virtual void OnInitialize();

	virtual void OnTerminate();

	virtual void OnUpdate(f32 p_DeltaTime);

	virtual void OnRender();

//Attributes
private:

	//game
	Utilization::System m_InputSystem;

	Utilization::InputState m_Controller;

	///////
	//scene
	///////
	Visualization::Camera m_Camera;
	Visualization::ConstantBuffer<Visualization::LightingBuffer> m_LightingBuffer;
	Mathematics::MatrixStack m_Matrix;

	//skybox
	Visualization::DepthStencil m_DepthTestDisable;
	Visualization::DepthStencil m_DepthTestEnable;
	Visualization::Solid m_Skyshape;
	Visualization::Material m_SkyshapeMat;

	//terrain
	Visualization::Solid m_Terrain;
	Visualization::Material m_TerrainMat;

	//moon
	Visualization::BumpedSolid m_moon;
	Visualization::Material m_moonMat;
	Visualization::Texture m_moonBump;

	//earth
	Visualization::BumpedSolid m_earth;
	Visualization::Material m_earthMat;
	Visualization::Texture m_earthBump;

	//mars
	Visualization::BumpedSolid m_mars;
	Visualization::Material m_marsMat;
	Visualization::Texture m_marsBump;

	//shader
	Visualization::VertexShader<Visualization::ShadedVertex> m_shadedVS;
	Visualization::PixelShader m_shadedPS;
	Visualization::VertexShader<Visualization::BumpedVertex> m_bumpedVS;
	Visualization::PixelShader m_bumpedPS;
};

#endif //#ifndef IncludedGameH