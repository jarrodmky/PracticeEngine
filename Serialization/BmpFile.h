#ifndef IncludedSeriBmpFileH
#define IncludedSeriBmpFileH

//===========================================================================
// Filename:	BmpFile.h
// Author:		Jarrod MacKay
// Description:	Informationally equivalent to a basic .obj file
//===========================================================================

//===========================================================================
// Definition
//===========================================================================

namespace Serialization
{
	namespace BMP
	{
		typedef Abstracts::DynamicArray<Mathematics::Vector3> ColourTable;
		typedef Abstracts::DynamicArray<Mathematics::scalar> GrayScaleTable;

		class BmpFile
		{
		public:

			BmpFile(const std::string& p_Filename = "")
				: m_Filename(p_Filename)
				, m_Width()
				, m_Height()
				, m_ColourBuffer(nullptr)
			{}

			bool ReadInBinary()
			{
				using namespace std;

				try
				{
					//open and set to start of file
					ifstream inFile(m_Filename.c_str(), ios::binary | ios::ate);

					if (inFile.good())
					{
						inFile.seekg(0, ios::beg);

						// read the 54-byte header
						Abstracts::Array<s8, 54> info;
						inFile.read(*info, 54);

						// get height and width
						m_Width = static_cast<u32>(*(int*)&info[18]);
						m_Height = static_cast<u32>(*(int*)&info[22]);

						// read colours into buffer (3 bytes per pixel)
						u32 size(3 * m_Width * m_Height);
						m_ColourBuffer = std::make_unique<u8[]>(size);
						inFile.read((s8*)(m_ColourBuffer.get()), size);

						//close file
						inFile.close();
					}
					else
					{
						return false;
					}
				}
				catch (...)
				{
					m_Width = 0;
					m_Height = 0;
					m_ColourBuffer = nullptr;
					return false;
				}

				return true;
			}

			void GetColourTable(ColourTable& p_ColourTable) const
			{
				//set aside space
				p_ColourTable.Resize(m_Height, m_Width);

				//copy over colours in reverse order
				for (u32 i = 0; i < p_ColourTable.Size(); ++i)
				{
					u32 offset(i * 3);
					p_ColourTable[i](3) = static_cast<f32>(m_ColourBuffer[offset] / 255);
					p_ColourTable[i](2) = static_cast<f32>(m_ColourBuffer[offset + 1] / 255);
					p_ColourTable[i](1) = static_cast<f32>(m_ColourBuffer[offset + 2] / 255);
				}
			}

			void GetGrayScaleTable(GrayScaleTable& p_GrayTable) const
			{
				//set aside space
				p_GrayTable.Resize(m_Height, m_Width);

				//copy over colours in reverse order
				for (u32 i = 0; i < p_GrayTable.Size(); ++i)
				{
					u32 offset(i * 3);
					p_GrayTable[i] = static_cast<f32>((m_ColourBuffer[offset] / 255
													+ m_ColourBuffer[offset + 1] / 255
													+ m_ColourBuffer[offset + 1] / 255)) / 3.0f;
				}
			}

		private:

			std::string m_Filename;

			u32 m_Width;

			u32 m_Height;

			std::unique_ptr<u8[]> m_ColourBuffer; // 3 * width * height sized with reversed colours
		};
	} // namespace BMP
} // namespace Serialization

#endif // #ifndef IncludedSeriObjFileH