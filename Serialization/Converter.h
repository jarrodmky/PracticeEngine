/*
(C)2015 Jarrod MacKay
May 1, 2015

Converter.h
A class which contain methods for transfering between file formats.
*/

#pragma once
#ifndef IncludedSerialConverterH
#define IncludedSerialConverterH

#include "JsonFile.h"
#include "CsvFile.h"
#include "ObjFile.h"
#include "BmpFile.h"

namespace Serialization
{
	class Converter
	{
	public:

		///*
		//	Uses a single CSV file object to create a informationally equivalent JSON file object
		//*/
		//static JSON::JsonFile& ConvertCsvToJson(const CSV::CsvFile& p_InputFile, JSON::JsonFile& p_OutputFile)
		//{
		//	//add table to file
		//	p_OutputFile.addObject(JSON::MakeJsonTable(p_InputFile));
		//	return p_OutputFile;
		//}
	};
}
#endif // ifndef IncludedSerialConverterH