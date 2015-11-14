/*
(C)2015 Jarrod MacKay
May 2, 2015

Value.cpp
*/

#include "Precompiled.h"
#include "Value.h"

namespace JSON
{
	ValuePointer::ValuePointer(Value* p_ValueRawPtr)
		: 
		m_Value(nullptr/* p_ValueRawPtr*/)
	{}

	ValuePointer::~ValuePointer()
	{
		//m_Value..reset(nullptr);
	}

	ValuePointer::ValuePointer(const ValuePointer& other)
	{
		m_Value.reset(&(*(other.m_Value)));
	}	
	
	//ValuePointer::ValuePointer(std::unique_ptr<Value>& other)
	//{
	//	m_Value.reset(&(*(other)));
	//	other.release();
	//}

	ValuePointer::ValuePointer(ValuePointer&& other) 
		: 
		m_Value(std::move(other.m_Value))
	{}

	ValuePointer& ValuePointer::operator =(const ValuePointer& other)
	{
		m_Value.reset(&(*(other.m_Value)));
		return *this;
	}

	ValuePointer& ValuePointer::operator =(ValuePointer&& other)
	{
		m_Value = std::move(other.m_Value);
		return *this;
	}

	ValuePointer& ValuePointer::operator =(Value* p_ValueRawPtr)
	{
		m_Value.reset(std::move(p_ValueRawPtr));
		return *this;
	}

	std::string ValuePointer::toText(void) const
	{
		AssertOnly(m_Value != nullptr);
		return m_Value->toText();
	}

	std::string Null::toText(void) const
	{
		return "null";
	}

	Logic::Logic(bool p_bValue)
	{
		m_bBool = p_bValue;
	}

	std::string Logic::toText(void) const
	{
		if (m_bBool) return "true";
		else return "false";
	}

	String::String() : m_sString() {}

	String::String(std::string p_sValue)
	{
		m_sString = p_sValue;
	}

	std::string String::toText(void) const
	{
		return std::string("\"" + m_sString + "\"");
	}

	Number::Number(double p_dValue)
	{
		m_dNumber = p_dValue;
	}
	
	std::string Number::toText(void) const
	{
		std::string retString;
		std::stringstream formatter(retString);

		//format output string
		formatter << std::scientific << std::setprecision(8);
		formatter << m_dNumber;

		return retString;
	}
	
	Object::Object() : m_Members(0) {}

	void Object::addMember(String& p_String, ValuePointer p_Value)
	{
		m_Members.push_back(StringValue(p_String, p_Value));
	}

	void Object::clearMembers(void)
	{
		m_Members.clear();
	}

	std::string Object::toText(void) const
	{
		unsigned int numberOfMembers = m_Members.size();
		if (numberOfMembers < 1)
		{
			return "{}";
		}

		//add the first curly brace
		std::string returnText("{");

		//add first member
		returnText.append(m_Members[0].first.toText()
			+ ":" + m_Members[0].second.toText());

		//if more members, append a comma and print next member
		for (unsigned int i = 1; i < numberOfMembers; ++i)
		{
			returnText.append("," + m_Members[i].first.toText()
				+ ":" + m_Members[i].second.toText());
		}

		//close the curly braces and return
		returnText.append("}");
		return returnText;
	}
	
	Array::Array() : m_Values(0) {}

	void Array::addValue(ValuePointer p_Value)
	{
		m_Values.push_back(p_Value);
	}

	void Array::clearValues(void)
	{
		m_Values.clear();
	}

	std::string Array::toText(void) const
	{
		//add square bracket a print first element
		std::string returnText("[");

		//add first value if it exists
		if (m_Values.size() > 0)
		{
			returnText.append(m_Values[0].toText());
		}

		//if more elements, append a comma and print
		for (unsigned int i = 1; i < m_Values.size(); ++i)
		{
			returnText.append("," + m_Values[i].toText());
		}

		//close the brackets and return
		returnText.append("]");
		return returnText;
	}
}