#ifndef IncludedAbstPoolH
#define IncludedAbstPoolH

//===========================================================================
// Filename:	Pool.h
// Author:		Jarrod MacKay
// Description:	Defines a pool of objects
//===========================================================================

//===========================================================================
// Includes
//===========================================================================

#include "DynamicArray.h"


//===========================================================================
// Templates
//===========================================================================

namespace Abstracts
{
	template<u32 t_LotSize>
	class AddressSet
	{
	//Attributes
	private:

		u32 m_Lots;

		DynamicArray<u8> m_Block;

	//Operators
	public:

		inline AddressSet(const u32 p_Addresses)
			: m_Lots(p_Addresses)
			, m_Block(0, m_Lots * t_LotSize)
		{}

		inline ~AddressSet() {}

	//Methods
	public:

		inline void* GetAddress(const u32 p_Lot)
		{
			Assert(p_Lot < m_Lots, "Not a valid lot!");
			return static_cast<void*>(&(m_Block[p_Lot * t_LotSize]));
		}

		const bool HasLotAt(const void* p_Address) const
		{
			for (u32 i = 0; i < m_Lots; ++i)
			{
				if (p_Address == &m_Block[i * t_LotSize])
				{
					return true;
				}

			}
			return false;
		}

		inline const u32 Size() const
		{
			return m_Lots;
		}

		inline void Resize(const u32 p_NewSize)
		{
			m_Lots = p_NewSize;
			m_Block.Resize(m_Lots * t_LotSize);
		}
	};



	template<typename t_Type>
	class Pool
	{
	//Attributes
	private:

		u32 m_NextFreeLane;

		AddressSet<sizeof(t_Type)> m_Lanes;

		std::vector<bool> m_Used;

		//Operators
	public:

		inline Pool(const u32 p_Size)
			: m_NextFreeLane(0)
			, m_Lanes(p_Size)
			, m_Used(p_Size, false)
		{
			for (u32 i = 0; i < p_Size - 1; ++i)
			{
				SetNextLane(i, i + 1);
			}

			SetNextLane(p_Size - 1, -1);
		}

		inline ~Pool() 
		{
			for (u32 i = 0; i < m_Lanes.Size(); ++i)
			{
				if (IsUsed(i))
				{
					Get(i)->~t_Type();
				}
			}
		}

		//Methods
	public:

		template<typename... t_Args>
		const u32 Fill(const t_Args&... p_Args)
		{
			Assert(!IsFull(), "No more space!");
			u32 fillLane = m_NextFreeLane;
			Assert(!IsUsed(fillLane), "Lane is in use!");
			m_NextFreeLane = *GetNextLane(fillLane);
			m_Used[fillLane].flip();
			new(m_Lanes.GetAddress(fillLane)) t_Type(p_Args...);
			return fillLane;
		}

		void Free(const u32 p_Slot)
		{
			Assert(p_Slot < m_Lanes.Size(), "Invalid lane!")
			Assert(IsUsed(p_Slot), "Lane not is use!");
			Get(p_Slot)->~t_Type();
			SetNextLane(p_Slot, m_NextFreeLane);
			m_Used[p_Slot].flip();
			m_NextFreeLane = p_Slot;
		}

		inline void Expand(const u32 p_NewSize)
		{
			Assert(p_NewSize > Size(), "Not expanding!");
			const u32 lastSize = m_Lanes.Size();
			m_Used.resize(p_NewSize, false);
			m_Lanes.Resize(p_NewSize);
			if (0 != lastSize)
			{
				for (u32 i = 0; i < lastSize; ++i)
				{
					if (-1 == *GetNextLane(i))
					{
						SetNextLane(i, lastSize);
						break;
					}
				}
			}
			else
			{
				m_NextFreeLane = 0;
			}
			for (u32 i = lastSize; i < p_NewSize - 1; ++i)
			{
				SetNextLane(i, i + 1);
			}
			SetNextLane(p_NewSize - 1, -1);
		}

		inline void Shrink(const u32 p_NewSize)
		{
			Assert(p_NewSize < Size(), "Not shrinking!");
			//check used before deleting
			const u32 currSize = m_Lanes.Size();
			for (u32 i = p_NewSize; i < currSize; ++i)
			{
				if (IsUsed(i))
				{
					Get(i)->~t_Type();
					m_Used[i].flip();
				}
			}
			DebugBlock
				(
				for (u32 i = p_NewSize; i < currSize; ++i)
				{
					Assert(!IsUsed(i), "Memory not freed!");
				}
			);
			m_Used.resize(p_NewSize);
			m_Lanes.Resize(p_NewSize);
			m_NextFreeLane = -1;
			if (0 != p_NewSize)
			{
				for (s64 iExpanded = p_NewSize - 1; iExpanded >= 0; --iExpanded)
				{
					const u32 i = static_cast<u32>(iExpanded);
					if (!IsUsed(i))
					{
						SetNextLane(i, m_NextFreeLane);
						m_NextFreeLane = i;
					}
				}
			}
		}

		inline t_Type* Get(const u32 p_Slot)
		{
			Assert(IsUsed(p_Slot), "Cannot access garbage!");
			return static_cast<t_Type*>(m_Lanes.GetAddress(p_Slot));
		}

		inline const bool IsFull() const
		{
			return m_NextFreeLane == -1;
		}

		inline const bool IsEmpty() const
		{
			for (auto bit : m_Used)
			{
				if (bit)
				{
					return false;
				}
			}
			return true;
		}

		inline const u32 Size() const
		{
			return m_Lanes.Size();
		}

	protected:

		inline u32* GetNextLane(const u32 p_Slot)
		{
			return static_cast<u32*>(m_Lanes.GetAddress(p_Slot));
		}

		inline void SetNextLane(const u32 p_Slot, const u32 p_NextLane)
		{
			*(GetNextLane(p_Slot)) = p_NextLane;
		}

		inline const bool IsUsed(const u32 p_Slot) const
		{
			return m_Used[p_Slot];
		}
	};
} // namespace Abstracts
#endif // #ifndef IncludedAbstPoolH