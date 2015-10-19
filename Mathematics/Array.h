#ifndef IncludedMathArrayH
#define IncludedMathArrayH

//===========================================================================
// Filename:	Array.h
// Author:		Jarrod MacKay
// Description:	Defines a generic 3-dimensional array class.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "MathBase.h"

//===========================================================================
// Templates
//===========================================================================

template<typename t_Type, u32 t_Rows, u32 t_Columns = 1, u32 t_Pages = 1>
class Array
{
//Attributes
private:

	t_Type m_Array[t_Rows * t_Columns * t_Pages];

//Operations
public:

	//ctor
	Array(const t_Type p_Initial = t_Type())
	: m_Array()
	{
		Assert(0 < t_Rows, "Invalid number of rows!");
		Assert(0 < t_Columns, "Invalid number of columns!");
		Assert(0 < t_Pages, "Invalid number of pages!");

		(*this) = p_Initial;
	}

	//copy ctor
	Array(const Array<t_Type, t_Rows, t_Columns, t_Pages>& p_Other)
	: m_Array()
	{
		(*this) = p_Other;
	}

	//copy assignment
	Array<t_Type, t_Rows, t_Columns, t_Pages>& operator = (const Array<t_Type, t_Rows, t_Columns, t_Pages>& p_Other)
	{
		for (u32 i = 1; i <= t_Rows; ++i)
		{
			for (u32 j = 1; j <= t_Columns; ++j)
			{
				for (u32 k = 1; k <= t_Pages; ++k)
				{
					(*this)(i, j, k) = p_Other(i, j, k);
				}
			}
		}
		return *this;
	}

	//single value assignment
	Array<t_Type, t_Rows, t_Columns, t_Pages>& operator = (const t_Type& p_Value)
	{
		for (u32 i = 1; i <= t_Rows; ++i)
		{
			for (u32 j = 1; j <= t_Columns; ++j)
			{
				for (u32 k = 1; k <= t_Pages; ++k)
				{
					(*this)(i, j, k) = p_Value;
				}
			}
		}
		return *this;
	}

	inline t_Type& operator ()(const u32 p_Row, const u32 p_Column, const u32 p_Page)
	{
		return m_Array[GetIndex(p_Row, p_Column, p_Page)];
	}

	inline t_Type operator ()(const u32 p_Row, const u32 p_Column, const u32 p_Page) const
	{
		return m_Array[GetIndex(p_Row, p_Column, p_Page)];
	}

//Methods
private:

	inline u32 GetIndex(u32 p_Row, u32 p_Column, u32 p_Page) const
	{
		--p_Row;
		--p_Column;
		--p_Page;

		Assert(p_Row < t_Rows, "Invalid row index!");
		Assert(p_Column < t_Columns, "Invalid column index!");
		Assert(p_Page < t_Pages, "Invalid page index!");

		return (t_Rows * t_Columns) * p_Page + (t_Rows) * p_Column + p_Row;
	}
};

//===========================================================================
// Specializations
//===========================================================================

template<typename t_Type, u32 t_Rows, u32 t_Columns>
class Array<t_Type, t_Rows, t_Columns, 1>
{
//Attributes
private:

	t_Type m_Array[t_Rows * t_Columns];

//Operations
public:

	//ctor
	Array(const t_Type p_Initial = t_Type())
	{
		Assert(0 < t_Rows, "Invalid number of rows!");
		Assert(0 < t_Columns, "Invalid number of columns!");

		(*this) = p_Initial;
	}

	//copy ctor
	Array(const Array<t_Type, t_Rows, t_Columns>& p_Other)
	{
		(*this) = p_Other;
	}

	//copy assignment
	Array<t_Type, t_Rows, t_Columns>& operator = (const Array<t_Type, t_Rows, t_Columns>& p_Other)
	{
		for (u32 i = 1; i <= t_Rows; ++i)
		{
			for (u32 j = 1; j <= t_Columns; ++j)
			{
				(*this)(i, j) = p_Other(i, j);
			}
		}
		return *this;
	}

	//single value assignment
	Array<t_Type, t_Rows, t_Columns>& operator = (const t_Type& p_Value)
	{
		for (u32 i = 1; i <= t_Rows; ++i)
		{
			for (u32 j = 1; j <= t_Columns; ++j)
			{
				(*this)(i, j) = p_Value;
			}
		}
		return *this;
	}

	inline t_Type& operator ()(const u32 p_Row, const u32 p_Column)
	{
		return m_Array[GetIndex(p_Row, p_Column)];
	}

	inline t_Type operator ()(const u32 p_Row, const u32 p_Column) const
	{
		return m_Array[GetIndex(p_Row, p_Column)];
	}

//Methods
private:

	inline u32 GetIndex(u32 p_Row, u32 p_Column) const
	{
		--p_Row;
		--p_Column;

		Assert(p_Row < t_Rows, "Invalid row index!");
		Assert(p_Column < t_Columns, "Invalid column index!");

		return (t_Rows) * p_Column + p_Row;
	}
};

#endif // #ifndef IncludedMathArrayH