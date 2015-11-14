/*
(C)2015 Jarrod MacKay
May 1, 2015

Value.h
A collection of closely related wrapper classes that represent the JSON 
formats. All formatting is compliant with JSON.org

Array
Object
String
Number
Logical
Null
*/

#pragma once
#ifndef VALUE_H
#define VALUE_H

namespace JSON
{
	//The most general type
	class Value
	{
	public:

		//virtual string of JSON formatted output
		virtual std::string toText(void) const = 0;
	};

	class ValuePointer
	{
	public:
		ValuePointer(Value* p_ValueRawPtr = nullptr);

		~ValuePointer();

		ValuePointer(const ValuePointer& other);

		ValuePointer(ValuePointer&& other);

		ValuePointer& operator =(const ValuePointer& other);

		ValuePointer& operator =(ValuePointer&& other);

		ValuePointer& operator =(Value* p_ValueRawPtr);

		std::string toText(void) const;

	private:

		std::shared_ptr<Value> m_Value;
	};



	//A value that has no data
	class Null : virtual public Value
	{
	public:

		virtual std::string toText(void) const;
	};



	//a value that has two possible states
	class Logic : virtual public Value
	{
	public:

		Logic(bool p_bValue);

		virtual std::string toText(void) const;

	private:

		bool m_bBool;
	};



	//a value that represents a valid JSON string
	class String : virtual public Value
	{
	public:

		String();

		String(std::string p_sValue);

		virtual std::string toText(void) const;

	private:

		std::string m_sString;
	};



	//a JSON string that has a specific numeric format
	class Number : virtual public Value
	{
	public:

		Number(double p_dValue);

		virtual std::string toText(void) const;

	private:

		double m_dNumber;
	};

	//a string/value pair object
	typedef std::pair<String, ValuePointer> StringValue;

	//The object structure
	class Object : virtual public Value
	{
	public:

		Object();
		
		void addMember(String& p_String, ValuePointer p_Value);

		void clearMembers(void);

		virtual std::string toText(void) const;

	private:

		std::vector<StringValue> m_Members;
	};



	//The array structure
	class Array : virtual public Value
	{
	public:

		Array();

		void addValue(ValuePointer p_Value);

		void clearValues(void);

		virtual std::string toText(void) const;

	private:

		std::vector<ValuePointer> m_Values;
	};
}
#endif