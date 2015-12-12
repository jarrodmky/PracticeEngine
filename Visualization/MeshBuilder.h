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
#include "System.h"

//===========================================================================
// Classes
//===========================================================================

namespace Visualization
{
	class MeshBuilder
	{
	//Methods
	public:

		template <typename t_MeshType>
		static void CreatePoint(t_MeshType& p_Mesh);
		
		template <typename t_MeshType>
		static void CreateLine(t_MeshType& p_Mesh);
		
		template <typename t_MeshType>
		static void CreateTriangle
			( t_MeshType& p_Mesh
			, const Mathematics::Vector3& p_A
			, const Mathematics::Vector3& p_B
			, const Mathematics::Vector3& p_C);
		
		template <typename t_MeshType>
		static void CreateQuad(t_MeshType& p_Mesh);
		
		template <typename t_MeshType>
		static void CreateCube(t_MeshType& p_Mesh, const Mathematics::Vector3& p_Centre, const Mathematics::scalar p_Width);
		
		template <typename t_MeshType>
		static void CreateInvertedCube(t_MeshType& p_Mesh, const Mathematics::Vector3& p_Centre, const Mathematics::scalar p_Width);
		
		template <typename t_MeshType>
		static void CreateSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere);

		template <typename t_MeshType>
		static void CreateBumpedSphere(t_MeshType& p_Mesh, const Mathematics::Sphere& p_Sphere);
		
		template <typename t_MeshType>
		static void CreateCylinder(t_MeshType& p_Mesh);

		template <typename t_MeshType>
		static void CreateHeightMesh(t_MeshType& p_Mesh, const std::string& p_Filename);

		template <typename t_MeshType>
		static void CreateHeightMesh(t_MeshType& p_Mesh, const u32 p_Rows, const u32 p_Columns);
	};
}

//===========================================================================
// Inline Definitions
//===========================================================================

#include "MeshBuilder.inl"

#endif // #ifndef IncludedVisuMeshBuilderH