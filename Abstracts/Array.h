#ifndef IncludedAbstArrayH
#define IncludedAbstArrayH

//===========================================================================
// Filename:	Array.h
// Author:		Jarrod MacKay
// Description:	Defines a generic 3-dimensional static array class.
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include <Core.h>

//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{
	template <typename t_Type, u32 t_Rows, u32 t_Columns = 1, u32 t_Pages = 1>
	class Array
	{
	//Attributes
	private:

		typedef const Array<t_Type, t_Rows, t_Columns, t_Pages>& ArrayRef;

		t_Type m_Array[t_Rows * t_Columns * t_Pages];

		//Operations
	public:

		//ctor
		inline Array(const t_Type p_Initial = t_Type())
		{
			Assert(0 < t_Rows, "Invalid number of rows!");
			Assert(0 < t_Columns, "Invalid number of columns!");
			Assert(0 < t_Pages, "Invalid number of pages!");

			Clear(p_Initial);
		}

		//ctor
		inline Array(const t_Type* p_Initial, const u32 p_Size)
			: Array()
		{
			Assert(p_Size <= t_Rows * t_Columns * t_Pages, "Cannot fit initializer array!");
			Assert(!((p_Size == 0) ^ (p_Initial == nullptr)), "Size zero means null array!");
			Assert((sizeof(t_Type*) == sizeof(p_Initial)) || (sizeof(p_Initial) == p_Size), "Should be same size!");
			std::copy_n(p_Initial, p_Size, m_Array);
		}

		//copy ctor
		inline Array(ArrayRef p_Other)
			: Array()
		{
			std::copy_n(p_Other.m_Array, t_Rows * t_Columns * t_Pages, m_Array);
		}

		//copy assignment
		inline ArrayRef operator =(ArrayRef p_Other)
		{
			std::copy_n(p_Other.m_Array, t_Rows * t_Columns * t_Pages, m_Array);
			return *this;
		}

		//comparison
		inline const bool operator ==(ArrayRef p_Other) const
		{
			return std::equal(m_Array, (m_Array + t_Rows * t_Columns * t_Pages), p_Other.m_Array);
		}

		inline t_Type& operator ()(const u32 p_Row, const u32 p_Column, const u32 p_Page)
		{
			return m_Array[GetIndex(p_Row, p_Column, p_Page)];
		}

		inline const t_Type& operator ()(const u32 p_Row, const u32 p_Column, const u32 p_Page) const
		{
			return m_Array[GetIndex(p_Row, p_Column, p_Page)];
		}

		inline t_Type* operator*()
		{
			return m_Array;
		}

		//Methods
	public:

		//single value assignment
		inline void Clear(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array, (m_Array + t_Rows * t_Columns * t_Pages), p_Value);
		}

		//comparisons
		inline const bool Equals(ArrayRef p_Other, BoolFxn<t_Type> p_Function) const
		{
			return std::equal(m_Array, (m_Array + t_Rows * t_Columns * t_Pages), p_Other.m_Array, p_Function);
		}

		//apply function methods
		inline void Map(UnaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows * t_Columns * t_Pages), m_Array, p_Function);
		}

		inline void Map(ArrayRef p_Other, BinaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows * t_Columns * t_Pages), p_Other.m_Array, m_Array, p_Function);
		}

	private:

		inline u32 GetIndex(const u32 p_Row, const u32 p_Column, const u32 p_Page) const
		{
			Assert(p_Row < t_Rows, "Invalid row index!");
			Assert(p_Column < t_Columns, "Invalid column index!");
			Assert(p_Page < t_Pages, "Invalid page index!");

			return (t_Rows * t_Columns) * p_Page + (t_Rows) * p_Column + p_Row;
		}
	};

	//===========================================================================
	// Specializations
	//===========================================================================

	//==========
	// 2D array
	//==========
	template <typename t_Type, u32 t_Rows, u32 t_Columns>
	class Array <t_Type, t_Rows, t_Columns, 1>
	{
	//Attributes
	private:

		typedef const Array<t_Type, t_Rows, t_Columns>& ArrayRef;

		t_Type m_Array[t_Rows * t_Columns];

		//Operations
	public:

		//ctor
		inline Array(const t_Type p_Initial = t_Type())
		{
			Assert(0 < t_Rows, "Invalid number of rows!");
			Assert(0 < t_Columns, "Invalid number of columns!");

			Clear(p_Initial);
		}

		//ctor
		inline Array(const t_Type* p_Initial, const u32 p_Size)
			: Array()
		{
			Assert(p_Size <= t_Rows * t_Columns, "Cannot fit initializer array!");
			Assert(!((p_Size == 0) ^ (p_Initial == nullptr)), "Size zero means null array!");
			Assert((sizeof(t_Type*) == sizeof(p_Initial)) || (sizeof(p_Initial) == p_Size), "Should be same size!");
			std::copy_n(p_Initial, p_Size, m_Array);
		}

		//copy ctor
		inline Array(ArrayRef p_Other)
			: Array()
		{
			std::copy_n(p_Other.m_Array, t_Rows * t_Columns, m_Array);
		}

		//copy assignment
		inline ArrayRef operator =(ArrayRef p_Other)
		{
			std::copy_n(p_Other.m_Array, t_Rows * t_Columns, m_Array);
			return *this;
		}

		//comparison
		inline const bool operator ==(ArrayRef p_Other) const
		{
			return std::equal(m_Array, (m_Array + t_Rows * t_Columns), p_Other.m_Array);
		}

		inline t_Type& operator ()(const u32 p_Row, const u32 p_Column)
		{
			return m_Array[GetIndex(p_Row, p_Column)];
		}

		inline const t_Type& operator ()(const u32 p_Row, const u32 p_Column) const
		{
			return m_Array[GetIndex(p_Row, p_Column)];
		}

		inline t_Type* operator*()
		{
			return m_Array;
		}

		//Methods
	public:

		//single value assignment
		inline void Clear(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array, (m_Array + t_Rows * t_Columns), p_Value);
		}

		//comparisons
		inline const bool Equals(ArrayRef p_Other, BoolFxn<t_Type> p_Function) const
		{
			return std::equal(m_Array, (m_Array + t_Rows * t_Columns), p_Other.m_Array, p_Function);
		}

		//apply function methods
		inline void Map(UnaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows * t_Columns), m_Array, p_Function);
		}

		inline void Map(ArrayRef p_Other, BinaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows * t_Columns), p_Other.m_Array, m_Array, p_Function);
		}

	private:

		inline u32 GetIndex(const u32 p_Row, const u32 p_Column) const
		{
			Assert(p_Row < t_Rows, "Invalid row index!");
			Assert(p_Column < t_Columns, "Invalid column index!");

			return (t_Rows) * p_Column + p_Row;
		}
	};

	//==========
	// 1D array
	//==========
	template <typename t_Type, u32 t_Rows>
	class Array <t_Type, t_Rows, 1, 1>
	{
	//Attributes
	private:

		typedef const Array<t_Type, t_Rows>& ArrayRef;

		t_Type m_Array[t_Rows];

		//Operations
	public:

		//ctor
		inline Array(const t_Type p_Initial = t_Type())
		{
			Clear(p_Initial);
		}

		//ctor
		inline Array(const t_Type* p_Initial, const u32 p_Size)
			: Array()
		{
			Assert(p_Size <= t_Rows, "Cannot fit initializer array!");
			Assert(!((p_Size == 0) ^ (p_Initial == nullptr)), "Size zero means null array!");
			Assert((sizeof(t_Type*) == sizeof(p_Initial)) || (sizeof(p_Initial) == p_Size), "Should be same size!");
			std::copy_n(p_Initial, p_Size, m_Array);
		}

		//copy ctor
		inline Array(ArrayRef p_Other)
			: Array()
		{
			std::copy_n(p_Other.m_Array, t_Rows, m_Array);
		}

		//copy assignment
		inline ArrayRef operator =(ArrayRef p_Other)
		{
			std::copy_n(p_Other.m_Array, t_Rows, m_Array);
			return *this;
		}

		//comparison
		inline const bool operator ==(ArrayRef p_Other) const
		{
			return std::equal(m_Array, (m_Array + t_Rows), p_Other.m_Array);
		}

		inline t_Type& operator [](const u32 p_Row)
		{
			return m_Array[p_Row];
		}

		inline const t_Type& operator [](const u32 p_Row) const
		{
			return m_Array[p_Row];
		}

		inline t_Type* operator*()
		{
			return m_Array;
		}

		//Methods
	public:

		//single value assignment
		inline void Clear(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array, (m_Array + t_Rows), p_Value);
		}

		//comparisons
		inline const bool Equals(ArrayRef p_Other, BoolFxn<t_Type> p_Function) const
		{
			return std::equal(m_Array, (m_Array + t_Rows), p_Other.m_Array, p_Function);
		}

		//apply function methods
		inline void Map(UnaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows), m_Array, p_Function);
		}

		inline void Map(ArrayRef p_Other, BinaryFxn<t_Type> p_Function)
		{
			std::transform(m_Array, (m_Array + t_Rows), p_Other.m_Array, m_Array, p_Function);
		}
	};

	
	//==========
	// Error array
	//==========
	template <typename t_Type>
	class Array <t_Type, 0, 0, 0>;
}
#endif // #ifndef IncludedAbstArrayH