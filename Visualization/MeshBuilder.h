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
			(t_MeshType& p_Mesh
			, const Mathematics::Vector3& p_A
			, const Mathematics::Vector3& p_B
			, const Mathematics::Vector3& p_C);

		template <typename t_MeshType>
		static void CreateQuad(t_MeshType& p_Mesh
							   , const Mathematics::Quad3& p_Quad
							   , const Mathematics::LinearColour& p_FlatColour = Mathematics::ColourPallet::White);

		template <typename t_MeshType>
		static void CreateUnitCube(t_MeshType& p_Mesh, const bool p_Inverted = false
								   , const Mathematics::LinearColour& p_FlatColour = Mathematics::ColourPallet::White);

		template <typename t_MeshType>
		static void CreateUnitSphere(t_MeshType& p_Mesh
									 , const u32 p_Resolution = 64
									 , const Mathematics::LinearColour& p_FlatColour = Mathematics::ColourPallet::White);

		template <typename t_MeshType>
		static void CreateUnitTorus(t_MeshType& p_Mesh
			, const u32 p_Resolution = 64
			, const Mathematics::LinearColour& p_FlatColour = Mathematics::ColourPallet::White);

		template <typename t_MeshType>
		static void CreateHeightMesh(t_MeshType& p_Mesh, const std::string& p_Filename);

		template <typename t_MeshType>
		static void CreateHeightMesh(t_MeshType& p_Mesh, const u32 p_Rows, const u32 p_Columns);

		template <typename t_MeshType>
		static void CreateModelMesh(t_MeshType& p_Mesh, FILE* p_File);

		template <typename t_MeshType>
		static void CreateModelMesh(t_MeshType& p_Mesh, FILE* p_File, Mathematics::PointCloud3& p_Points);

	};
}

//===========================================================================
// Inline Definitions
//===========================================================================

#include "MeshBuilder.inl"

#endif // #ifndef IncludedVisuMeshBuilderH