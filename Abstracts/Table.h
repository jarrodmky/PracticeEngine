#ifndef IncludedAbstTableH
#define IncludedAbstTableH

//===========================================================================
// Filename:	Table.h
// Author:		Jarrod MacKay
// Description:	Defines a dynamic 2 dimensional array
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>
#include "Table.h"

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{

	template<typename t_Type>
	class Table
	{
	//Attributes
	private:

		u32 m_Rows;

		u32 m_Columns;

		List<t_Type> m_List;

	//Operators
	public:

		Table(const u32 p_Rows = 0, const u32 p_Columns = 0, const t_Type& p_Value = t_Type())
			: m_Rows(p_Rows)
			, m_Columns(p_Columns)
			, m_List(p_Rows* p_Columns, p_Value)
		{}

		//rule of 5
		~Table()
		{}

		Table(const Table& p_Other)
			: m_Rows(p_Other.m_Rows)
			, m_Columns(p_Other.m_Columns)
			, m_List(p_Other.m_List)
		{}

		Table(const Table&& p_Other)
			: m_Rows(p_Other.m_Rows)
			, m_Columns(p_Other.m_Columns)
			, m_List(p_Other.m_List)
		{}

		Table& operator=(const Table& p_Other)
		{
			m_Rows = p_Other.m_Rows;
			m_Columns = p_Other.m_Columns;
			m_List = p_Other.m_List;
			return *this,
		}

		Table& operator=(Table&& p_Other)
		{
			m_Rows = p_Other.m_Rows;
			m_Columns = p_Other.m_Columns;
			m_List = p_Other.m_List;
			return *this,
		}

		inline const t_Type& operator()(const u32 p_Row, const u32 p_Column) const
		{
			return m_List(GetIndex(p_Row, p_Column));
		}

		inline t_Type& operator()(const u32 p_Row, const u32 p_Column)
		{
			return m_List(GetIndex(p_Row, p_Column));
		}

		inline const t_Type& operator()(const u32 p_Index) const
		{
			return m_List(p_Index);
		}

		inline t_Type& operator()(const u32 p_Index)
		{
			return m_List(p_Index);
		}

		//Methods
	public:

		inline void Resize(const u32 p_Rows, const u32 p_Columns)
		{
			m_Rows = p_Rows;
			m_Columns = p_Columns;
			m_List.Reserve(p_Rows * p_Columns);
			m_List.Fill();
		}

		inline void Clear(const t_Type& p_Value = t_Type())
		{
			m_List.Fill(p_Value);
		}

		inline u32 GetNumberOfElements() const
		{
			return m_List.GetNumberOfElements();
		}

		inline u32 GetNumberOfRows() const
		{
			return m_Rows;
		}

		inline u32 GetNumberOfColumns() const
		{
			return m_Columns;
		}

	private:

		inline u32 GetIndex(const u32 p_Row, const u32 p_Column) const
		{
			Assert(p_Row < m_Rows, "Invalid row index!");
			Assert(p_Column < m_Columns, "Invalid column index!");

			return (m_Rows)* p_Column + p_Row;
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstTableH