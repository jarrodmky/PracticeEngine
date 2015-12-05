///*
//(C)2015 Jarrod MacKay
//May 1, 2015
//
//JsonFile.h
//Represents a JSON file, allows multiple objects to be
//included in the file.
//*/
//
//#pragma once
//#ifndef JSONFILE_H
//#define JSONFILE_H
//
//#include "Value.h"
//
//namespace JSON
//{
//	//class ObjectPointer
//	//{
//	//public:
//	//	ObjectPointer()
//	//		:
//	//		m_Object()
//	//	{}
//
//	//	~ObjectPointer()
//	//	{
//	//		m_Object.reset(nullptr);
//	//	}
//
//	//	ObjectPointer(const ObjectPointer& other)
//	//	{
//	//		m_Object.reset(&(*(other.m_Object)));
//	//	}
//
//	//	ObjectPointer(ObjectPointer&& other)
//	//		:
//	//		m_Object(std::move(other.m_Object))
//	//	{}
//
//	//	ObjectPointer(Object* p_ValueRawPtr)
//	//	{
//	//		m_Object.reset(p_ValueRawPtr);
//	//	}
//
//	//	ObjectPointer& operator =(const ObjectPointer& other)
//	//	{
//	//		m_Object.reset(&(*(other.m_Object)));
//	//		return *this;
//	//	}
//
//	//	ObjectPointer& operator =(ObjectPointer&& other)
//	//	{
//	//		m_Object = std::move(other.m_Object);
//	//		return *this;
//	//	}
//
//	//	//ValuePointer& operator =(Value* p_ValueRawPtr)
//	//	//{
//	//	//	m_Value.reset(p_ValueRawPtr);
//	//	//	return *this;
//	//	//}
//
//	//	std::string toText(void) const
//	//	{
//	//		return m_Object->toText();
//	//	}
//
//	//private:
//
//	//	std::unique_ptr<Object> m_Object;
//	//};
//
//
//	class JsonFile
//	{
//	public:
//
//		//JsonFile(const std::string& p_sFilename = "")
//		//	: 
//		//	m_Objects(0),
//		//	m_sFilename(p_sFilename)
//		//{}
//
//		//void addObject(ValuePointer p_Object)
//		//{
//		//	m_Objects.push_back(p_Object);
//		//}
//
//		//bool writeOutText(void) const
//		//{
//		//	//open and check the file stream
//		//	std::ofstream outFile(m_sFilename.c_str());
//		//	if (!outFile.good())
//		//	{
//		//		outFile.close();
//		//		return false;
//		//	}
//
//		//	//print the JSON object to the file
//		//	for (unsigned int i = 0; i < m_Objects.size(); ++i)
//		//	{
//		//		//outFile << m_Objects[i].toText() << std::endl;
//		//	}
//
//		//	//stop using the file
//		//	outFile.close();
//		//	return true;
//		//}
//
//	private:
//
//		//std::vector<ValuePointer> m_Objects;
//
//		//std::string m_sFilename;
//	};
//
//
//
//	//methods
//	/*
//	Makes a JSON Object (Table) out of a CSV File
//	*/
//	//JSON::ValuePointer MakeJsonTable(const CSV::CsvFile& p_CsvFile)
//	//{
//	//	//create a JSON "table"
//	//	JSON::Object* table = new JSON::Object();
//
//	//	//add records and a name
//	//	table->addMember(
//	//		JSON::String(GetBaseNameFromFilename(p_CsvFile.getFilename())),
//	//		MakeJsonRecordSet(p_CsvFile.getTable()));
//
//	//	return JSON::ValuePointer(table);
//	//}
//
//	///*
//	//Makes a JSON Array out of a CSV table
//	//*/
//	//JSON::ValuePointer MakeJsonRecordSet(const CSV::Table& p_CsvTable)
//	//{
//	//	//create a JSON array
//	//	JSON::Array* recordSet = new JSON::Array();
//
//	//	//for each record in the table...
//	//	for (unsigned int i = 0; i < p_CsvTable.getNumberOfRecords(); ++i)
//	//	{
//
//	//		//...add a "JSON record" to the array
//	//		recordSet->addValue(MakeJsonRecord(p_CsvTable, i));
//	//	}
//
//	//	//store table data and name in JSON object
//	//	JSON::ValuePointer retPointer;
//	//	retPointer = recordSet;
//
//	//	return retPointer;
//	//}
//
//	////shared_ptr<JSON::ValuePointer> pVal;
//
//	////bool Create(shared_ptr<JSON::ValuePointer> &pOut)
//	////{
//	////	pOut.Reset(new JSON::ValuePointer());
//
//	////}
//
//
//	////JSON::ValuePointer* pVal;
//	////if(Create(&pVal))
//
//	////bool Create(JSON::ValuePointer**ppOut)
//	////{
//	////	*ppOut = new JSON::ValuePointer;
//	////	return true;
//	////}
//
//	///*
//	//Makes a JSON object out of a CSV record (row)
//	//*/
//	//JSON::ValuePointer MakeJsonRecord(const CSV::Table& p_CsvTable, const unsigned int p_uiRow)
//	//{
//	//	JSON::Object* newRecord = new JSON::Object();
//
//	//	//for each attribute, add an name-value pair to the object
//	//	for (unsigned int j = 0; j < p_CsvTable.getNumberOfAttributes(); ++j)
//	//	{
//	//		newRecord->addMember(JSON::String(p_CsvTable.getAttribute(j)),
//	//			ConvertValue(p_CsvTable.getValueAsString(p_uiRow, j)));
//	//	}
//
//	//	JSON::ValuePointer retPointer;
//	//	retPointer = newRecord;
//
//	//	return retPointer;
//	//}
//
//	///*
//	//Converts a CSV Value to a JSON Value (Both are the atomic data tpe of respective file types)
//	//*/
//	//JSON::ValuePointer ConvertValue(const CSV::Value& p_CsvValue)
//	//{
//	//	JSON::ValuePointer retPointer;
//	//	std::string checkString = p_CsvValue;
//	//	std::transform(checkString.begin(), checkString.end(), checkString.begin(), ::tolower);
//
//	//	if (4 == p_CsvValue.size() && p_CsvValue.find("null") == 0)
//	//	{
//	//		//values is null
//	//		retPointer = new JSON::Null();
//	//	}
//	//	else if (4 == p_CsvValue.size() && p_CsvValue.find("true") == 0)
//	//	{
//	//		//value is true logical
//	//		retPointer = new JSON::Logic(true);
//	//	}
//	//	else if (5 == p_CsvValue.size() && p_CsvValue.find("false") == 0)
//	//	{
//	//		//value is false logical
//	//		retPointer = new JSON::Logic(false);
//	//	}
//	//	else
//	//	{
//	//		//value is either number or string
//	//		char* remainder = "";
//	//		double value;
//	//		value = strtod(p_CsvValue.c_str(), &remainder);
//
//	//		if (strcmp(remainder, "\0") == 0)
//	//		{
//	//			retPointer = new JSON::Number(value);
//	//		}
//	//		else
//	//		{
//	//			retPointer = new JSON::String(p_CsvValue);
//	//		}
//	//	}
//	//	return retPointer;
//	//}
//}
//#endif