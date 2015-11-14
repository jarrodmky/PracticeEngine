#ifndef IncludedSeriObjFileH
#define IncludedSeriObjFileH

//===========================================================================
// Filename:	ObjFile.h
// Author:		Jarrod MacKay
// Description:	Informationally equivalent to a basic .obj file
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "Precompiled.h"

//===========================================================================
// Definition
//===========================================================================

namespace Serialization
{
	class ObjFile
	{
	public:

		ObjFile(const std::string& p_sFilename = "")
			: m_Filename(p_sFilename)
		{}

		bool readInText()
		{
		}

	private:

		std::string m_Filename;

		std::vector<Mathematics::Point> m_VertexLocations;

		std::vector<Mathematics::Vector> m_VertexNormals;

		std::vector<u32> m_Indices;


	};
} // namespace Serialization

#endif // #ifndef IncludedSeriObjFileH