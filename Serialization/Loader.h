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
	class Loader
	{
	//methods
	public:

		/*
			Reads a .bmp file into a colour table
		*/
		static bool ReadBmpToColourTable(const std::string& p_SourceFilename, BMP::ColourTable& p_DestinationBuffer)
		{
			BMP::BmpFile source(p_SourceFilename);
			if (source.ReadInBinary())
			{
				source.GetColourTable(p_DestinationBuffer);
				return true;
			}
			return false;
		}
	};
}
#endif // ifndef IncludedSerialLoaderH