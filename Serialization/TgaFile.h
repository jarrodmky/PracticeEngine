#ifndef IncludedSeriTgaFileH
#define IncludedSeriTgaFileH

//===========================================================================
// Filename:	TgaFile.h
// Author:		Jarrod MacKay
// Description:	Informationally equivalent to a basic .obj file
//===========================================================================

//===========================================================================
// Definition
//===========================================================================

namespace Serialization
{
	namespace TGA
	{
		typedef Abstracts::DynamicArray<Mathematics::Vector3> ColourTable;
		typedef Abstracts::DynamicArray<Mathematics::scalar> GrayScaleTable;

		class TgaFile
		{
		private:
			typedef union RGBA
			{
				u32 Colour;
				struct
				{
					u8 B, G, R, A;
				};
			} *PRGB;


		public:

			TgaFile(const std::string& p_Filename = "")
				: m_Filename(p_Filename)
			{
			}

			std::vector<unsigned char> GetPixels() { return this->Pixels; }

			bool ReadInBinary()
			{
				std::fstream hFile(m_Filename.c_str(), std::ios::in | std::ios::binary);
				if(!hFile.is_open()) { throw std::invalid_argument("File Not Found."); }

				u8 Header[18] = {0};
				std::vector<u8> ImageData;
				static u8 DeCompressed[12] = {0x0, 0x0, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
				static u8 IsCompressed[12] = {0x0, 0x0, 0xA, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};

				hFile.read(reinterpret_cast<char*>(&Header), sizeof(Header));

				if(!std::memcmp(DeCompressed, &Header, sizeof(DeCompressed)))
				{
					BitsPerPixel = Header[16];
					width = Header[13] * 0xFF + Header[12];
					height = Header[15] * 0xFF + Header[14];
					size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

					if((BitsPerPixel != 24) && (BitsPerPixel != 32))
					{
						hFile.close();
						throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
					}

					ImageData.resize(size);
					ImageCompressed = false;
					hFile.read(reinterpret_cast<char*>(ImageData.data()), size);
				}
				else if(!std::memcmp(IsCompressed, &Header, sizeof(IsCompressed)))
				{
					BitsPerPixel = Header[16];
					width = Header[13] * 0xFF + Header[12];
					height = Header[15] * 0xFF + Header[14];
					size = ((width * BitsPerPixel + 31) / 32) * 4 * height;

					if((BitsPerPixel != 24) && (BitsPerPixel != 32))
					{
						hFile.close();
						throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit Image.");
					}

					RGBA Pixel = {0};
					int CurrentByte = 0;
					std::size_t CurrentPixel = 0;
					ImageCompressed = true;
					u8 ChunkHeader = {0};
					int BytesPerPixel = (BitsPerPixel / 8);
					ImageData.resize(width * height * sizeof(RGBA));

					do
					{
						hFile.read(reinterpret_cast<char*>(&ChunkHeader), sizeof(ChunkHeader));

						if(ChunkHeader < 128)
						{
							++ChunkHeader;
							for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
							{
								hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

								ImageData[CurrentByte++] = Pixel.B;
								ImageData[CurrentByte++] = Pixel.G;
								ImageData[CurrentByte++] = Pixel.R;
								if(BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
							}
						}
						else
						{
							ChunkHeader -= 127;
							hFile.read(reinterpret_cast<char*>(&Pixel), BytesPerPixel);

							for(int I = 0; I < ChunkHeader; ++I, ++CurrentPixel)
							{
								ImageData[CurrentByte++] = Pixel.B;
								ImageData[CurrentByte++] = Pixel.G;
								ImageData[CurrentByte++] = Pixel.R;
								if(BitsPerPixel > 24) ImageData[CurrentByte++] = Pixel.A;
							}
						}
					} while(CurrentPixel < (width * height));
				}
				else
				{
					hFile.close();
					throw std::invalid_argument("Invalid File Format. Required: 24 or 32 Bit TGA File.");
				}

				hFile.close();
				this->Pixels = ImageData;
			}

			void GetColourTable(ColourTable& p_ColourTable) const
			{
				//set aside space
				p_ColourTable.Resize(height, width);

				//copy over colours in reverse order
				for(u32 i = 0; i < p_ColourTable.GetNumberOfElements(); ++i)
				{
					u32 offset(i * 3);
					p_ColourTable(i)(3) = static_cast<f32>(Pixels[offset] / 255);
					p_ColourTable(i)(2) = static_cast<f32>(Pixels[offset + 1] / 255);
					p_ColourTable(i)(1) = static_cast<f32>(Pixels[offset + 2] / 255);
				}
			}

			void GetGrayScaleTable(GrayScaleTable& p_GrayTable) const
			{
				//set aside space
				p_GrayTable.Resize(height, width);

				//copy over colours in reverse order
				for(u32 i = 0; i < p_GrayTable.GetNumberOfElements(); ++i)
				{
					u32 offset(i * 3);
					p_GrayTable(i) = static_cast<f32>((Pixels[offset] / 255
						+ Pixels[offset + 1] / 255
						+ Pixels[offset + 1] / 255)) / 3.0f;
				}
			}

		private:

			std::string m_Filename;
			std::vector<unsigned char> Pixels;
			bool ImageCompressed;
			u32 size, BitsPerPixel;

		public:
			u32 width, height;
		};
	} // namespace BMP
} // namespace Serialization

#endif // #ifndef IncludedSeriObjFileH