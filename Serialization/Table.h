///*
//(C)2015 Jarrod MacKay
//May 1, 2015
//
//Table.h
//A text data table representation object with a header row and records with attribute columns
//*/
//
//#pragma once
//#ifndef TABLE_H
//#define TABLE_H
//
//#include <Core.h>
//
//namespace CSV
//{
//	//an STL string object
//	typedef std::string Value;
//
//	typedef std::unique_ptr<Value[]> Row;
//
//	/*
//		Represents all data that would be written or read from a Excel CSV table
//	*/
//	class Table
//	{
//	public:
//
//		Table(unsigned int p_uiNumberOfAttributes = 0) : 
//			m_uiNumAttributes(p_uiNumberOfAttributes),
//			m_Header(nullptr),
//			m_Values(0)
//		{}
//
//		void addHeader(const std::vector<std::string>& p_vHeaderString)
//		{
//			if (!m_Header)
//			{
//				m_Header.swap(std::make_unique<Value[]>(m_uiNumAttributes));
//
//				for (unsigned int i = 0; i < m_uiNumAttributes; ++i)
//				{
//					m_Header[i] = p_vHeaderString[i];
//				}
//			}
//		}
//
//		void addRecord(const std::vector<std::string>& p_vRecordString)
//		{
//			Row newRecord = std::make_unique<Value[]>(m_uiNumAttributes);
//			
//			for (unsigned int i = 0; i < m_uiNumAttributes; ++i)
//			{
//				newRecord[i] = p_vRecordString[i];
//			}
//
//			m_Values.push_back(std::move(newRecord));
//		}
//
//		Value& getAttribute(const unsigned int p_uiColumn) const
//		{
//			Assert(isColumn(p_uiColumn), "Invalid column access!");
//			return m_Header[p_uiColumn];
//		}
//
//		Value& getValueAsString(const unsigned int p_uiRow, const unsigned int p_uiColumn) const
//		{
//			Assert(isRow(p_uiRow) && isColumn(p_uiColumn), "invalid indices!");
//			return m_Values[p_uiRow][p_uiColumn];
//		}
//
//		unsigned int getNumberOfAttributes(void) const
//		{
//			return m_uiNumAttributes;
//		}
//
//		unsigned int getNumberOfRecords(void) const
//		{
//			return m_Values.size();
//		}
//
//	private:
//
//		unsigned int m_uiNumAttributes;
//
//		Row m_Header;
//
//		std::vector<Row> m_Values;
//
//		bool isRow(const unsigned int p_uiIndex) const
//		{
//			return (0 <= p_uiIndex) && (p_uiIndex < m_Values.size());
//		}
//		
//		bool isColumn(const unsigned int p_uiIndex) const
//		{
//			return (0 <= p_uiIndex) && (p_uiIndex < m_uiNumAttributes);
//		}
//	};
//};
//#endif