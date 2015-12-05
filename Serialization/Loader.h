/*
(C)2015 Jarrod MacKay
Dec. 3, 2015

Loader.h
A class which contain methods for reading files into buffers
*/

#pragma once
#ifndef IncludedSerialLoaderH
#define IncludedSerialLoaderH

#include <Abstracts.h>
#include "ObjFile.h"
#include "BmpFile.h"

namespace Serialization
{
	typedef std::vector<Mathematics::Vector> VectorBuffer;

	class Loader
	{
	//methods
	public:

		/*
			Reads a .bmp file into a colour vector
		*/
		static VectorBuffer& ReadBmpToColourBuffer(BMP::BmpFile& p_SourceFile, Abstracts::Table<Mathematics::Vector>& p_DestinationBuffer)
		{
			p_SourceFile.ReadInBinary();
			p_SourceFile.GetVectorBuffer(p_DestinationBuffer);

			return p_DestinationBuffer;
		}
	};
}
#endif // ifndef IncludedSerialLoaderH