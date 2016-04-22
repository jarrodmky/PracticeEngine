#ifndef IncludedAbstDynamicArrayH
#define IncludedAbstDynamicArrayH

//===========================================================================
// Filename:	DynamicArray.h
// Author:		Jarrod MacKay
// Description:	
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
	template<typename t_Type>
	class DynamicArray
	{
		//Attributes
	private:

		u32 m_Rows;
		u32 m_Columns;
		u32 m_Pages;
		u32 m_Elements;

		std::unique_ptr<t_Type[]> m_Array;

		//Operators
	public:

		explicit DynamicArray(const t_Type& p_InitialValue = t_Type(), const u32 p_Rows = 1, const u32 p_Columns = 1, const u32 p_Pages = 1)
			: m_Rows(p_Rows)
			, m_Columns(p_Columns)
			, m_Pages(p_Pages)
			, m_Elements(p_Rows * p_Columns * p_Pages)
			, m_Array(nullptr)
		{
			m_Array = std::make_unique<t_Type[]>(m_Elements);
			Clear(p_InitialValue);
		}

		//rule of 5
		~DynamicArray()
		{
			Destroy();
		}

		DynamicArray(const DynamicArray& p_Other)
			: m_Rows(p_Other.m_Rows)
			, m_Columns(p_Other.m_Columns)
			, m_Pages(p_Other.m_Pages)
			, m_Elements(p_Other.m_Rows * p_Other.m_Columns * p_Other.m_Pages)
			, m_Array(nullptr)
		{
			m_Array = std::make_unique<t_Type[]>(m_Elements);
			CopyInFrom(p_Other);
		}

		DynamicArray(const DynamicArray&& p_Other)
			: m_Rows(p_Other.m_Rows)
			, m_Columns(p_Other.m_Columns)
			, m_Pages(p_Other.m_Pages)
			, m_Elements(p_Other.m_Rows * p_Other.m_Columns * p_Other.m_Pages)
			, m_Array(nullptr)
		{
			m_Array.swap(p_Other.m_Array);
			p_Other.Destroy();
		}

		DynamicArray& operator=(const DynamicArray& p_Other)
		{
			m_Rows = p_Other.m_Rows;
			m_Columns = p_Other.m_Columns;
			m_Pages = p_Other.m_Pages;
			m_Elements = p_Other.m_Rows * p_Other.m_Columns * p_Other.m_Pages;
			m_Array.reset(nullptr);
			m_Array = std::make_unique<t_Type[]>(m_Elements);
			CopyInFrom(p_Other, m_Elements);
			return *this;
		}

		DynamicArray& operator=(DynamicArray&& p_Other)
		{
			m_Rows = p_Other.m_Rows;
			m_Columns = p_Other.m_Columns;
			m_Pages = p_Other.m_Pages;
			m_Elements = p_Other.m_Rows * p_Other.m_Columns * p_Other.m_Pages;
			m_Array.swap(p_Other.m_Array);
			p_Other.Destroy();
			return *this;
		}

		const bool operator==(DynamicArray& p_Other)
		{
			return m_Rows == p_Other.m_Rows
				&& m_Columns == p_Other.m_Columns
				&& m_Pages == p_Other.m_Pages
				&& m_Elements == p_Other.m_Elements
				&& EqualPrefixElements(p_Other);
		}

		inline const t_Type& operator()(const u32 p_Row, const u32 p_Column, const u32 p_Page = 0) const
		{
			return m_Array[GetIndex(p_Row, p_Column, p_Page)];
		}

		inline t_Type& operator()(const u32 p_Row, const u32 p_Column, const u32 p_Page = 0)
		{
			return m_Array[GetIndex(p_Row, p_Column, p_Page)];
		}

		inline const t_Type& operator[](const u32 p_Index) const
		{
			Assert(p_Index < m_Elements, "Invalid index!");
			return m_Array[p_Index];
		}

		inline t_Type& operator[](const u32 p_Index)
		{
			Assert(p_Index < m_Elements, "Invalid index!");
			return m_Array[p_Index];
		}

		//Methods
	public:

		void Resize(const u32 p_Rows, const u32 p_Columns = 1, const u32 p_Pages = 1)
		{
			const u32 newSize = p_Rows * p_Columns * p_Pages;
			if (Size() != newSize)
			{
				DynamicArray<t_Type> temp(t_Type(), p_Rows, p_Columns, p_Pages);
				temp.CopyInFrom(*this);
				*this = std::move(temp);
			}
			else
			{
				m_Elements = newSize;
				m_Rows = LargerOf<u32>(p_Rows, 0);
				m_Columns = LargerOf<u32>(p_Columns, 0);
				m_Pages = LargerOf<u32>(p_Pages, 0);
			}
		}

		inline void Store(const t_Type* p_Array, const u32 p_Elements, const u32 p_StartIndex = 0)
		{
			CopyInFrom(p_Array, p_Elements, p_StartIndex);
		}

		inline void Clear(const t_Type& p_Value = t_Type())
		{
			std::fill(m_Array.get(), (m_Array.get() + m_Elements), p_Value);
		}

		void Destroy()
		{
			m_Array.reset(nullptr);
			m_Rows = 0;
			m_Columns = 0;
			m_Pages = 0;
			m_Elements = 0;
		}

		inline const t_Type* const Raw() const 
		{
			return m_Array.get();
		}

		inline u32 Size() const
		{
			return m_Elements;
		}

		inline u32 Rows() const
		{
			return m_Rows;
		}

		inline u32 Columns() const
		{
			return m_Columns;
		}

		inline u32 Pages() const
		{
			return m_Pages;
		}

	private:

		inline u32 GetIndex(const u32 p_Row, const u32 p_Column, const u32 p_Page) const
		{
			Assert(p_Row < m_Rows, "Invalid row index!");
			Assert(p_Column < m_Columns, "Invalid column index!");
			Assert(p_Page < m_Pages, "Invalid page index!");
			return (m_Rows * m_Columns) * p_Page + (m_Rows)* p_Column + p_Row;
		}

		inline void CopyInFrom(const DynamicArray& p_Other)
		{
			CopyInFrom(p_Other.m_Array.get(), SmallerOf(p_Other.Size(), Size()));
		}

		void CopyInFrom(const t_Type* p_Other, const u32 p_Elements, const u32 p_StartIndex = 0)
		{
			Assert(m_Elements >= (p_Elements + p_StartIndex), "Cannot copy more than size!");
			for (u32 i = 0; i < p_Elements; ++i)
			{
				m_Array[i + p_StartIndex] = p_Other[i];
			}
		}

		const bool EqualPrefixElements(const DynamicArray& p_Other)
		{
			bool check = true;
			for (u32 i = 0; i < min(m_Elements, p_Other.m_Elements); ++i)
			{
				check = check && ((*this)[i] == p_Other[i]);
			}
			return check;
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstDynamicArrayH