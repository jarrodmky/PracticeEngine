#ifndef IncludedSeriBmpFileH
#define IncludedSeriBmpFileH

//===========================================================================
// Filename:	BmpFile.h
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
	namespace BMP
	{
		class BmpFile
		{
		public:

			BmpFile(const std::string& p_sFilename = "")
				: m_Filename(p_sFilename)
				, m_Width()
				, m_Height()
				, m_ColourBuffer(nullptr)
			{}

			bool ReadInBinary()
			{
				using namespace std;

				//open and set to start of file
				ifstream inFile(m_Filename.c_str(), ios::binary | ios::ate);
				inFile.seekg(0, ios::beg);

				// read the 54-byte header
				Abstracts::Array<s8, 54> info;
				inFile.read(info.GetPointer(), 54);

				// get height and width
				m_Width = static_cast<u32>(info(18));
				m_Height = static_cast<u32>(info(22));

				// read colours into buffer (3 bytes per pixel)
				u32 size(3 * m_Width * m_Height);
				m_ColourBuffer = std::make_unique<s8[]>(size);
				inFile.read(m_ColourBuffer.get(), size);

				//close file
				inFile.close();
			}

			void GetVectorBuffer(std::vector<Mathematics::Vector>& p_List) const
			{
				//set aside space
				u32 size(m_Width * m_Height);
				p_List.clear();
				p_List.resize(size);

				//copy over colours in reverse order
				for (u32 i = 0; i < size; ++i)
				{
					s8* colour(&m_ColourBuffer[3 * i]);
					p_List[i].z = colour[0];
					p_List[i].y = colour[1];
					p_List[i].x = colour[2];
				}
			}

		private:

			std::string m_Filename;

			u32 m_Width;

			u32 m_Height;

			std::unique_ptr<s8[]> m_ColourBuffer; // 3 * width * height
		};
	} // namespace BMP
} // namespace Serialization

#endif // #ifndef IncludedSeriObjFileH