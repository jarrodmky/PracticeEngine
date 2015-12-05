#ifndef IncludedVisTerrainH
#define IncludedVisTerrainH

//===========================================================================
// Filename:	Terrain.h
// Author:		Jarrod MacKay
// Description:	Describes a mesh that is assumed to remain "stiff" but can
//				still undergo linear transformations
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>
#include <Serialization.h>
#include "System.h"
#include "Solid.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class Terrain
	{
	//Attributes
	private:

		System& m_System;

		Solid m_Mesh;

		//Lightmap

	//Operators
	public:

		Terrain(System& p_System);

		~Terrain();

		NonCopyable(Terrain);

	//Functions
	public:

		void Initialize(const Serialization::BMP::BmpFile& p_File, const Mathematics::coordinate& p_Location = Mathematics::coordinate());

		void Terminate();

		void Render(const LightingBuffer* p_Lighting) const;
	};
}

#endif // #ifndef IncludedVisuTerrainH