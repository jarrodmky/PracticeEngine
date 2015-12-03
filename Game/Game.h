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

};

#endif //#ifndef IncludedGameH