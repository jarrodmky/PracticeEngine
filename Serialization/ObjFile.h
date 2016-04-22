#ifndef IncludedSeriObjFileH
#define IncludedSeriObjFileH

//===========================================================================
// Filename:	ObjFile.h
// Author:		Jarrod MacKay
// Description:	Informationally equivalent to a basic .obj file
//===========================================================================

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
			using namespace std;

			m_VertexLocations.clear();
			m_VertexNormals.clear();
			m_VertexTextures.clear();
			m_Indices.clear();

			try
			{
				//open and set to start of file
				ifstream inFile(m_Filename.c_str());

				s8 buffer[256];

				if (inFile.good())
				{
					while(!inFile.eof())
					{
						inFile.getline(buffer, 256);

						stringstream inLine(buffer);

						//get line id
						s8 id[2];

						inLine.getline(id, 2, ' ');

						if(id[0] == 'v')
						{
							if(id[1] == '\0')
							{

							}
							else if(id[1] == 'n')
							{

							}
							else if(id[1] == 't')
							{

							}
						}
						else if(id[0] == 'f')
						{

						}
					}
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
				return false;
			}

			return true;
		}

	private:

		std::string m_Filename;

		std::vector<Mathematics::Vector3> m_VertexLocations;

		std::vector<Mathematics::Vector3> m_VertexNormals;

		std::vector<Mathematics::Vector2> m_VertexTextures;

		std::vector<u32> m_Indices;


	};
} // namespace Serialization

#endif // #ifndef IncludedSeriObjFileH