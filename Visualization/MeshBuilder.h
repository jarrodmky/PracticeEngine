#ifndef IncludedVisuMeshBuilderH
#define IncludedVisuMeshBuilderH

//===========================================================================
// Filename:	MeshBuilder.h
// Author:		Jarrod MacKay
// Description:	Builds meshes
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Mathematics.h>

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	template <typename t_MeshType>
	class MeshBuilder
	{
	//Methods
	public:

		using VertexType = typedef typename t_MeshType::Vertex;

		static void CreatePoint(t_MeshType& p_Mesh);
		
		static void CreateLine(t_MeshType& p_Mesh);

		static void CreateTriangle
			( t_MeshType& p_Mesh
			, const Mathematics::Point& p_A
			, const Mathematics::Point& p_B
			, const Mathematics::Point& p_C);

		static void CreateQuad(t_MeshType& p_Mesh);

		static void CreateCube(t_MeshType& p_Mesh, const Mathematics::Point& p_Centre, const Mathematics::scalar p_Width);

		static void CreateSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere);

		static void CreateCylinder(t_MeshType& p_Mesh);
	};
}

//===========================================================================
// Inline Definitions
//===========================================================================

#include "MeshBuilder.inl"

#endif // #ifndef IncludedVisuMeshBuilderH