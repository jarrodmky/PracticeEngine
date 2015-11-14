/*
(C)2015 Jarrod MacKay
May 1, 2015

JsonFile.h
Represents a JSON file, allows multiple objects to be
included in the file.
*/

#pragma once
#ifndef JSONFILE_H
#define JSONFILE_H

#include "Value.h"

namespace JSON
{
	//class ObjectPointer
	//{
	//public:
	//	ObjectPointer()
	//		:
	//		m_Object()
	//	{}

	//	~ObjectPointer()
	//	{
	//		m_Object.reset(nullptr);
	//	}

	//	ObjectPointer(const ObjectPointer& other)
	//	{
	//		m_Object.reset(&(*(other.m_Object)));
	//	}

	//	ObjectPointer(ObjectPointer&& other)
	//		:
	//		m_Object(std::move(other.m_Object))
	//	{}

	//	ObjectPointer(Object* p_ValueRawPtr)
	//	{
	//		m_Object.reset(p_ValueRawPtr);
	//	}

	//	ObjectPointer& operator =(const ObjectPointer& other)
	//	{
	//		m_Object.reset(&(*(other.m_Object)));
	//		return *this;
	//	}

	//	ObjectPointer& operator =(ObjectPointer&& other)
	//	{
	//		m_Object = std::move(other.m_Object);
	//		return *this;
	//	}

	//	//ValuePointer& operator =(Value* p_ValueRawPtr)
	//	//{
	//	//	m_Value.reset(p_ValueRawPtr);
	//	//	return *this;
	//	//}

	//	std::string toText(void) const
	//	{
	//		return m_Object->toText();
	//	}

	//private:

	//	std::unique_ptr<Object> m_Object;
	//};


	class JsonFile
	{
	public:

		JsonFile(const std::string& p_sFilename = "")
			: 
			m_Objects(0),
			m_sFilename(p_sFilename)
		{}

		void addObject(ValuePointer p_Object)
		{
			m_Objects.push_back(p_Object);
		}

		bool writeOutText(void) const
		{
			//open and check the file stream
			std::ofstream outFile(m_sFilename.c_str());
			if (!outFile.good())
			{
				outFile.close();
				return false;
			}

			//print the JSON object to the file
			for (unsigned int i = 0; i < m_Objects.size(); ++i)
			{
				//outFile << m_Objects[i].toText() << std::endl;
			}

			//stop using the file
			outFile.close();
			return true;
		}

	private:

		std::vector<ValuePointer> m_Objects;

		std::string m_sFilename;
	};
}
#endif