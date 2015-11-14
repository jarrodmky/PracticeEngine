/*
(C)2015 Jarrod MacKay
May 1, 2015

FileConverter.h
A class which contain overloaded
methods for transfering between file formats.
*/

#pragma once
#ifndef FILECONVERTER_H
#define FILECONVERTER_H

#include "JsonFile.h"
#include "CsvFile.h"

class FileConverter
{
public:

	/*
		Uses a single CSV file object to create a informationally equivalent JSON file object
	*/
	JSON::JsonFile& convertToJson(const CSV::CsvFile& p_InputFile, JSON::JsonFile& p_OutputFile) const
	{
		//add table to file
		p_OutputFile.addObject(makeJsonTable(p_InputFile));
		return p_OutputFile;
	}

private:
	/*
		Makes a JSON Object (Table) out of a CSV File
	*/
	JSON::ValuePointer makeJsonTable(const CSV::CsvFile& p_CsvFile) const
	{
		//create a JSON "table"
		JSON::Object* table = new JSON::Object();

		//add records and a name
		table->addMember(
			JSON::String(getBaseNameFromFilename(p_CsvFile.getFilename())),
			makeJsonRecordSet(p_CsvFile.getTable()));

		return JSON::ValuePointer(table);
	}

	/*
		Makes a JSON Array out of a CSV table
	*/
	JSON::ValuePointer makeJsonRecordSet(const CSV::Table& p_CsvTable) const
	{
		//create a JSON array
		JSON::Array* recordSet = new JSON::Array();

		//for each record in the table...
		for (unsigned int i = 0; i < p_CsvTable.getNumberOfRecords(); ++i)
		{

			//...add a "JSON record" to the array
			recordSet->addValue(makeJsonRecord(p_CsvTable, i));
		}

		//store table data and name in JSON object
		JSON::ValuePointer retPointer;
		retPointer = recordSet;

		return retPointer; 
	}

	//shared_ptr<JSON::ValuePointer> pVal;

	//bool Create(shared_ptr<JSON::ValuePointer> &pOut)
	//{
	//	pOut.Reset(new JSON::ValuePointer());

	//}


	//JSON::ValuePointer* pVal;
	//if(Create(&pVal))

	//bool Create(JSON::ValuePointer**ppOut)
	//{
	//	*ppOut = new JSON::ValuePointer;
	//	return true;
	//}

	/*
		Makes a JSON object out of a CSV record (row)
	*/
	JSON::ValuePointer makeJsonRecord(const CSV::Table& p_CsvTable, const unsigned int p_uiRow) const
	{
		JSON::Object* newRecord = new JSON::Object();

		//for each attribute, add an name-value pair to the object
		for (unsigned int j = 0; j < p_CsvTable.getNumberOfAttributes(); ++j)
		{
			newRecord->addMember(JSON::String(p_CsvTable.getAttribute(j)),
								 convertValue(p_CsvTable.getValueAsString(p_uiRow, j)));
		}

		JSON::ValuePointer retPointer;
		retPointer = newRecord;

		return retPointer;
	}

	/*
		Converts a CSV Value to a JSON Value (Both are the atomic data tpe of respective file types)
	*/
	JSON::ValuePointer convertValue(const CSV::Value& p_CsvValue) const
	{
		JSON::ValuePointer retPointer;
		std::string checkString = p_CsvValue;
		std::transform(checkString.begin(), checkString.end(), checkString.begin(), ::tolower);

		if (4 == p_CsvValue.size() && p_CsvValue.find("null") == 0)
		{
			//values is null
			retPointer = new JSON::Null();
		}
		else if (4 == p_CsvValue.size() && p_CsvValue.find("true") == 0)
		{
			//value is true logical
			retPointer = new JSON::Logic(true);
		}
		else if (5 == p_CsvValue.size() && p_CsvValue.find("false") == 0)
		{
			//value is false logical
			retPointer = new JSON::Logic(false);
		}
		else
		{
			//value is either number or string
			char* remainder = "";
			double value;
			value = strtod(p_CsvValue.c_str(), &remainder);

			if (strcmp(remainder, "\0") == 0)
			{
				retPointer = new JSON::Number(value);
			}
			else
			{
				retPointer = new JSON::String(p_CsvValue);
			}
		}
		return retPointer;
	}


	/*
		Given "<filepath>[/ or \]<basename>.<file extension>" returns "<basename>" as json string
	*/
	std::string getBaseNameFromFilename(const std::string& p_sFilename) const
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
};
#endif