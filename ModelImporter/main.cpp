#include <stdio.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <Core.h>
#include <Serialization.h>
#include <Visualization.h>

using namespace Visualization;

struct Parameters
{
	Parameters()
	: inputFilename(nullptr)
	, outputFilename(nullptr)
	, scale(1.0f)
	{}

	const char* inputFilename;
	const char* outputFilename;
	f32 scale;
};

void PrintHelp()
{
	printf("Usage should be ModelImporter.exe <input file> <output file>");
	printf("additionally [-s scale] is an optional parameter that specifies what to scale to model by");
}

void ParseArguments(Parameters& p_Params, int argc, char *argv[])
{
	p_Params.inputFilename = argv[argc - 2];
	p_Params.outputFilename = argv[argc - 1];
	if(argc > 3)
	{
		for(s32 i = 1; i < argc - 2; ++i)
		{
			if(argv[i][0] == '-')
			{
				switch(argv[i][1])
				{
				case 's':
					p_Params.scale = static_cast<f32>(atof(argv[i + 1]));
				}
			}
		}
	}
}

int main ( int argc, char *argv[] )
{
	if(argc < 3)
	{
		PrintHelp();
		return -1;
	}

	Parameters params;
	ParseArguments(params, argc, argv);

	printf("Hello, reading from %s..\n", params.inputFilename);

	Assimp::Importer importer;

	//TODO: set flags as switches in the command line

	const u32 flags = aiProcess_CalcTangentSpace       
		| aiProcess_Triangulate
		| aiProcess_JoinIdenticalVertices  
		| aiProcess_SortByPType
		| aiProcess_FlipWindingOrder
		| aiProcess_FlipUVs;

	const aiScene* scene = importer.ReadFile(params.inputFilename, flags);

	if(scene == nullptr)
	{
		printf("Error: %s\n", importer.GetErrorString());
		return -1;
	}

	std::vector<FramedMesh*> meshes;
	std::vector<std::string> textureFilenames;

	//read mesh data
	if(scene->HasMeshes())
	{
		for(u32 meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
		{
			aiMesh* readMesh = scene->mMeshes[meshIndex];
			FramedMesh* mesh = new FramedMesh;
			mesh->Allocate(readMesh->mNumVertices, readMesh->mNumFaces * 3, Mathematics::TopologyIndexing::TriangleList);

			//Position
			for(u32 i = 0; i < readMesh->mNumVertices; ++i)
			{
				FramedMesh::VertexType& vertex(mesh->GetVertex(i));
				vertex.Position(0) = readMesh->mVertices[i].x;
				vertex.Position(1) = readMesh->mVertices[i].y;
				vertex.Position(2) = readMesh->mVertices[i].z;
			}

			//Normals
			if(readMesh->HasNormals())
			{
				for(u32 i = 0; i < readMesh->mNumVertices; ++i)
				{
					FramedMesh::VertexType& vertex(mesh->GetVertex(i));
					vertex.Normal(0) = readMesh->mNormals[i].x;
					vertex.Normal(1) = readMesh->mNormals[i].y;
					vertex.Normal(2) = readMesh->mNormals[i].z;
				}
			}

			//Tangents
			if(readMesh->HasTangentsAndBitangents())
			{
				for(u32 i = 0; i < readMesh->mNumVertices; ++i)
				{
					FramedMesh::VertexType& vertex(mesh->GetVertex(i));
					vertex.Tangent(0) = readMesh->mTangents[i].x;
					vertex.Tangent(1) = readMesh->mTangents[i].y;
					vertex.Tangent(2) = readMesh->mTangents[i].z;
				}
			}

			//UVs
			if(readMesh->HasTextureCoords(0))
			{
				for(u32 i = 0; i < readMesh->mNumVertices; ++i)
				{
					FramedMesh::VertexType& vertex(mesh->GetVertex(i));
					vertex.TextureCoord(0) = readMesh->mTextureCoords[0][i].x;
					vertex.TextureCoord(1) = readMesh->mTextureCoords[0][i].y;
				}
			}

			//Indices
			for(u32 face = 0, index = 0; face < readMesh->mNumFaces; ++face, index += 3)
			{
				mesh->GetIndex(index + 0) = readMesh->mFaces[face].mIndices[0];
				mesh->GetIndex(index + 1) = readMesh->mFaces[face].mIndices[1];
				mesh->GetIndex(index + 2) = readMesh->mFaces[face].mIndices[2];
 			}

			meshes.push_back(mesh);
		}
	}
	

	//read material data
	if(scene->HasMaterials())
	{
		for(u32 i = 0; i < scene->mNumMaterials; ++i)
		{
			aiMaterial* material(scene->mMaterials[i]);

			const u32 textureCount(material->GetTextureCount(aiTextureType_DIFFUSE));

			if(textureCount > 0)
			{
				aiString texturePath;
				if(material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
				{
					textureFilenames.push_back(texturePath.C_Str());
				}
			}
		}
	}
	

	//TODO
	//Utils::fileopen file(outputFilename)
	//Utisl::IO::write(mesh)
	//file.close;

	
	
	printf("Writing to %s...\n", params.outputFilename);

	FILE* file = nullptr;
	errno_t error = fopen_s(&file, params.outputFilename, "w");
	if(error != 0)
	{
		Log("Failed to write to output file!");
		return -1;
	}

	const u32 numMeshes = static_cast<u32>(meshes.size());
	fprintf(file, "numMeshes: %d\n", numMeshes);
	for(u32 m = 0; m < numMeshes; ++m)
	{
		FramedMesh* mesh = meshes[m];
		const u32 numVertices = mesh->GetVertexCount();
		const u32 numIndices = mesh->GetIndexCount();
		const f32 scale = params.scale;
		fprintf(file, "numVertices: %d\n", numVertices);
		fprintf(file, "numIndices: %d\n", numIndices);

		for(u32 v = 0; v < numVertices; ++v)
		{
			FramedMesh::VertexType& vertex = mesh->GetVertex(v);
			fprintf(file, "%f %f %f %f %f %f %f %f %f %f %f\n"
					, vertex.Position(0) * scale, vertex.Position(1) * scale, vertex.Position(2) * scale
					, vertex.Normal(0), vertex.Normal(1), vertex.Normal(2)
					, vertex.Tangent(0), vertex.Tangent(1), vertex.Tangent(2)
					, vertex.TextureCoord(0), vertex.TextureCoord(1));
		}
		
		for(u32 i = 0; i < numIndices; i += 3)
		{
			fprintf(file, "%d %d %d\n", mesh->GetIndex(i + 0), mesh->GetIndex(i + 1), mesh->GetIndex(i + 2));
		}
	}
		
	const u32 numTextures = static_cast<u32>(textureFilenames.size());
	fprintf(file, "numTextures: %d\n", numTextures);
	for(u32 t = 0; t < numTextures; ++t)
	{
		fprintf(file, "%s\n", textureFilenames[t].c_str());
	}

	fclose(file);

	for(u32 i = 0; i < numMeshes; ++i)
	{
		meshes[i]->Destroy();
		ProperlyDelete(meshes[i]);
	}

	
	printf("Import complete!\n");
	//TODO
	//abstract into general file importer/exporter utils

	return 0;
}