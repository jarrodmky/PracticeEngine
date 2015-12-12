#ifndef IncludedSerializationH
#define IncludedSerializationH

//===========================================================================
// Filename:	Serialization.h
// Author:		Jarrod MacKay
// Description:	Main entry point to the file i/o library.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "JsonFile.h"
#include "CsvFile.h"
#include "ObjFile.h"
#include "BmpFile.h"
#include "Converter.h"
#include "Loader.h"

namespace Serialization
{

	//===========================================================================
	// Functions
	//===========================================================================

	/*
	Given "<filepath>[/ or \]<basename>.<file extension>" returns "<basename>" as json string
	*/
	static std::string GetBaseNameFromFilename(const std::string& p_sFilename)
	{
		unsigned int length = p_sFilename.length();
		unsigned int i = 0;

		unsigned int baseEnd = 0;
		unsigned int baseStart = 0;

		//get index of last '.' occurence
		for (i = length; i >= 0; --i)
		{
			if (p_sFilename[i] == char('.'))
			{
				baseEnd = i;
				break;
			}
		}

		//get index of last '/' or '\' occurence before last '.'
		for (; i >= 0; --i)
		{
			if (p_sFilename[i] == char('\\') || p_sFilename[i] == char('/'))
			{
				baseStart = i;
				break;
			}
		}

		//return substring
		return p_sFilename.substr(baseStart + 1, baseEnd - baseStart - 1);
	}
}
#endif //#ifndef IncludedSerializationH